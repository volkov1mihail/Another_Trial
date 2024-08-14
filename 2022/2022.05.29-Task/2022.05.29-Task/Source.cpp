#include<iostream>
#include<cstdlib>
#include<omp.h>
#include<list>
#include<iomanip>
#include<math.h>
using namespace std;
//Программа


double f(double x);																								//Функция, поддающаяся интегрированию
double integr(float a, float b, double f(double));								//Интеграл функции f(double) через формулу трапеций 
double integral(float a, float b, double f(double));							//Линейное интегрирование
double integral_t(float a, float b, double f(double));						//Параллельное интегрирование
int partition(int* A, int l, int r);															//Сортировка части массива определенным образом
void qsort(int* A, int l, int r);																	//Линейная сортировка
void qsort_t(int* A, int l, int r);																//Параллельная сортировка


int main()
{
	srand(time(NULL));
	double t = omp_get_wtime();                                     //Момент перед началом вычислений
	cout << setprecision(10) << "integral(1, 10, f) = " << integral(1, 10, f) << endl;  //Линейное интегрирование
	cout << "Time line:: " << omp_get_wtime() - t << endl;					//Время, затраченное на вычисления

	t = omp_get_wtime();                                            //Момент перед началом вычислений
#pragma omp parallel
	{
#pragma omp single
		{
			cout << "integral(1, 10, f)_t = " << integral_t(1, 10, f) << endl; //Параллельное интегрирование
		}
	}
	cout << "Time parallel: " << omp_get_wtime() - t << endl;       //Время, затраченное на вычисления


	int* A = new int[1'0000];                                       //Инициализация массива
	for (int i = 0; i < 1'0000; ++i)                                //Заполнение массива случайными числами от 0 до 10000
		A[i] = rand() % 10000;
	t = omp_get_wtime();                                            //Момент перед началом вычислений
	qsort(A, 0, 1'0000 - 1);                                        //Линейная сортировка
	cout << "Time quicksort:: " << omp_get_wtime() - t << endl;     //Время, затраченное на вычисления

	for (int i = 0; i < 1'0000; ++i)                                //Заполнение массива случайными числами от 0 до 10000
		A[i] = rand() % 10000;
	t = omp_get_wtime();                                            //Момент перед началом вычислений
#pragma omp parallel
	{
#pragma omp single
		{
			qsort_t(A, 0, 1'0000 - 1);																	//Параллельная сортировка
		}
	}
	cout << "Time quicksort_t:: " << omp_get_wtime() - t << endl;   //Время, затраченное на вычисления
	//for (int i = 0; i < 10000; ++i)																	//Вывод отсортированного массива на экран
	//	cout << A[i] << " ";
	cout << endl;

	delete[]A;                                                      //Освобождение памяти
	return EXIT_SUCCESS;
}

double f(double x)																								//Функция, поддающаяся интегрированию
{
	return 1 / (1 + x * x);
}

double integr(float a, float b, double f(double))									//Интеграл функции f(double) через формулу трапеций 
{
	double sum = 0;
	double dx = (b - a) / 10;																				//Длина шага суммирования
	for (int i = 0; i < 10; ++i)																		
		sum += dx * (f(a + i * dx) + f(a + (i + 1) * dx)) / 2;				//Площадь одной трапеции
	return sum;
}

double integral(float a, float b, double f(double))								//Линейная рекурсивная фунцкия, вычисляющая интеграл функции
{																																	//f(double) на отрезке [a;b] через формулу трапеций
	double sum = integr(a, b, f);																		//Начальное приближение
	if (abs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.000000001)	//Проверка достигнутой точности
	//Если ожидаемая точность не достигнута, рекурсивная функция integral вызывается для двух половин отрезка [a;b], тем самым увеличивая точность
		sum = integral(a, (a + b) / 2, f) + integral((a + b) / 2, b, f);
	return sum;
}

double integral_t(float a, float b, double f(double))							//Параллельная рекурсивная фунцкия, вычисляющая интеграл функции
{																																	//f(double) на отрезке [a;b] через формулу трапеций
	double sum = integr(a, b, f);																		//Начальное приближение
	double sum1 = 0;
	double sum2 = 0;
	if (abs(sum - integr(a, (a + b) / 2, f) - integr((a + b) / 2, b, f)) > 0.000000001)	//Проверка достигнутой точности
//Если ожидаемая точность не достигнута, рекурсивная функция integral_t вызывается для двух половин отрезка [a;b], тем самым увеличивая точность
	{
#pragma omp task shared(sum1)
		sum1 = integral_t(a, (a + b) / 2, f);
#pragma omp task shared (sum2)
		sum2 = integral_t((a + b) / 2, b, f);
#pragma omp taskwait
		sum = sum1 + sum2;
	}
	return sum;
}

int partition(int* A, int l, int r)																//Функция, принимающая часть массива между индексами l и r и переставляющая элементы массива так,
{																																	//чтобы слева от элемента A[r] стояли числа, не большие, а справа - не меньшие его
	int i = l - 1, j = r;																						//Индексы i и j, позволяющие менять местами элементы в массиве
	int v = A[r];																										//Значение v = A[r], относитльно которого мы хотим отсортировать часть массива
	while (true)
	{
	//Цикл while(true) увеличивает индекс i до тех пор, пока A[i] не станет >= v
	//Далее аналогичным образом индекс j уменьшается до тех пор, пока A[j] не станет <= v
	//После этого в случае, если индекс j больше индекса i и больше граничного индекса l, найденные элементы A[i] и A[j] меняются местами
	//После этой перестановки индекс процесс повторяется заново
	//Если во время уменьшения индекса j он стал <= i или j == l, выполняется последняя перестановка изначального элемента A[r] и A[i] и 
	//индес i возвращается вместе с отсортированным участком массива
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

void qsort(int* A, int l, int r)																	//Линейная сортировка массива А
{	//До тех пор, пока крайние индексы l и r не станут удовлетворять условию l >= r,
	//функция будет сортировать данную часть массива с помощью функции partition
	//После каждой такой сортировки изначальный кусок массива делится на две части, которые передаются в рекурсивную функцию qsort
	if (l >= r) return;
	int i = partition(A, l, r);
	qsort(A, l, i - 1);
	qsort(A, i + 1, r);
}

void qsort_t(int* A, int l, int r)																//Параллельная сортировка массива А
{	//До тех пор, пока крайние индексы l и r не станут удовлетворять условию l >= r,
	//функция будет сортировать данную часть массива с помощью функции partition
	//После каждой такой сортировки изначальный кусок массива делится на две части, которые передаются в рекурсивную функцию qsort_t
	if (l >= r) return;
	int i = partition(A, l, r);
#pragma omp task
	qsort_t(A, l, i - 1);
#pragma omp task
	qsort_t(A, i + 1, r);
}
