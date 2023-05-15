#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include<armadillo>

using namespace std;
using namespace arma;

double integral;
vector<double> rand_coeff;

vector<double> coefficients_Gauss(vector<double> nodes);
double Legendre(double x, vec coeff, int k);
vector<double> find_roots(double a, double b, double(*f)(double, vec, int), vec coeff, int k, int t);
double w_poly_integral(double a, double b, int k);
double secant(pair<double, double>& p, double e, double(*f)(double, vec, int), vec coeff, int k);
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
double w_func(double x, int k)
{
	return weight(x) * func(x, k);
}
double interp(double(*f)(double, int), vec coeff, int k, vector<double> nodes)
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
double w_polynomial(double x, int k)
{
	return weight(x) * polynomial(x, k);
}
double nast(double x, vec coeff, int k)
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
	cout << "Задание 5.1:" << endl;
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
	vector<double> nodes_IKF;
	for (int i = 0; i < N; ++i)
	{
		cout << "Введите узел ИКФ x" << i << endl;
		cin >> c;
		nodes_IKF.push_back(c);
	}

	mat A = ones(N, N);
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = A(i - 1, j) * nodes_IKF[j];
	}
	vec B = moments.rows(0, N - 1);
	vec coeff = solve(A, B);
	cout << "Коэффициенты ИКФ:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "A" << i << " = " << coeff(i) << endl;

	double result1 = interp(func, coeff, 0, nodes_IKF);
	cout << "Приближенное значение интеграла: " << result1 << ", абсолютная фактическая разность: " << abs(integral - result1) << endl;

	for (int i = 0; i <= 2 * N; ++i)
	{
		while (c == 0)
			c = (rand() % 1000) / 100;
		rand_coeff.push_back(c);
	}
	double result2 = interp(polynomial, coeff, N - 1, nodes_IKF);
	cout << "Проверка на примере полинома степени N-1:" << endl;
	cout << "Приближенное значение интеграла: " << result2 << ", абсолютная фактическая разность: " << abs(Simpson(a, b, m, w_polynomial, N - 1) - result2) << endl;

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

	vector<double> nodes_nast = find_roots(a, b, nast, coeff, 0, 1);
	A = ones(N, N);
	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			A(i, j) = A(i - 1, j) * nodes_nast[j];
	}
	B = moments.rows(0, N - 1);
	coeff = solve(A, B);
	cout << "Коэффициенты КФ НАСТ:" << endl;
	for (int i = 0; i < N; ++i)
		cout << "A" << i << " = " << coeff(i) << endl;

	double result3 = interp(func, coeff, 0, nodes_nast);
	cout << "Приближенное значение интеграла: " << result3 << ", абсолютная фактическая разность: " << abs(integral - result3) << endl;
	double result4 = interp(polynomial, coeff, 2 * N - 1, nodes_nast);
	cout << "Проверка на примере полинома степени 2N-1:" << endl;
	cout << "Приближенное значение интеграла: " << result4 << ", абсолютная фактическая разность: " << abs(Simpson(a, b, m, w_polynomial, 2 * N - 1) - result4) << endl;

	//-----------------------------------------------------------------------------------------------------
	//Задание 5.2
	cout << endl << endl << "Задание 5.2:" << endl;
	cout << "КФ Гаусса, ее узлы и коэффициенты. Вычисление интегралов при помощи КФ Гаусса" << endl;
	cout << "КФ Мелера, ее узлы и коэффициенты. Вычисление интегралов при помощи КФ Мелера" << endl;
	cout << "Введите максимальный параметр N, до которого рассчитывать квадратурные формулы Гаусса" << endl;
	cin >> N;

	vector<vector<double>> nodes_Legendre;
	vector<vector<double>> coeff_Gauss;
	cout << "Узлы и коэффициенты КФ Гаусса:" << endl;
	for (int i = 0; i < N; ++i)
	{
		nodes_Legendre.push_back(find_roots(-1, 1, Legendre, coeff, i + 1, 0));
		coeff_Gauss.push_back(coefficients_Gauss(nodes_Legendre[i]));
		cout << "N = " << i + 1 << endl;
		for (int j = 0; j < nodes_Legendre[i].size(); ++j)
			cout << j << "	Узел: " << nodes_Legendre[i][j] << ". Коэффициент: " << coeff_Gauss[i][j] << endl;
	}

	int N1;
	cout << endl << "Введите N, для которого осуществить проверку точности КФ Гаусса на многочленах степени 0..N+2" << endl;
	cin >> N1;
	rand_coeff.clear();
	for (int i = 0; i <= N + 2; ++i)
	{
		while (c == 0)
			c = (rand() % 1000) / 100;
		rand_coeff.push_back(c);
	}
	double result_i;
	coeff = vec(coeff_Gauss[N1 - 1]);
	for (int i = 0; i <= N1 + 2; ++i)
	{
		result_i = interp(polynomial, coeff, i, nodes_Legendre[N1 - 1]);
		cout << i << " степень:		Приближенное значение интеграла: " << result_i;
		cout << ", абсолютная фактическая разность: " << abs(Simpson(-1, 1, m, polynomial, i) - result_i) << " " << endl;
	}

	cout << endl << "Вычисление интеграла функции f(x) от a до b:" << endl;
	for (int i = 0; i < N; ++i)
	{
		result_i = interp(func, coeff_Gauss[i], 0, nodes_Legendre[i]);
		cout << i << "степень:	Приближенное значение интеграла: " << result_i << ", абсолютная фактическая разность: " << abs(integral - result_i) << " " << endl;
	}
	double t = 0;
	while (t == 0)
	{
		cout << endl << "Если хотите установить другие промежутки интегрирования, введите 1" << endl;
		cout << "В противном случае, введите 0" << endl;
		cin >> t;
		if (t == 1)
		{
			cout << "Введите левый конец промежутка интегрирования a" << endl;
			cin >> a;
			cout << "Введите правый конец промежутка интегрирования b" << endl;
			cin >> b;

		}
	}


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

