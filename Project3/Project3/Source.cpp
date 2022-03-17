#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include<iomanip>
//#include"Point.h"

#define N 100000000
double PI = 3.14159265;
double x[100000000];
//Point p[10000];


void calculate_sin(int n);

void calulate_pi(int n);

bool prime(int a);

int prime_numbers_line(int n); // n >=3

int prime_numbers_2(int n);

int prime_numbers_4(int n);


void filling_p(int n);

double diameter_line(int n);

double diameter_2(int n);

double diameter_3(int n);

double diameter_4(int n);

using namespace std;
int main()
{
	srand(time(0));
	//calculate_sin(100000000);

	calulate_pi(100000000);


	double t = omp_get_wtime();
	cout << "prime numbers: " << prime_numbers_line(10000000) << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
	cout << "prime numbers: " << prime_numbers_2(10000000) << endl;
	cout << "Time 2: " << omp_get_wtime() - t << endl;

	/*
	filling_p(10000);
	double t = omp_get_wtime();
	cout << "diameter :" << diameter_line(10000) << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;
	*/



	return EXIT_SUCCESS;
}

void calculate_sin(int n)
{
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
	{
		x[i] = sin(PI * i / (2.0 * n));

	}
	cout << "Time line: " << omp_get_wtime() - t << endl;
	////////////////////////////////////////////
	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / 2; i += 2)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
#pragma omp section
		{
			for (int i = 1; i < n; i += 2)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
	}
	cout << "Time 2: " << omp_get_wtime() - t << endl;
	/////////////////////////////////////////////////////////////////////
	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i <= n; i += 4)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
#pragma omp section
		{
			for (int i = 1; i <= n; i += 4)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
#pragma omp section
		{
			for (int i = 2; i <= n; i += 4)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
#pragma omp section
		{
			for (int i = 3; i <= n; i += 4)
			{
				x[i] = sin(PI * i / (2.0 * n));
			}
		}
	}
	cout << "Time 4: " << omp_get_wtime() - t << endl;

}

void calulate_pi(int n)
{
	long double pi = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / N;
	cout << "Time line: " << omp_get_wtime() - t << endl;
	cout << setprecision(15) << "pi = " << pi << endl;

	pi = 0;
	double tt = 0;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (int i = 1; i <= n; i += 2)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}
		}
#pragma omp section
		{
			for (int i = 2; i <= n; i += 2)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}
		}
	}

	pi = pi * 4 / n;
	tt = omp_get_wtime() - t;
	cout << setprecision(6) << "Time 2: " << tt << endl;

	cout << setprecision(15) << "pi = " << pi << endl;

	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (int i = 0; i < n; i += 4)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}

		}
#pragma omp section
		{
			for (int i = 1; i < n; i += 4)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}

		}
#pragma omp section
		{
			for (int i = 2; i < n; i += 4)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}

		}
#pragma omp section
		{
			for (int i = 3; i < n; i += 4)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}

		}
	}
	pi = pi * 4 / n;
	cout << setprecision(6) << "Time 4: " << omp_get_wtime() - t << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
}

bool prime(int a)
{
	if (a == 1) return false;
	/*
	if (a % 2 == 0 && a != 2)
	{
		return false;
	}
	*/
	for (int i = 3; i * i <= a; i += 2)
	{
		if (a % i == 0)
		{
			return false;
		}
	}
	return true;
}

int prime_numbers_line(int n)
{
	int p = 0;
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++p;
		}
	}
	return p;
}

int prime_numbers_2(int n)
{
	int p = 0;
#pragma omp parallel sections reduction(+:p)
	{
#pragma omp section
		{
			for (int i = 3; i <= n; i += 4)
			{
				if (prime(i))
				{
					++p;
				}
			}
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 4)
			{
				if (prime(i))
				{
					++p;
				}
			}
		}
	}
	return p;
}

int prime_numbers_4(int n)
{
	return 0;
}

/*
void filling_p(int n)
{
	for (int i = 0; i < n; ++i)
	{
		p[i].x = rand() % 100;
		p[i].y = rand() % 100;
	}
}
double diameter_line(int n)
{
	double max = 0;
	double d = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	return max;
}
*/
double diameter_2(int n)
{
	return 0.0;
}

double diameter_3(int n)
{
	return 0.0;
}

double diameter_4(int n)
{
	return 0.0;
}