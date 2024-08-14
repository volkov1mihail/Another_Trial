#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <iomanip>
#include <ctime>
#include <clocale>

using namespace std;

void bisection(pair<double, double>& p, double e);
void Newton(pair<double, double>& p, double e);
void modNewton(pair<double, double>& p, double e);
void secant(pair<double, double>& p, double e);

double function(double x)
{
	//return pow(2, -x) - sin(x);
	double x2 = x * x;
	return x2 * (x2 / 3 + sqrt(2) * sin(x)) - sqrt(3) / 19;
}
double f_deriv(double x)
{
	//return -pow(2, -x) * log(2) - cos(x);
	double x2 = x * x;
	return 4 * x2 * x / 3 + sqrt(2) * x2 * cos(x) + 2 * sqrt(2) * x * sin(x);
}
double s_deriv(double x)
{
	//return pow(2, -x) * log(2) * log(2) + sin(x);
	double x2 = x * x;
	return 4 * x2 - sqrt(2) * (x2 - 2) * sin(x) + 4 * sqrt(2) * x * cos(x);
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << "ЧИСЛЕННЫЕ МЕТОДЫ РЕШЕНИЯ НЕЛИНЕЙНЫХ УРАВНЕНИЙ" << endl;
	int  N = 0;
	double a = 0;
	double b = 0;
	double e = 0;
	double h = 0;
	cout << setprecision(18) << "Введите значение A" << endl;
	cin >> a;
	cout << "Ведите значение B" << endl;
	cin >> b;
	cout << "Ведите значение N" << endl;
	cin >> N;
	cout << "Ведите значение e" << endl;
	cin >> e;
	cout << "Исходные параметры: [A,B] = [" << a << "," << b << "], f(x) = pow(2,-x)-sin(x), e = " << e << "." << endl;
	h = (b - a) / N;
	double x1 = a;
	double x2 = x1 + h;
	double y2;
	double y1 = function(x1);
	vector < pair <double, double>> v;
	pair<double, double> p;
	while (x2 <= b)
	{
		y2 = function(x2);
		if (y1 * y2 < 0)
		{
			cout << "[a" << v.size() << ",b" << v.size() << "]=[" << x1 << "," << x2 << "]" << endl;
			p.first = x1;
			p.second = x2;
			v.push_back(p);
		}
		x1 += h;
		x2 += h;
		y1 = y2;
	}
	cout << "Количество отрезков перемены знака равно " << v.size() << endl << endl;

	cout << "Бисекция:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		bisection(v[i], e);
	}
	cout << endl << "Метод Ньютона:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		Newton(v[i], e);
	}
	cout << endl << "Модифицированный метод Ньютона:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		modNewton(v[i], e);
	}
	cout << endl << "Метод секущих:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		secant(v[i], e);
	}
	return 0;
}


void bisection(pair<double, double>& p, double e)
{
	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
	double a = p.first;
	double b = p.second;
	double c = 0;
	int i = 0;
	while (b - a > 2 * e)
	{
		c = (a + b) / 2;
		function(a)* function(c) <= 0 ? b = c : a = c;
		++i;
	}
	c = (a + b) / 2;
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
}

void Newton(pair<double, double>& p, double e)
{
	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
	double x0 = (p.first + p.second) / 2;
	int i = 1;
	double x1 = x0 - function(x0) / f_deriv(x0);
	while (abs(x1 - x0) > 2 * e)
	{
		x0 = x1;
		x1 = x0 - function(x0) / f_deriv(x0);
		++i;
		if (i > 1000000)
		{
			cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
			break;
		}
	}
	if (i <= 1000000)
	{
		double c = (x1 + x0) / 2;
		cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
	}
}


void modNewton(pair<double, double>& p, double e)
{
	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
	double x0 = (p.first + p.second) / 2;
	int i = 1;
	double a = 1 / f_deriv(x0);
	double x1 = x0 - function(x0) * a;
	while (abs(x1 - x0) > 2 * e)
	{

		x0 = x1;
		x1 = x0 - function(x0) * a;
		++i;
		if (i > 1000000)
		{
			cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
			break;
		}
	}
	if (i <= 1000000)
	{
		double c = (x1 + x0) / 2;
		cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
	}
}


void secant(pair<double, double>& p, double e)
{
	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
	double x0 = p.first;
	double x1 = p.second;
	double g = function(x1);
	double x2 = x1 - (x1 - x0) * g / (g - function(x0));
	int i = 2;
	while (abs(x2 - x1) > e)
	{
		x0 = x1;
		x1 = x2;
		x2 = x1 - (x1 - x0) * function(x1) / (function(x1) - function(x0));
		++i;
	}
	double c = (x2 + x1) / 2;
	cout << "xm = " << c << ",  d = " << abs(x2 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
}