double w_poly_integral(double a, double b, int k)
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

double secant(pair<double, double>& p, double e, double(*f)(double, vec, int), vec coeff, int k)
{
	double x0 = p.first;
	double x1 = p.second;
	double g = f(x1, coeff, k);
	double x2 = x1 - (x1 - x0) * g / (g - f(x0, coeff, k));
	int i = 2;
	while (abs(x2 - x1) > e)
	{
		x0 = x1;
		x1 = x2;
		g = f(x1, coeff, k);
		x2 = x1 - (x1 - x0) * g / (g - f(x0, coeff, k));
		++i;
	}
	return (x2 + x1) / 2;
}

double Legendre(double x, vec coeff, int k)
{
	if (k == 0)
		return 1;
	else if (k == 1)
		return x;
	return ((2 * k - 1) * x * Legendre(x, coeff, k - 1) - (k - 1) * Legendre(x, coeff, k - 2)) / k;
}

vector<double> find_roots(double a, double b, double(*f)(double, vec, int), vec coeff, int k, int t)
{
	vector<double> nodes;
	double e = 0.000000000001;
	int N1 = 10000;
	double h = (b - a) / N1;
	double x1 = a;
	double x2 = x1 + h;
	double y2;
	double y1 = f(x1, coeff, k);

	vector < pair <double, double>> v;
	pair<double, double> p;
	while (x2 <= b)
	{
		y2 = f(x2, coeff, k);
		if (y1 * y2 < 0)
		{
			p.first = x1;
			p.second = x2;
			v.push_back(p);
		}
		x1 += h;
		x2 += h;
		y1 = y2;
	}
	if (t == 1)
		cout << "Узлы многочлена:" << endl;
	for (int i = 0; i < v.size(); ++i)
	{
		nodes.push_back(secant(v[i], e, f, coeff, k));
		if (t == 1)
			cout << "a" << i << " = " << nodes[i] << endl;
	}
	return nodes;
}

vector<double> coefficients_Gauss(vector<double> nodes)
{
	vector<double> result;
	int N = nodes.size();
	vec coeff;
	double P;
	for (int i = 0; i < N; ++i)
	{
		P = Legendre(nodes[i], coeff, N - 1);
		result.push_back(2 * (1 - nodes[i] * nodes[i]) / (N * N * P * P));
	}
	return result;
}

