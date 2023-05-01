#include <iostream>
#include <cmath>
#include <iomanip>
#include <math.h>
using namespace std;

double coeff[4]{ 0 };

double zero()
{
	return coeff[0];
}

double first_deg(double x)
{
	return coeff[0] * x + coeff[1];
}

double second_deg(double x)
{
	return coeff[0] * x * x + coeff[1] * x + coeff[2];
}

double third_deg(double x)
{
	return coeff[0] * x * x * x + coeff[1] * x * x + coeff[2] * x + coeff[3];
}

double func(double x)
{
	return x * x;
}

double antideriv(double x)
{
	return x * x * x / 3;
}

double real_value(double a, double b, int k)
{
	switch (k)
	{
	case 1:
		return cos(a) - cos(b);
	case 2:
		return sin(b) - sin(a);
	case 3:
		return b * (log(b) - 1) - a * (log(a) - 1);
	case 4:
		return exp(b) - exp(a);
	case 5:
		return antideriv(b) - antideriv(a);
	case 6:
		return coeff[0] * (b - a);
	case 7:
		return (b * b - a * a) * coeff[0] / 2 + (b - a) * coeff[1];
	case 8:
		return (b * b * b - a * a * a) * coeff[0] / 3 + (b * b - a * a) * coeff[1] / 2 + (b - a) * coeff[2];
	case 9:
		return (b * b * b * b - a * a * a * a) * coeff[0] / 4 + (b * b * b - a * a * a) * coeff[1] / 3 + (b * b - a * a) * coeff[2] / 2 + (b - a) * coeff[3];
	}
	return 0;
}

double choice(double x, int k)
{
	switch (k)
	{
	case 1:
		return sin(x);
	case 2:
		return cos(x);
	case 3:
		return log(x);
	case 4:
		return exp(x);
	case 5:
		return func(x);
	case 6:
		return zero();
	case 7:
		return first_deg(x);
	case 8:
		return second_deg(x);
	case 9:
		return third_deg(x);
	}
	return 0;
}

double error(double a, double b, int k, int m)
{
	switch (k)
	{
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		return 1 / a;
	case 4:
		return exp(b);
	case 5:
		return 0;
	case 6:
		return 0;
	case 7:
		return abs(coeff[0]);
	case 8:
		return fmax(abs(2 * coeff[0] * a + coeff[1]), abs(2 * coeff[0] * b + coeff[1]));
	case 9:
		double t = -coeff[1] / 2 / coeff[0];
		double y1 = abs(3 * coeff[0] * t * t + 2 * coeff[1] * t + coeff[2]);
		double y2 = abs(3 * coeff[0] * a * a + 2 * coeff[1] * a + coeff[2]);
		double y3 = abs(3 * coeff[0] * b * b + 2 * coeff[1] * b + coeff[2]);
		return fmax(fmax(y1, y2), y3);
	}
	return 0;
}

double error2(double a, double b, int k, int m)
{
	switch (k)
	{
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		return 1 / (a * a);
	case 4:
		return exp(b);
	case 5:
		return 0;
	case 6:
		return 0;
	case 7:
		return 0;
	case 8:
		return abs(2 * coeff[0]);
	case 9:
		return fmax(abs(6 * coeff[0] * a + 2 * coeff[1]), abs(6 * coeff[0] * b + 2 * coeff[1]));
	}
	return 0;
}

double error4(double a, double b, int k, int m)
{
	switch (k)
	{
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		return 6 / (a * a * a * a);
	case 4:
		return exp(b);
	case 5:
		return 0;
	case 6:
		return 0;
	case 7:
		return 0;
	case 8:
		return 0;
	case 9:
		return abs(6 * coeff[0]);
	}
	return 0;
}

double W(double a, double b, int k, int m)
{
	double s = 0;
	double h = (b - a) / m;
	for (int j = 1; j < m; ++j)
	{
		a += h;
		s += choice(a, k);
	}
	return s;
}

double Q(double a, double b, int k, int m)
{
	double s = 0;
	double h = (b - a) / m;
	a += h / 2;
	for (int j = 0; j < m; ++j)
	{
		s += choice(a, k);
		a += h;
	}
	return s;
}

double left_rectangle(double a, double b, int k, int m, double W)
{
	double result = (m == 1 ? (b - a) * choice(a, k) : (b - a) * (choice(a, k) + W) / m);
	cout << "Формула левого прямоугольника: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
	if (m > 1)
	{
		cout << "Теоретическая оценка погрешности: ";
		if (k == 1 or k == 2)
			cout << "предполагается max|f'(x)| = 1,   ";
		cout << (b - a) * (b - a) * error(a, b, k, m) / 2 / m << endl;
	}
	return result;
}

double right_rectangle(double a, double b, int k, int m, double W)
{
	double result = m == 1 ? (b - a) * choice(b, k) : (b - a) * (choice(b, k) + W) / m;
	cout << "Формула правого прямоугольника: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
	if (m > 1)
	{
		cout << "Теоретическая оценка погрешности: ";
		if (k == 1 or k == 2)
			cout << "предполагается max|f'(x)| = 1,   ";
		cout << (b - a) * (b - a) * error(a, b, k, m) / 2 / m << endl;
	}
	return result;
}

