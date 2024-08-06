#include <iostream>
#include <fstream>
#include <omp.h>


using namespace std;


void print(float** A, int N, int M);

void divide(float** A, int N, int M, float d);

void subtract(float** A, int M, int a, int b, float c);

void transform(float** A, int N, int M);

void transform_par(float** A, int N, int M);

void GaussJordan(float** A, int N, int M);

void GaussJordan_par(float** A, int N, int M);


int main()
{

	ifstream input("input.txt");
	if (!input.is_open())
	{
		cout << "not open!" << endl;
	}
	int N;
	int M;
	input >> N;
	input >> M;
	float** A = new float* [N];
	for (int i = 0; i < N; ++i)
	{
		A[i] = new float[M];
		for (int j = 0; j < M; ++j)
		{
			input >> A[i][j];
		}
	}
	print(A, N, M);
	cout << endl;
	double t = omp_get_wtime();
	GaussJordan(A, N, M);
	cout << "time line: " << omp_get_wtime() - t << endl;
	print(A, N, M);
	input.seekg(0, ios::beg);
	input >> N;
	input >> M;
	for (int i = 0; i < N; ++i)
	{
		A[i] = new float[M];
		for (int j = 0; j < M; ++j)
		{
			input >> A[i][j];
		}
	}
	print(A, N, M);
	cout << endl;
	t = omp_get_wtime();
	GaussJordan_par(A, N, M);
	cout << "time parallel: " << omp_get_wtime() - t << endl;
	print(A, N, M);


	for (int i = 0; i < N; ++i)
	{
		delete[]A[i];
	}
	return EXIT_SUCCESS;
}

void print(float** A, int N, int M)
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
}

void divide(float** A, int N, int M, float d)
{
	for (int i = 0; i < M; ++i)
	{
		if (d != 0)
			A[N][i] /= d;
	}
}

void subtract(float** A, int M, int a, int b, float c)
{
	for (int i = 0; i < M; ++i)
	{
		A[b][i] -= c * A[a][i];
	}
}

void transform(float** A, int N, int M)
{
	for (int i = 0; i < N; ++i)
	{
		divide(A, i, M, A[i][i]);
		for (int j = 0; j < N; ++j)
		{
			if (i != j)
			{
				subtract(A, M, i, j, A[j][i]);
			}
		}
	}
}

void transform_par(float** A, int N, int M)
{

	for (int i = 0; i < N; ++i)
	{
		divide(A, i, M, A[i][i]);
#pragma omp parallel for schedule(static)
		for (int j = 0; j < N; ++j)
		{
			if (i != j)
			{
				subtract(A, M, i, j, A[j][i]);
			}
		}
	}


}

void GaussJordan(float** A, int N, int M)
{
	transform(A, N, M);
	for (int i = 1; i <= N; ++i)
	{
		cout << "x" << i << " = " << A[i - 1][N] << endl;
	}
}

void GaussJordan_par(float** A, int N, int M)
{
	transform_par(A, N, M);
	for (int i = 1; i <= N; ++i)
	{
		cout << "x" << i << " = " << A[i - 1][N] << endl;
	}
}