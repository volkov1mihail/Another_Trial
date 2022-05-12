#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include<iomanip>
#include"Point.h"

#define N 100000000
double PI = 3.14159265;
double x[100000000];
Point p[10000];


void calculate_sin(int n);

void calculate_sin_pf(int n);

void calulate_pi(int n);

void calulate_pi_pf(int n);

bool prime(int a);

int prime_numbers_line(int n); // n >=3

int prime_numbers_2(int n);

void prime_numbers_pf(int n);

void filling_p(int n);

double diameter_line(int n);

double diameter_2(int n);

double diameter_3(int n);

double diameter_4(int n);

void diameter_pf(int n);

using namespace std;
int main()
{
	srand(time(0));

	//calculate_sin(100000000);

	//calulate_pi(100000000);

	/*
	double t = omp_get_wtime();
	cout << "prime numbers: " << prime_numbers_line(10000000) << endl;
	cout  << setprecision(6)  << "Time line: " << omp_get_wtime() - t << endl;
	t = omp_get_wtime();
	cout << "prime numbers: " << prime_numbers_2(10000000) << endl;
	cout << "Time 2: " << omp_get_wtime() - t << endl;
	*/


	/*
	filling_p(10000);
	double t = omp_get_wtime();
	cout << "diameter :" << diameter_line(10000) << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;
	t = omp_get_wtime();
	cout << "diameter :" << diameter_2(10000) << endl;
	cout << setprecision(6) << "Time 2: " << omp_get_wtime() - t << endl;
	t = omp_get_wtime();
	cout << "diameter :" << diameter_3(10000) << endl;
	cout << setprecision(6) << "Time 3: " << omp_get_wtime() - t << endl;
	t = omp_get_wtime();
	cout << "diameter :" << diameter_4(10000) << endl;
	cout << setprecision(6) << "Time 4: " << omp_get_wtime() - t << endl;
	*/



	//calculate_sin_pf(100000000);

	//calulate_pi_pf(100000000);

	//prime_numbers_pf(10000000);

	//diameter_pf(10000);

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

void calculate_sin_pf(int n)
{
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
	{
		x[i] = sin(PI * i / (2.0 * n));

	}
	cout << "Time line: " << omp_get_wtime() - t << endl;
	////////////////////////////////////////////
	t = omp_get_wtime();
#pragma omp parallel for schedule (static)
	for (int i = 0; i < n; ++i)
	{
		x[i] = sin(PI * i / (2.0 * n));

	}
	cout << "Time static: " << omp_get_wtime() - t << endl;
	////////////////////////////////////////////
	t = omp_get_wtime();
#pragma omp parallel for schedule (dynamic, 1000)
	for (int i = 0; i < n; ++i)
	{
		x[i] = sin(PI * i / (2.0 * n));
	}
	cout << "Time dynamic: " << omp_get_wtime() - t << endl;
	////////////////////////////////////////////
	t = omp_get_wtime();
#pragma omp parallel for schedule (guided, 1000)
	for (int i = 0; i < n; ++i)
	{
		x[i] = sin(PI * i / (2.0 * n));
	}
	cout << "Time guided: " << omp_get_wtime() - t << endl;

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

void calulate_pi_pf(int n)
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
	//////////////////////////////////////////
	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / N;
	cout << setprecision(6) << "Time static: " << omp_get_wtime() - t << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	//////////////////////////////////////////
	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / N;
	cout << setprecision(6) << "Time dynamic: " << omp_get_wtime() - t << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	//////////////////////////////////////////
	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / N;
	cout << setprecision(6) << "Time guided: " << omp_get_wtime() - t << endl;
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

void prime_numbers_pf(int n)
{
	int p = 0;
	double t = omp_get_wtime();
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++p;
		}
	}
	cout << "prime numbers: " << p << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;
	///////////////////////////////////////////////
	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++p;
		}
	}
	cout << "prime numbers: " << p << endl;
	cout << setprecision(6) << "Time static: " << omp_get_wtime() - t << endl;
	///////////////////////////////////////////////
	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++p;
		}
	}
	cout << "prime numbers: " << p << endl;
	cout << setprecision(6) << "Time dynamic: " << omp_get_wtime() - t << endl;
	///////////////////////////////////////////////
	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++p;
		}
	}
	cout << "prime numbers: " << p << endl;
	cout << setprecision(6) << "Time guided: " << omp_get_wtime() - t << endl;

}

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

