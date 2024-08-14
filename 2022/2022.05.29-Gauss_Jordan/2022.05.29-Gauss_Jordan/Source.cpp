#include <iostream>
#include <fstream>
#include <omp.h>
using namespace std;
//Программа считывает из файла input.txt размер матрицы NxM и ее элементы
//После этого методом Гаусса-Жордана решается система линейных уравнений, соответсвующая данной матрице
//Решение СЛУ выполняется сначала линейным образом, затем с использованием параллельных потоков
//Время, затраченное на решение системы, выводится на экран для сравнения эффективности обоих решений
void print(float** A, int N, int M);											//Функция, выводящая матрицу размером NxM на экран
void divide(float** A, int N, int M, float d);						//Деление всех элементов в строке под номером a на число d
void subtract(float** A, int M, int a, int b, float c);		//Поэлементное вычитание из элементов строки b элементов строки a с коэффициентом c
void transform(float** A, int N, int M);									//Метод Гаусса-Жордана, линейное решение
void transform_par(float** A, int N, int M);							//Метод Гаусса-Жордана, решение с использованием параллельных потоков(тип планирования static)
void GaussJordan(float** A, int N, int M);								//Вызов функции, реализующей линейный метод Гаусса-Жордана и вывод решения СЛУ на экран
void GaussJordan_par(float** A, int N, int M);						//Вызов функции, реализующей параллельный метод Гаусса-Жордана и вывод решения СЛУ на экран


int main()
{
	ifstream input("input.txt");														//Файл, с которого будут считываться параметры матрицы А
	if (!input.is_open())
		cout << "not open!" << endl;
	int N;
	int M;
	input >> N;
	input >> M;
	float** A = new float* [N];
	for (int i = 0; i < N; ++i)
	{
		A[i] = new float[M];																	//Инициализация элементов матрицы и записывание данных из файла input.txt
		for (int j = 0; j < M; ++j)														//Матрица А имеет N строк и N + 1 столбоц
			input >> A[i][j];																		//Последний столбец характеризует вектор свободных членов в СЛУ
	}
	print(A, N, M);
	cout << endl;


	double t = omp_get_wtime();															//Момент времени перед началом вычислений
	GaussJordan(A, N, M);																		//Линейное решение
	cout << "time line: " << omp_get_wtime() - t << endl;		//Время, затраченное на решение СЛУ
	print(A, N, M);
	cout << endl;


	input.seekg(0, ios::beg);																//Повторное считывание данных из файла, т.к. матрица А изменила
	input >> N;																							//свой вид под действием функции GaussJordan
	input >> M;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			input >> A[i][j];
	print(A, N, M);
	cout << endl;


	t = omp_get_wtime();																		//Момент времени перед началом вычислений
	GaussJordan_par(A, N, M);																//Решение с использованием параллельных потоков
	cout << "time parallel: " << omp_get_wtime() - t << endl; //Время, затраченное на решение СЛУ
	print(A, N, M);

	for (int i = 0; i < N; ++i)															//Освобождение памяти
		delete[] A[i];
	delete[] A;
	return EXIT_SUCCESS;
}

void print(float** A, int N, int M)												//Функция, выводящая матрицу размером NxM на экран
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
			cout << A[i][j] << " ";
		cout << endl;
	}
}

void divide(float** A, int a, int M, float d)							//Деление всех элементов в строке под номером a на число d
{
	for (int i = 0; i < M; ++i)
		if (d != 0)
			A[a][i] /= d;
}

void subtract(float** A, int M, int a, int b, float c)		//Поэлементное вычитание из элементов строки b элементов строки a с коэффициентом c
{
	for (int i = 0; i < M; ++i)
		A[b][i] -= c * A[a][i];
}

void transform(float** A, int N, int M)										//Метод Гаусса-Жордана, линейное решение
{
	for (int i = 0; i < N; ++i)
	{
		divide(A, i, M, A[i][i]);
		for (int j = 0; j < N; ++j)
			if (i != j)
				subtract(A, M, i, j, A[j][i]);
	}
}

void transform_par(float** A, int N, int M)								//Метод Гаусса-Жордана, решение с использованием параллельных потоков(тип планирования static)
{
	for (int i = 0; i < N; ++i)
	{
		divide(A, i, M, A[i][i]);
#pragma omp parallel for schedule(static)
		for (int j = 0; j < N; ++j)
			if (i != j)
				subtract(A, M, i, j, A[j][i]);
	}
}

void GaussJordan(float** A, int N, int M)									//Вызов функции, реализующей линейный метод Гаусса-Жордана и вывод решения СЛУ на экран
{
	transform(A, N, M);
	for (int i = 1; i <= N; ++i)
		cout << "x" << i << " = " << A[i - 1][N] << endl;
}

void GaussJordan_par(float** A, int N, int M)							//Вызов функции, реализующей параллельный метод Гаусса-Жордана и вывод решения СЛУ на экран
{
	transform_par(A, N, M);
	for (int i = 1; i <= N; ++i)
		cout << "x" << i << " = " << A[i - 1][N] << endl;
}