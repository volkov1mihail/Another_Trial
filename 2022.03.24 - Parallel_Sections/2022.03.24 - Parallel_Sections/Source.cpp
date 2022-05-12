#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include<iomanip>



struct Point
{
	double x;
	double y;
	double z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};
};


#define N 100000000
double PI = 3.14159265;
double x[100000000];
Point p[10000];

void sin();
void sin_2();
void pi();
void pi_2();
int prime_numbers(int);
int prime_numbers_2(int);
double diameter();



double distance(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

using namespace std;
int main()
{
	srand(time(0));
	//sin();
	//sin_2();
	//pi();
	//pi_2();
	//int n = prime_numbers(1000000);
	//n = prime_numbers_2(1000000);
	double d = diameter();
	return 0;
}


void sin()
{
	double t = omp_get_wtime();
	for (int i = 0; i < N; ++i)
	{
		x[i] = sin(PI * i / (2.0 * N));

	}
	cout << "sin::" << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;



	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < N / 2; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
#pragma omp section
		{
			for (int i = N / 2; i < N; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
	}
	cout << "Time 2:: " << omp_get_wtime() - t << endl;



	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < N / 4; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
#pragma omp section
		{
			for (int i = N / 4; i < N / 2; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
#pragma omp section
		{
			for (int i = N / 2; i < 3 * N / 4; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
#pragma omp section
		{
			for (int i = 3 * N / 4; i < N; ++i)
			{
				x[i] = sin(PI * i / (2.0 * N));
			}
		}
	}
	cout << "Time 4:: " << omp_get_wtime() - t << endl;

}

void sin_2()
{
	double t = omp_get_wtime();
#pragma omp parallel for schedule (static)
	for (int i = 0; i < N; ++i)
	{
		x[i] = sin(PI * i / (2.0 * N));

	}
	cout << "Time static:: " << omp_get_wtime() - t << endl;


	t = omp_get_wtime();
#pragma omp parallel for schedule (dynamic, 1000)
	for (int i = 0; i < N; ++i)
	{
		x[i] = sin(PI * i / (2.0 * N));
	}
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;


	t = omp_get_wtime();
#pragma omp parallel for schedule (guided, 1000)
	for (int i = 0; i < N; ++i)
	{
		x[i] = sin(PI * i / (2.0 * N));
	}
	cout << "Time guided:: " << omp_get_wtime() - t << endl;
}


void pi()
{
	long double pi = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < N; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	}
	pi = pi * 4 / N;
	cout << "pi::" << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	cout << setprecision(6) << "Time 1:: " << omp_get_wtime() - t << endl;


	pi = 0;
	double tt = 0;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (int i = 1; i <= N / 2; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}
		}
#pragma omp section
		{
			for (int i = N / 2 + 1; i <= N; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}
		}
	}
	pi = pi * 4 / N;
	cout << "Time 2:: " << omp_get_wtime() - t << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (int i = 0; i < N / 4; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}

		}
#pragma omp section
		{
			for (int i = N / 4; i < N / 2; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}

		}
#pragma omp section
		{
			for (int i = N / 2; i < 3 * N / 4; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}

		}
#pragma omp section
		{
			for (int i = 3 * N / 4; i <= N; ++i)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
			}

		}
	}
	pi = pi * 4 / N;
	cout << "Time 4:: " << omp_get_wtime() - t << endl;
}


void pi_2()
{

	long double pi = 0;
	double t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: pi)
	for (int i = 0; i < N; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	}
	pi = pi * 4 / N;
	cout << setprecision(6) << "Time static:: " << omp_get_wtime() - t << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: pi)
	for (int i = 0; i < N; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	}
	pi = pi * 4 / N;
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: pi)
	for (int i = 0; i < N; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	}
	pi = pi * 4 / N;
	cout << "Time guided:: " << omp_get_wtime() - t << endl;
}


