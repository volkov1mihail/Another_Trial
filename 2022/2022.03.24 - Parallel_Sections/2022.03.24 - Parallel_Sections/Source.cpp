#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include<iomanip>
//Задача, используя параллельные потоки, вычислить синус натуральных чисел от 0 до PI/2 с шагом PI/(2 * N) и измерить затраченное на это время
//Требуется вычислить число PI с высокой точностью с помощью формулы PI = 4 * arctg(1)
//Требуется сосчитать количество простых чисел от 2 до 1000000 (верхнюю границу можно менять)
//Для случайно выбранных 10000 точек (x,y,z) требуется вычислить максимальное расстояние между ними
//Для каждой отдельной задачи нужно последовательно использовать 1 поток, 2 потока, 4 потока и методы static, dynamic и guided из библиотеки omp.h
//Время, потраченное на выполнение каждой задачи, выводится на экран для возможности сравнения эффективности разных методов распараллеливания цикла for

struct Point																//Стуктура, представляющая собой точку в пространстве с координатами (x,y,z)
{
	double x;
	double y;
	double z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};
};


#define N 100000000                         //количество итераций
double PI = 3.14159265;											//Значение числа PI, используемое для вычисления синусов
double SIN[100000000];											//Массив, в который записываются полученные значения синусов
Point p[10000];															//Массив случайных точек в пространстве

void sin();																	//Рассчет синусов, используя 1, 2 и 4 потока
void sin_2();																//Рассчет синусов, используя метод static, dynamic и guided
void pi();																	//Рассчет числа PI, используя 1, 2 и 4 потока
void pi_2();																//Рассчет числа PI, используя метод static, dynamic и guided
int prime_numbers(int);											//Рассчет количества простых чисел, используя 1, 2 и 4 потока
int prime_numbers_2(int);										//Рассчет количества простых чисел, используя метод static, dynamic и guided
double diameter();													//Рассчет расстояния до точек, используя 1, 2 и 4 потока
//double diameter_2(int n);										//Рассчет расстояния до точек, используя метод static, dynamic и guided

double distance(Point a, Point b)						//Функция, вычисляющая расстояние от точки a до точки b
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

using namespace std;
int main()
{
	srand(time(0));														//Гарантия того, что сгенерированные точки в пространстве не будут повторятся при повторном запуске программы
	sin();																		//Рассчет синусов, используя 1, 2 и 4 потока
	sin_2();																	//Рассчет синусов, используя метод static, dynamic и guided
	pi();																			//Рассчет числа PI, используя 1, 2 и 4 потока
	pi_2();																		//Рассчет числа PI, используя метод static, dynamic и guided
	int n = prime_numbers(1000000);						//Рассчет количества простых чисел, используя 1, 2 и 4 потока
	n = prime_numbers_2(1000000);							//Рассчет количества простых чисел, используя метод static, dynamic и guided
	double d = diameter();										//Рассчет расстояния до точек, используя 1, 2 и 4 потока
	//d = diameter_2(10000);									//Рассчет расстояния до точек, используя метод static, dynamic и guided
	return 0;
}


