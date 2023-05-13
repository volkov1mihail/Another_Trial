#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<armadillo>

using namespace std;
using namespace arma;

vector<double> nodes;
double integral;
vector<double> rand_coeff;

double poly_integral(double a, double b, int k);
double secant(pair<double, double>& p, double e, double(*f)(double, vec), vec coeff);
double Simpson(double a, double b, int m, double(*f)(double, int), int k);
double weight(double x)
{
	return sqrt(x);
}
double moment(double x, int k)
{
	double result = weight(x);
	for (int i = 0; i < k; ++i)
		result *= x;
	return result;
}
double func(double x, int k)
{
	return sin(x);
}
double interp(double(*f)(double, int), vec coeff, int k)
{
	double result = 0;
	for (int i = 0; i < coeff.n_rows; ++i)
		result += coeff(i) * f(nodes[i], k);
	return result;
}
double integration(double x, int k)
{
	return weight(x) * func(x, k);
}
double polynomial(double x, int k)
{
	double result = rand_coeff[0];
	double c = x;
	for (int i = 1; i <= k; ++i)
	{
		result += rand_coeff[i] * c;
		c *= x;
	}
	return result;
}
double nast(double x, vec coeff)
{
	double result = coeff(0);
	double c = x;
	for (int i = 1; i < coeff.n_rows; ++i)
	{
		result += coeff(i) * c;
		c *= x;
	}
	return result + c;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Приближённое вычисление интегралов при помощи квадратурных формул Наивысшей Алгебраической Степени Точности(НАСТ)" << endl;
	double a, b;
	int N;
	int m = 10000;
	cout << "Введите левый конец промежутка интегрирования a" << endl;
	cin >> a;
	cout << "Введите правый конец промежутка интегрирования b" << endl;
	cin >> b;
	integral = Simpson(a, b, m, integration, 0);
	cout << "Точное значение интеграла: " << integral << endl;
	cout << "Введите количество узлов N" << endl;
	cin >> N;

	vec moments(2 * N);
	cout << "Моменты весовой функции:" << endl;
	for (int i = 0; i < 2 * N; ++i)
	{
		moments(i) = Simpson(a, b, m, moment, i);
		cout << "mu" << i << " = " << moments(i) << endl;
	}

	cout << "Интерполяционная квадратурная формула(ИКФ):" << endl;
	double c;
	for (int i = 0; i < N; ++i)
	{
		cout << "Введите узел ИКФ x" << i << endl;
		cin >> c;
		nodes.push_back(c);
	}

	mat A = ones(N, N);
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = A(i - 1, j) * nodes[j];
	}
	vec B = moments.rows(0, N - 1);
	vec coeff = solve(A, B);
	cout << "Коэффициенты ИКФ:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "A" << i << " = " << coeff(i) << endl;

	double result1 = interp(func, coeff, 0);
	cout << "Приближенное значение интеграла: " << result1 << ", абсолютная фактическая разность: " << abs(integral - result1) << endl;

	for (int i = 0; i <= 2 * N; ++i)
	{
		while (c == 0)
			c = (rand() % 1000) / 100;
		rand_coeff.push_back(c);
	}
	double result2 = interp(polynomial, coeff, N - 1);
	cout << "Проверка на примере полинома степени N-1:" << endl;
	cout << "Приближенное значение интеграла: " << result2 << ", абсолютная фактическая разность: " << abs(poly_integral(a, b, N - 1) - result2) << endl;

	cout << endl << "Квадратурная формула НАСТ:" << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = moments(j + i);
	}
	B = -moments.rows(N, 2 * N - 1);
	coeff = solve(A, B);
	cout << "Коэффициенты ортогонального многочлена:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "a" << i << " = " << coeff(i) << endl;

	double e;
	int N1;
	cout << "Введите числа N1 и e для поиска корней ортогонального многочлена" << endl;
	cin >> N1;
	cin >> e;
	double h = (b - a) / N1;
	double x1 = a;
	double x2 = x1 + h;
	double y2;
	double y1 = nast(x1, coeff);

	vector < pair <double, double>> v;
	pair<double, double> p;
	while (x2 <= b)
	{
		y2 = nast(x2, coeff);
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
	cout << "Узлы ортогонального многочлена:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		nodes[i] = secant(v[i], e, nast, coeff);
		cout << "a" << i << " = " << nodes[i] << endl;
	}

	A = ones(N, N);
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = A(i - 1, j) * nodes[j];
	}
	B = moments.rows(0, N - 1);
	coeff = solve(A, B);
	cout << "Коэффициенты КФ НАСТ:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "A" << i << " = " << coeff(i) << endl;

	double result3 = interp(func, coeff, 0);
	cout << "Приближенное значение интеграла: " << result3 << ", абсолютная фактическая разность: " << abs(integral - result3) << endl;
	double result4 = interp(polynomial, coeff, 2 * N - 1);
	cout << "Проверка на примере полинома степени 2N-1:" << endl;
	cout << "Приближенное значение интеграла: " << result4 << ", абсолютная фактическая разность: " << abs(poly_integral(a, b, 2 * N - 1) - result4) << endl;

	return 0;
}


double Simpson(double a, double b, int m, double(*f)(double, int), int k)
{
	double W = 0;
	double h = (b - a) / m;
	double c = a;
	for (int j = 1; j < m; ++j)
	{
		c += h;
		W += f(c, k);
	}

	double Q = 0;
	c = a + h / 2;
	for (int j = 0; j < m; ++j)
	{
		Q += f(c, k);
		c += h;
	}
	return (b - a) * (f(a, k) + f(b, k) + 2 * W + 4 * Q) / 6 / m;
}

double poly_integral(double a, double b, int k)
{
	double result = 0;
	double a1 = a * 2 * sqrt(a) / 3;
	double b1 = b * 2 * sqrt(b) / 3;
	for (int i = 0; i <= k; ++i)
	{
		result += rand_coeff[i] * (b1 - a1);
		b1 = b * b1 * (2 * i + 3) / (2 * i + 5);
		a1 = a * a1 * (2 * i + 3) / (2 * i + 5);
	}
	return result;
}

double secant(pair<double, double>& p, double e, double(*f)(double, vec), vec coeff)
{
	double x0 = p.first;
	double x1 = p.second;
	double g = f(x1, coeff);
	double x2 = x1 - (x1 - x0) * g / (g - f(x0, coeff));
	int i = 2;
	while (abs(x2 - x1) > e)
	{
		x0 = x1;
		x1 = x2;
		g = f(x1, coeff);
		x2 = x1 - (x1 - x0) * g / (g - f(x0, coeff));
		++i;
	}
	return (x2 + x1) / 2;
}

double Legendre(double x, int k)
{
	if (k == 0)
		return 1;
	else if (k == 1)
		return x;
	return ((2 * k - 1) * x * Legendre(x, k - 1) - (k - 1) * Legendre(x, k - 2)) / k;
}