bool prime(int a)
{
	for (int i = 3; i * i <= a; i += 2)
	{
		if (a % i == 0)
		{
			return false;
		}
	}
	return true;
}


int prime_numbers(int n)
{
	int c = 1;
	double t = omp_get_wtime();
	for (int i = 3; i < n; i += 2)
	{
		c = prime(i) ? c + 1 : c;

	}
	cout << "Prime numbers::" << endl << "c =" << c << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:c)
	{
#pragma omp section
		{
			for (int i = 3; i <= n; i += 4)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 4)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
	}
	cout << "Time 2:: " << omp_get_wtime() - t << endl;

	c = 1;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:c)
	{
#pragma omp section
		{
			for (int i = 3; i <= n; i += 8)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 8)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
#pragma omp section
		{
			for (int i = 7; i <= n; i += 8)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
#pragma omp section
		{
			for (int i = 9; i <= n; i += 8)
			{
				if (prime(i))
				{
					++c;
				}
			}
		}
	}
	cout << "Time 4:: " << omp_get_wtime() - t << endl;
	return c;
}


int prime_numbers_2(int n)
{
	int c = 1;
	double t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: c)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++c;
		}
	}
	cout << "Time static:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: c)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++c;
		}
	}
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: c)
	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i))
		{
			++c;
		}
	}
	cout << "Time guided:: " << omp_get_wtime() - t << endl;
	return c;
}


double diameter()
{
	for (int i = 0; i < 10000; ++i)
	{
		p[i].x = (double)((rand() % 100)) / 100;
		p[i].y = (double)((rand() % 100)) / 100;
		p[i].z = (double)((rand() % 100)) / 100;
	}
	double d = 0;
	double c = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < 9999; ++i)
	{
		for (int j = i; j < 10000; ++j)
		{
			c = distance(p[i], p[j]);
			if (d < c)
			{
				d = c;
			}
		}
	}
	cout << "Diameter:: " << d << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;


	d = 0;
	double d1 = 0;
	c = 0;
	double c1 = 0;
	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < 9999 / 2; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
					{
						d = c;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 9999 / 2; i < 9999; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
					{
						d1 = c1;
					}
				}
			}
		}
	}
	d = max(d, d1);
	cout << "Time 2:: " << omp_get_wtime() - t << endl;


	d = 0;
	d1 = 0;
	double d2 = 0;
	c = 0;
	c1 = 0;
	double c2 = 0;
	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < 9999 / 3; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
					{
						d = c;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 9999 / 3; i < 2 * 9999 / 3; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
					{
						d1 = c1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 2 * 9999 / 3; i < 9999; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d2 < c2)
					{
						d2 = c2;
					}
				}
			}
		}
	}
	cout << "Time 3:: " << omp_get_wtime() - t << endl;


	d = 0;
	d1 = 0;
	d2 = 0;
	double d3 = 0;
	c = 0;
	c1 = 0;
	c2 = 0;
	double c3 = 0;
	t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < 9999 / 4; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
					{
						d = c;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 9999 / 4; i < 9999 / 2; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
					{
						d1 = c1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 9999 / 2; i < 3 * 9999 / 4; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d2 < c2)
					{
						d2 = c2;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = 3 * 9999 / 4; i < 9999; ++i)
			{
				for (int j = i; j < 10000; ++j)
				{
					c3 = distance(p[i], p[j]);
					if (d3 < c3)
					{
						d3 = c3;
					}
				}
			}
		}
	}
	d = max(d, d1);
	d2 = max(d2, d3);
	d = max(d, d2);
	cout << "Time 4:: " << omp_get_wtime() - t << endl;
	return d;
}


double diameter_2(int n)
{

	double max = 0;
	double d = 0;
	double t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = distance(p[i], p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "Time static:: " << omp_get_wtime() - t << endl;


	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = distance(p[i], p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;



	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = distance(p[i], p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "Time guided:: " << omp_get_wtime() - t << endl;
}