double diameter_2(int n)
{
	double max1 = 0;
	double max2 = 0;
	double d1 = 0;
	double d2 = 0;
	int c = n - sqrt(2) * n / 2;
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < c; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d1 = p[i].dist(p[j]);
					if (max1 < d1)
					{
						max1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = c; i < n - 1; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d2 = p[i].dist(p[j]);
					if (max2 < d2)
					{
						max2 = d2;
					}
				}
			}
		}
	}
	return (max1 > max2) ? max1 : max2;
}

double diameter_3(int n)
{
	double max1 = 0;
	double max2 = 0;
	double max3 = 0;
	double d1 = 0;
	double d2 = 0;
	double d3 = 0;
	int b = n - n / sqrt(3);
	int a = b - sqrt(2) * b / 2;

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < a; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d1 = p[i].dist(p[j]);
					if (max1 < d1)
					{
						max1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = a; i < b; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d2 = p[i].dist(p[j]);
					if (max2 < d2)
					{
						max2 = d2;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = b; i < n - 1; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d3 = p[i].dist(p[j]);
					if (max3 < d3)
					{
						max3 = d3;
					}
				}
			}
		}
	}
	max1 = (max1 > max2) ? max1 : max2;
	return (max1 > max3) ? max1 : max3;
}

double diameter_4(int n)
{
	double max1 = 0;
	double max2 = 0;
	double max3 = 0;
	double max4 = 0;
	double d1 = 0;
	double d2 = 0;
	double d3 = 0;
	double d4 = 0;
	int c2 = n - sqrt(2) * n / 2;
	int c1 = c2 - sqrt(2) * c2 / 2;
	int c3 = 2 * c2 - sqrt(2) * c2 / 2;
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < c1; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d1 = p[i].dist(p[j]);
					if (max1 < d1)
					{
						max1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = c1; i < c2; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d2 = p[i].dist(p[j]);
					if (max2 < d2)
					{
						max2 = d2;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = c2; i < c3; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d3 = p[i].dist(p[j]);
					if (max3 < d3)
					{
						max3 = d3;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = c3; i < n - 1; ++i)
			{
				for (int j = i; j < n; ++j)
				{
					d4 = p[i].dist(p[j]);
					if (max4 < d4)
					{
						max4 = d4;
					}
				}
			}
		}
	}
	max1 = (max1 > max2) ? max1 : max2;
	max1 = (max1 > max3) ? max1 : max3;
	return (max1 > max4) ? max1 : max4;
}

void diameter_pf(int n)
{

	filling_p(10000);
	double maxx = 0;
	double d = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (maxx < d)
			{
				maxx = d;
			}
		}
	}
	cout << "diameter :" << maxx << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;
	/////////////////////////////////////////////////////////
	maxx = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (max: maxx)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (maxx < d)
			{
				maxx = d;
			}
		}
	}
	cout << "diameter :" << maxx << endl;
	cout << setprecision(6) << "Time static: " << omp_get_wtime() - t << endl;
	/////////////////////////////////////////////////////////
	maxx = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (max: maxx)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (maxx < d)
			{
				maxx = d;
			}
		}
	}
	cout << "diameter :" << maxx << endl;
	cout << setprecision(6) << "Time dynamic: " << omp_get_wtime() - t << endl;
	/////////////////////////////////////////////////////////
	maxx = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (max: maxx)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (maxx < d)
			{
				maxx = d;
			}
		}
	}
	cout << "diameter :" << maxx << endl;
	cout << setprecision(6) << "Time guided: " << omp_get_wtime() - t << endl;
}

