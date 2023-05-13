#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<armadillo>
#include"Reverse_Interpolation.cpp"

using namespace std;
using namespace arma;

vector<double> nodes;
double integral;

double Simpson(double a, double b, int m, double(*f)(double, int), int k);
double weight(double x)
{
	return x;
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
	return x;
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
	double result;
	double c = x;
	double a = 0;
	while (a = 0)
		a = (rand() % 1000) / 100;
	result = a;
	for (int i = 1; i <= k; ++i)
	{
		while (a = 0)
			a = (rand() % 1000) / 100;
		result += a * c;
		c *= x;
		a = 0;
	}
	return result;
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Приближённое вычисление интегралов при помощи квадратурных формул Наивысшей Алгебраической Степени Точности(НАСТ)" << endl;

	double a, b;
	int N;
	int m = 1000;
	cout << endl << "Введите левый конец промежутка интегрирования a" << endl;
	cin >> a;
	cout << endl << "Введите правый конец промежутка интегрирования b" << endl;
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
	double result2 = interp(polynomial, coeff, N - 1);
	cout << "Проверка на примере полинома степени N-1:" << endl;
	cout << "Приближенное значение интеграла: " << result2 << ", абсолютная фактическая разность: " << abs(Simpson(a, b, m, polynomial, N - 1) - result2) << endl;

	cout << endl << "Квадратурная формула НАСТ:" << endl;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = moments(j + i);
	}
	B = -moments.rows(N, 2*N - 1);
	coeff = solve(A, B);
	cout << "Коэффициенты КФ НАСТ:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "a" << i << " = " << coeff(i) << endl;

	vector<vector<double>> nodes2;
	vector<double> v{ 0, 0, 0, 0 };
	for (int i = 0; i < N; ++i)
		nodes2.push_back(v);



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