void sin()																	//Рассчет синусов, используя 1, 2 и 4 потока
{
	double t = omp_get_wtime();								//Момент времени перед началом вычислений
	for (int i = 0; i < N; ++i)								//Один поток
		SIN[i] = sin(PI * i / (2.0 * N));
	cout << "sin::" << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;				//Время, затраченное на выполнение вычислений


	t = omp_get_wtime();											//Момент времени перед началом вычислений
#pragma omp parallel sections								//Два потока
	{
#pragma omp section													//Поток #1
		{
			for (int i = 0; i < N / 2; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
#pragma omp section													//Поток #2
		{
			for (int i = N / 2; i < N; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
	}
	cout << "Time 2:: " << omp_get_wtime() - t << endl;				//Время, затраченное на выполнение вычислений


	t = omp_get_wtime();											//Момент времени перед началом вычислений
#pragma omp parallel sections								//Четыре потока
	{
#pragma omp section													//Поток #1
		{
			for (int i = 0; i < N / 4; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
#pragma omp section													//Поток #2
		{
			for (int i = N / 4; i < N / 2; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
#pragma omp section													//Поток #3
		{
			for (int i = N / 2; i < 3 * N / 4; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
#pragma omp section													//Поток #4
		{
			for (int i = 3 * N / 4; i < N; ++i)
				SIN[i] = sin(PI * i / (2.0 * N));
		}
	}
	cout << "Time 4:: " << omp_get_wtime() - t << endl;				//Время, затраченное на выполнение вычислений
}

void sin_2()																								//Рассчет синусов, используя метод static, dynamic и guided
{
	double t = omp_get_wtime();																//Момент времени перед началом вычислений
#pragma omp parallel for schedule (static)									//Метод static
	for (int i = 0; i < N; ++i)
		SIN[i] = sin(PI * i / (2.0 * N));
	cout << "Time static:: " << omp_get_wtime() - t << endl;	//Время, затраченное на выполнение вычислений


	t = omp_get_wtime();																			//Момент времени перед началом вычислений
#pragma omp parallel for schedule (dynamic, 1000)						//Метод dynamic c 1000 итерациями на запрос потока
	for (int i = 0; i < N; ++i)
		SIN[i] = sin(PI * i / (2.0 * N));
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;	//Время, затраченное на выполнение вычислений


	t = omp_get_wtime();																			//Момент времени перед началом вычислений
#pragma omp parallel for schedule (guided, 1000)						//Метод guided с минимумом в 1000 итераций на запрос потока
	for (int i = 0; i < N; ++i)
		SIN[i] = sin(PI * i / (2.0 * N));
	cout << "Time guided:: " << omp_get_wtime() - t << endl;	//Время, затраченное на выполнение вычислений
}

void pi()																																		//Рассчет числа PI, используя 1, 2 и 4 потока
{
	long double pi = 0;
	double t = omp_get_wtime();																								//Момент времени перед началом вычислений
	for (int i = 0; i < N; ++i)																								//Один поток
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	pi = pi * 4 / N;
	cout << "pi::" << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	cout << setprecision(6) << "Time 1:: " << omp_get_wtime() - t << endl;		//Время, затраченное на выполнение вычислений


	pi = 0;
	double tt = 0;
	t = omp_get_wtime();																											//Момент времени перед началом вычислений
#pragma omp parallel sections reduction(+:pi)																//Два потока
	{
#pragma omp section																													//Поток #1
		{
			for (int i = 1; i <= N / 2; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
#pragma omp section																													//Поток #2
		{
			for (int i = N / 2 + 1; i <= N; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
	}
	pi = pi * 4 / N;
	cout << "Time 2:: " << omp_get_wtime() - t << endl;												//Время, затраченное на выполнение вычислений


	pi = 0;
	t = omp_get_wtime();																											//Момент времени перед началом вычислений
#pragma omp parallel sections reduction(+:pi)																//Четыре потока
	{
#pragma omp section																													//Поток #1
		{
			for (int i = 0; i < N / 4; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
#pragma omp section																													//Поток #2
		{
			for (int i = N / 4; i < N / 2; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
#pragma omp section																													//Поток #3
		{
			for (int i = N / 2; i < 3 * N / 4; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
#pragma omp section																													//Поток #4
		{
			for (int i = 3 * N / 4; i <= N; ++i)
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
		}
	}
	pi = pi * 4 / N;
	cout << "Time 4:: " << omp_get_wtime() - t << endl;												//Время, затраченное на выполнение вычислений
}

void pi_2()																																	//Рассчет числа PI, используя метод static, dynamic и guided
{

	long double pi = 0;
	double t = omp_get_wtime();																								//Момент времени перед началом вычислений
#pragma omp parallel for schedule(static) reduction (+: pi)									//Метод static
	for (int i = 0; i < N; ++i)
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	pi = pi * 4 / N;
	cout << setprecision(6) << "Time static:: " << omp_get_wtime() - t << endl;		//Время, затраченное на выполнение вычислений


	pi = 0;
	t = omp_get_wtime();																											//Момент времени перед началом вычислений
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: pi)					//Метод dynamic c 1000 итерациями на запрос потока
	for (int i = 0; i < N; ++i)
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	pi = pi * 4 / N;
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;									//Время, затраченное на выполнение вычислений


	pi = 0;
	t = omp_get_wtime();																											//Момент времени перед началом вычислений
#pragma omp parallel for schedule(guided, 1000) reduction (+: pi)						//Метод guided с минимумом в 1000 итераций на запрос потока
	for (int i = 0; i < N; ++i)
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	pi = pi * 4 / N;
	cout << "Time guided:: " << omp_get_wtime() - t << endl;									//Время, затраченное на выполнение вычислений
}

bool prime(int a)																						//Функция, определяющая, является ли число a простым
{
	for (int i = 3; i * i <= a; i += 2)
		if (a % i == 0)
			return false;

	return true;
}

int prime_numbers(int n)																		//Рассчет количества простых чисел, используя 1, 2 и 4 потока
{
	int c = 1;																								//c - счетчик простых чисел. c = 1, т.к. проверка будет проводится с числа 3, пропуская
	double t = omp_get_wtime();																//первое простое число 2
	for (int i = 3; i < n; i += 2)														//Один поток
		c = prime(i) ? c + 1 : c;
	cout << "Prime numbers::" << endl << "c =" << c << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:c)								//Два потока
	{
#pragma omp section
		{
			for (int i = 3; i <= n; i += 4)
				if (prime(i))
					++c;
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 4)
				if (prime(i))
					++c;
		}
	}
	cout << "Time 2:: " << omp_get_wtime() - t << endl;

	c = 1;
	t = omp_get_wtime();
#pragma omp parallel sections reduction(+:c)								//Четыре потока
	{
#pragma omp section
		{
			for (int i = 3; i <= n; i += 8)
				if (prime(i))
					++c;
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 8)
				if (prime(i))
					++c;
		}
#pragma omp section
		{
			for (int i = 7; i <= n; i += 8)
				if (prime(i))
					++c;
		}
#pragma omp section
		{
			for (int i = 9; i <= n; i += 8)
				if (prime(i))
					++c;
		}
	}
	cout << "Time 4:: " << omp_get_wtime() - t << endl;
	return c;
}

int prime_numbers_2(int n)																				//Рассчет количества простых чисел, используя метод static, dynamic и guided
{
	int c = 1;																											//c - счетчик простых чисел. c = 1, т.к. проверка будет проводится с числа 3, пропуская
	double t = omp_get_wtime();																			//первое простое число 2
#pragma omp parallel for schedule(static, 10) reduction (+: c)		//Метод static
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
			++c;
	cout << "Time static:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: c)	//Метод dynamic c 1000 итерациями на запрос потока
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
			++c;
	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;


	c = 1;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: c)	//Метод guided с минимумом в 1000 итераций на запрос потока
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
			++c;
	cout << "Time guided:: " << omp_get_wtime() - t << endl;
	return c;
}

double diameter()																	//Рассчет расстояния до точек, используя 1, 2 и 4 потока
{
	for (int i = 0; i < 10000; ++i)									//Генерация случайных точек в пространстве
	{
		p[i].x = (double)((rand() % 100)) / 100;
		p[i].y = (double)((rand() % 100)) / 100;
		p[i].z = (double)((rand() % 100)) / 100;
	}
	double d = 0;																		//Предполагаемое максимальное расстояние между точками из массива p
	double c = 0;																		//Расстояние между двумя рассматриваемыми точками из массива p
	double t = omp_get_wtime();											//Один поток
	for (int i = 0; i < 9999; ++i)									//Фиксируется i-тая точка из массива, после чего вычисляются расстояния от нее
		for (int j = i; j < 10000; ++j)								//до всех последующий точек массива
		{
			c = distance(p[i], p[j]);
			if (d < c)																	//Если предполагаемое максимальное расстояние d оказалось меньше найденного, оно переназначается
				d = c;
		}
	cout << "Diameter:: " << d << endl;
	cout << "Time 1:: " << omp_get_wtime() - t << endl;

	//Т.к. для каждого числа i от 0 до 9999 проверяются пары j от i до 10000, равномерное распределение количества итераций
	//по ДВУМ потокам достигается при разбиении промежутка от 0 до 9999 на следующие:
	//от 0 до a - 1, от a до 9999, где a является решением уравнения:
	//(a - 1) * (10000 - a/2) = (10000 - a) * (5000 - a/2 + 1/2),
	//т.е. a = (20001 - sqrt(199980001))/2
	int a = (20001 - sqrt(199980001)) / 2;
	d = 0;
	double d1 = 0;
	c = 0;
	double c1 = 0;
	t = omp_get_wtime();														
#pragma omp parallel sections											//Два потока
	{
#pragma omp section
		{
			for (int i = 0; i < a; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
						d = c;
				}
		}
#pragma omp section
		{
			for (int i = a; i < 9999; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
						d1 = c1;
				}
		}
	}
	d = max(d, d1);																	//выбирается максимум из двух полученных значений, так как потоки проверяли разные пары точек
	cout << "Time 2:: " << omp_get_wtime() - t << endl;

	//Т.к. для каждого числа i от 0 до 9999 проверяются пары j от i до 10000, равномерное распределение количества итераций
	//по ТРЕМ потокам достигается при разбиении промежутка от 0 до 9999 на следующие: 
	//от 0 до a - 1, от a до b - 1, от b до 9999, где a и b являются решениями системы уравнений:
	//(a - 1) * (10000 - a/2) = (b - a) * (10000 - a/2 - b/2 + 1/2) = (10000 - b) * (5000 - b/2 + 1/2),
	//т.е. a = (20001 - sqrt(266640001))/2, b = (20001 - sqrt(133320001))/2
	a = (20001 - sqrt(266640001)) / 2;
	int b = (20001 - sqrt(133320001)) / 2;
	d = 0;
	d1 = 0;
	double d2 = 0;
	c = 0;
	c1 = 0;
	double c2 = 0;
	t = omp_get_wtime();
#pragma omp parallel sections											//Три потока
	{
#pragma omp section
		{
			for (int i = 0; i < a; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
						d = c;
				}
		}
#pragma omp section
		{
			for (int i = a; i < b; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
						d1 = c1;
				}
		}
#pragma omp section
		{
			for (int i = b; i < 9999; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d2 < c2)
						d2 = c2;
				}
		}
	}
	d = max(d, d1);																	//выбирается максимум из трех полученных значений, так как потоки проверяли разные пары точек
	d = max(d, d2);
	cout << "Time 3:: " << omp_get_wtime() - t << endl;

	//При разбиении цикла на ЧЕТЫРЕ потока, можно воспользоваться результатом разбиения цикла на ДВА потока
	//Так, разбив весь промежуток на части от 0 до b - 1 = (20001 - sqrt(199980001))/2 - 1 и от b до 9999 (раньше использовалось обозначение a),
	//можно далее разбить эти части на промежутки от 0 до a - 1, от a до b - 1, от b до l - 1 и от l до 9999,
	//где a = (20002 - sqrt(199980001) - sqrt(299990001 - 20000 * sqrt(199980001)))/2, l = (20001 - sqrt(99990001))/2
	a = (20002 - sqrt(199980001) - sqrt(299990001 - 20000 * sqrt(199980001))) / 2;
	b = (20001 - sqrt(199980001)) / 2;
	int l = (20001 - sqrt(99990001)) / 2;
	d = 0;
	d1 = 0;
	d2 = 0;
	double d3 = 0;
	c = 0;
	c1 = 0;
	c2 = 0;
	double c3 = 0;
	t = omp_get_wtime();
#pragma omp parallel sections											//Четыре потока
	{
#pragma omp section
		{
			for (int i = 0; i < a; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d < c)
						d = c;
				}
		}
#pragma omp section
		{
			for (int i = a; i < b; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c1 = distance(p[i], p[j]);
					if (d1 < c1)
						d1 = c1;
				}
		}
#pragma omp section
		{
			for (int i = b; i < l; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c = distance(p[i], p[j]);
					if (d2 < c2)
						d2 = c2;
				}
		}
#pragma omp section
		{
			for (int i = l; i < 9999; ++i)
				for (int j = i; j < 10000; ++j)
				{
					c3 = distance(p[i], p[j]);
					if (d3 < c3)
						d3 = c3;
				}
		}
	}
	d = max(d, d1);																	//выбирается максимум из четырех полученных значений, так как потоки проверяли разные пары точек
	d2 = max(d2, d3);
	d = max(d, d2);
	cout << "Time 4:: " << omp_get_wtime() - t << endl;
	return d;
}


//Функция diameter_2(int n) не работает, т.к. директива reduction(max: max) не поддерживается данной версией
//double diameter_2(int n)												//Рассчет расстояния до точек, используя метод static, dynamic и guided
//{
//
//	double max = 0;
//	double d = 0;
//	double t = omp_get_wtime();
//#pragma omp parallel for schedule(static, 10) reduction (max: max)
//	for (int i = 0; i < n - 1; ++i)
//	{
//		for (int j = i; j < n; ++j)
//		{
//			d = distance(p[i], p[j]);
//			if (max < d)
//			{
//				max = d;
//			}
//		}
//	}
//	cout << "Time static:: " << omp_get_wtime() - t << endl;
//
//
//	max = 0;
//	d = 0;
//	t = omp_get_wtime();
//#pragma omp parallel for schedule(dynamic, 1000) reduction (max: max)
//	for (int i = 0; i < n - 1; ++i)
//	{
//		for (int j = i; j < n; ++j)
//		{
//			d = distance(p[i], p[j]);
//			if (max < d)
//			{
//				max = d;
//			}
//		}
//	}
//	cout << "Time dynamic:: " << omp_get_wtime() - t << endl;
//
//
//
//	max = 0;
//	d = 0;
//	t = omp_get_wtime();
//#pragma omp parallel for schedule(guided, 1000) reduction (max: max)
//	for (int i = 0; i < n - 1; ++i)
//	{
//		for (int j = i; j < n; ++j)
//		{
//			d = distance(p[i], p[j]);
//			if (max < d)
//			{
//				max = d;
//			}
//		}
//	}
//	cout << "Time guided:: " << omp_get_wtime() - t << endl;
//}