double middle_rectangle(double a, double b, int k, int m, double Q)
{
	double result = m == 1 ? (b - a) * choice((a + b) / 2, k) : (b - a) * Q / m;
	cout << "Формула среднего прямоугольника: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
	if (m > 1)
	{
		cout << "Теоретическая оценка погрешности: ";
		if (k == 1 or k == 2)
			cout << "предполагается max|f'(x)| = 1,   ";
		cout << (b - a) * (b - a) * (b - a) * error2(a, b, k, m) / 24 / m / m << endl;;
	}
	return result;
}

double trapeze(double a, double b, int k, int m, double W)
{
	double result;
	if (m == 1)
		result = (b - a) * (choice(a, k) + choice(b, k)) / 2;
	else
		result = (b - a) * (choice(a, k) + choice(b, k) + 2 * W) / 2 / m;
	cout << "Формула трапеции: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
	if (m > 1)
	{
		cout << "Теоретическая оценка погрешности: ";
		if (k == 1 or k == 2)
			cout << "предполагается max|f'(x)| = 1,   ";
		cout << (b - a) * (b - a) * (b - a) * error2(a, b, k, m) / 12 / m / m << endl;;
	}
	return result;
}

double Simpson(double a, double b, int k, int m, double W, double Q)
{
	double result;
	if (m == 1)
		result = (b - a) * (choice(a, k) + 4 * choice((a + b) / 2, k) + choice(b, k)) / 6;
	else
		result = (b - a) * (choice(a, k) + choice(b, k) + 2 * W + 4 * Q) / 6 / m;
	cout << "Формула Симпсона: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
	if (m > 1)
	{
		cout << "Теоретическая оценка погрешности: ";
		if (k == 1 or k == 2)
			cout << "предполагается max|f'(x)| = 1,   ";
		cout << (b - a) * (b - a) * (b - a) * (b - a) * (b - a) * error4(a, b, k, m) / 2880 / m / m / m / m << endl;
	}
	return result;
}

void three_eighths(double a, double b, int k, int m)
{
	double result = (b - a) * (choice(a, k) + 3 * (choice(a + (b - a) / 3, k) + choice(a + 2 * (b - a) / 3, k)) + choice(b, k)) / 8;
	cout << "Формула 3/8: " << result << endl;
	cout << "Абсолютная фактическая погрешность |J-J(h)| = " << abs(real_value(a, b, k) - result) << endl;
}

