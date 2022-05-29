#include <iostream>
#include <cstdlib>
#include <omp.h>


#include<iomanip>


using namespace std;

double f(double x);

double integr(float a, float b, double f(double));

double integral(float a, float b, double f(double));

double integral_par(float a, float b, double f(double));

int main()
{

	cout << integr(1, 5, f) << endl;

	double t = omp_get_wtime();
	cout << "integral(1, 5, f) = " << integral(1, 5, f) << endl;
	cout << setprecision(6) << "Time line: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp single
		{
			cout << "integral(1, 5, f)_par = " << integral_par(1, 5, f) << endl;
		}
	}
	cout << setprecision(6) << "Time paralel: " << omp_get_wtime() - t << endl;



	return EXIT_SUCCESS;
}

double f(double x)
{
	return 1 / (1 + x * x);
}

double integr(float a, float b, double f(double))
{
	double sum = 0;
	double dx = (b - a) / 10;
	for (int i = 0; i < 10; ++i)
	{
		sum += dx * (f(a + i * dx) + f(a + (i + 1) * dx)) / 2;
	}
	return sum;
}

double integral(float a, float b, double f(double))
{
	double sum = integr(a, b, f);

	if (abs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.00000000001)
	{
		sum = integral(a, (a + b) / 2, f) + integral((a + b) / 2, b, f);
	}
	return sum;
}

double integral_par(float a, float b, double f(double))
{
	double sum = integr(a, b, f);
	double sum1 = 0;
	double sum2 = 0;
	if (abs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.0000000001)
	{
#pragma omp task shared(sum1)
		sum1 = integral(a, (a + b) / 2, f);
#pragma omp task shared (sum2)
		sum2 = integral((a + b) / 2, b, f);
#pragma omp taskwait
		sum = sum1 + sum2;
	}
	return sum;
}