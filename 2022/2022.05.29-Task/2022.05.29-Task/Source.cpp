#include <iostream>
#include <cstdlib>
#include <omp.h>
#include<list>
#include<iomanip>
#include<math.h>


using namespace std;

double f(double x);

double integr(float a, float b, double f(double));

double integral(float a, float b, double f(double));

double integral_t(float a, float b, double f(double));

int partition(int* A, int l, int r);

void qsort(int* A, int l, int r);

void qsort_t(int* A, int l, int r);


int main()
{
    double t = omp_get_wtime();
    cout << "integral(1, 10, f) = " << integral(1, 10, f) << endl;
    cout << setprecision(6) << "Time line:: " << omp_get_wtime() - t << endl;

    t = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        {
            cout << "integral(1, 10, f)_t = " << integral_t(1, 10, f) << endl;
        }
    }
    cout << setprecision(6) << "Time parallel: " << omp_get_wtime() - t << endl;


    int* A = new int[1'0000];
    srand(time(NULL));
    for (int i = 0; i < 1'0000; ++i)
    {
        A[i] = rand() % 10000;
    }
    t = omp_get_wtime();
    qsort(A, 0, 1'0000 - 1);
    cout << setprecision(15) << "Time quicksort:: " << omp_get_wtime() - t << endl;

    for (int i = 0; i < 1'0000; ++i)
    {
        A[i] = rand() % 10000;
    }
    t = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp single
        {
            qsort_t(A, 0, 1'0000 - 1);
        }
    }
    cout << setprecision(15) << "Time quicksort_t:: " << omp_get_wtime() - t << endl;
    for (int i = 0; i < 10000; ++i)
    {
        cout << A[i] << " ";
    }
    cout << endl;


    delete[]A;
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

    if (fabs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.00000000001)
    {
        sum = integral(a, (a + b) / 2, f) + integral((a + b) / 2, b, f);
    }
    return sum;
}

double integral_t(float a, float b, double f(double))
{
    double sum = integr(a, b, f);
    double sum1 = 0;
    double sum2 = 0;
    if (fabs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.0000000001)
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

int partition(int* A, int l, int r)
{
    int i = l - 1, j = r;
    int v = A[r];
    while (true)
    {
        while (A[++i] < v);
        while (v < A[--j])
            if (j == l)
                break;
        if (i >= j)
            break;
        swap(A[i], A[j]);
    }
    swap(A[i], A[r]);
    return i;
}

void qsort(int* A, int l, int r)
{
    if (l >= r) return;
    int i = partition(A, l, r);
    qsort(A, l, i - 1);
    qsort(A, i + 1, r);
}

void qsort_t(int* A, int l, int r)
{
    if (l >= r) return;
    int i = partition(A, l, r);
#pragma omp task
    qsort(A, l, i - 1);
#pragma omp task
    qsort(A, i + 1, r);
}