void polynomials(double a, double b, int m)
{
	cout << "Нулевая степень:" << endl;
	int k = 6;
	double w = W(a, b, k, m);
	double q = Q(a, b, k, m);

	cout << "m = 1" << endl;
	left_rectangle(a, b, k, 1, 0);
	right_rectangle(a, b, k, 1, 0);
	middle_rectangle(a, b, k, 1, 0);
	trapeze(a, b, k, 1, 0);
	Simpson(a, b, k, 1, 0, 0);
	three_eighths(a, b, k, 1);

	cout << endl << "m = " << m << endl;
	left_rectangle(a, b, k, m, w);
	right_rectangle(a, b, k, m, w);
	middle_rectangle(a, b, k, m, q);
	trapeze(a, b, k, m, w);
	Simpson(a, b, k, m, w, q);

	cout << endl << "Первая степень:" << endl;
	k = 7;
	w = W(a, b, k, m);
	q = Q(a, b, k, m);

	cout << "m = 1" << endl;
	left_rectangle(a, b, k, 1, 0);
	right_rectangle(a, b, k, 1, 0);
	middle_rectangle(a, b, k, 1, 0);
	trapeze(a, b, k, 1, 0);
	Simpson(a, b, k, 1, 0, 0);
	three_eighths(a, b, k, 1);

	cout << endl << "m = " << m << endl;
	left_rectangle(a, b, k, m, w);
	right_rectangle(a, b, k, m, w);
	middle_rectangle(a, b, k, m, q);
	trapeze(a, b, k, m, w);
	Simpson(a, b, k, m, w, q);

	cout << endl << "Вторая степень:" << endl;
	k = 8;
	w = W(a, b, k, m);
	q = Q(a, b, k, m);

	cout << "m = 1" << endl;
	left_rectangle(a, b, k, 1, 0);
	right_rectangle(a, b, k, 1, 0);
	middle_rectangle(a, b, k, 1, 0);
	trapeze(a, b, k, 1, 0);
	Simpson(a, b, k, 1, 0, 0);
	three_eighths(a, b, k, 1);

	cout << endl << "m = " << m << endl;
	left_rectangle(a, b, k, m, w);
	right_rectangle(a, b, k, m, w);
	middle_rectangle(a, b, k, m, q);
	trapeze(a, b, k, m, w);
	Simpson(a, b, k, m, w, q);

	cout << endl << "Третья степень:" << endl;
	k = 9;
	w = W(a, b, k, m);
	q = Q(a, b, k, m);

	cout << "m = 1" << endl;
	left_rectangle(a, b, k, 1, 0);
	right_rectangle(a, b, k, 1, 0);
	middle_rectangle(a, b, k, 1, 0);
	trapeze(a, b, k, 1, 0);
	Simpson(a, b, k, 1, 0, 0);
	three_eighths(a, b, k, 1);

	cout << endl << "m = " << m << endl;
	left_rectangle(a, b, k, m, w);
	right_rectangle(a, b, k, m, w);
	middle_rectangle(a, b, k, m, q);
	trapeze(a, b, k, m, w);
	Simpson(a, b, k, m, w, q);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Приближённое вычисление интеграла по квадратурным формулам" << endl;
	int m, l;

	double a, b;

	cout << "Введите левый конец промежутка A" << endl;
	cin >> a;
	cout << "Введите правый конец промежутка B" << endl;
	cin >> b;
	cout << "Введите m - число промежутков деления в задании 4.2" << endl;
	cin >> m;

	double memory[10]{ 0 };
	int k;
	cout << endl << "Выберите, на примере какой функции вычислить квадратурные формулы:" << endl;
	cout << "1 - sin(x)" << endl << "2 - cos(x)" << endl << "3 - ln(x)" << endl << "4 - exp(x)" << endl << "5 - func(x), хранящаяся в коде программы" << endl;
	cin >> k;

	cout << "Точное значение интеграла:   " << real_value(a, b, k) << endl;

	cout << "Задание 4.1" << endl << endl;
	left_rectangle(a, b, k, 1, 0);
	right_rectangle(a, b, k, 1, 0);
	middle_rectangle(a, b, k, 1, 0);
	trapeze(a, b, k, 1, 0);
	Simpson(a, b, k, 1, 0, 0);
	three_eighths(a, b, k, 1);

	cout << endl << "Задание 4.2" << endl << endl;
	double w = W(a, b, k, m);
	double q = Q(a, b, k, m);
	memory[0] = left_rectangle(a, b, k, m, w);
	memory[1] = right_rectangle(a, b, k, m, w);
	memory[2] = middle_rectangle(a, b, k, m, q);
	memory[3] = trapeze(a, b, k, m, w);
	memory[4] = Simpson(a, b, k, m, w, q);


	while (coeff[0] == 0 or coeff[1] == 0 or coeff[2] == 0 or coeff[3] == 0)
	{
		coeff[0] = ((double)(rand() % 1000)) / 100;
		coeff[1] = ((double)(rand() % 1000)) / 100;
		coeff[2] = ((double)(rand() % 1000)) / 100;
		coeff[3] = ((double)(rand() % 1000)) / 100;
	}

	cout << endl << "Задание 4.3" << endl;
	cout << "Введите l - во сколько раз нужно увеличить параметр m для задания 4.3" << endl;
	cin >> l;
	cout << endl;

	//m *= l;
	w = W(a, b, k, m*l);
	q = Q(a, b, k, m*l);
	memory[5] = left_rectangle(a, b, k, m*l, w);
	memory[6] = right_rectangle(a, b, k, m*l, w);
	memory[7] = middle_rectangle(a, b, k, m*l, q);
	memory[8] = trapeze(a, b, k, m*l, w);
	memory[9] = Simpson(a, b, k, m*l, w, q);

	memory[0] = (l * memory[5] - memory[0]) / (l - 1);
	memory[1] = (l * memory[6] - memory[1]) / (l - 1);
	memory[2] = (l * l * memory[7] - memory[2]) / (l * l - 1);
	memory[3] = (l * l * memory[8] - memory[3]) / (l * l - 1);
	memory[4] = (l * l * l * l * memory[9] - memory[4]) / (l * l * l * l - 1);

	cout << endl << "Уточнение по формуле Рунге" << endl << endl;
	cout << "Формула левого треугольника:   " << memory[0] << endl;
	cout << "Абсолютная фактическая погрешность:    " << abs(memory[0] - real_value(a, b, k)) << endl << endl;
	cout << "Формула правого треугольника:   " << memory[1] << endl;
	cout << "Абсолютная фактическая погрешность:    " << abs(memory[1] - real_value(a, b, k)) << endl << endl;
	cout << "Формула среднего треугольника:   " << memory[2] << endl;
	cout << "Абсолютная фактическая погрешность:    " << abs(memory[2] - real_value(a, b, k)) << endl << endl;
	cout << "Формула трапеции:   " << memory[3] << endl;
	cout << "Абсолютная фактическая погрешность:    " << abs(memory[3] - real_value(a, b, k)) << endl << endl;
	cout << "Формула Симпсона:   " << memory[4] << endl;
	cout << "Абсолютная фактическая погрешность:    " << abs(memory[4] - real_value(a, b, k)) << endl << endl;

	int t = 0;
	cout << endl << "Чтобы проверить АСТ квадратурных формул на многочленах, введите 1" << endl;
	cout << "Чтобы закончить работу программы, введите 0" << endl;
	cin >> t;
	cout << endl;
	m *= l;
	if (t == 1)
		polynomials(a, b, m /l);

	return 0;
}