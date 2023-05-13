#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <iomanip>
#include <ctime>
using namespace std;

void bisection(pair<double, double>& p, double e);
void Newton(pair<double, double>& p, double e);
void modNewton(pair<double, double>& p, double e);
void secant(pair<double, double>& p, double e);

double function(double x)
{
	return pow(2, -x) - sin(x);
}
double f_deriv(double x)
{
	return -pow(2, -x) * log(2) - cos(x);
}
double s_deriv(double x)
{
	return pow(2, -x) * log(2) * log(2) + sin(x);
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
		cout << "c = " << c << endl;
		function(a)* function(c) <= 0 ? b = c : a = c;
		++i;
	}
	c = (a + b) / 2;
	cout << "c = " << c << endl;
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
}


//void Newton(pair<double, double>& p, double e)
//{
//	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
//	double x0 = (p.first + p.second) / 2;
//	if (function(x0) * s_deriv(x0) <= 0)
//	{
//		cout << "Не выполнено условие 3 из теоремы о сходимости." << endl;
//	}
//	else
//	{
//		int i = 1;
//		double x1 = x0 - function(x0) / f_deriv(x0);
//		while (abs(x1 - x0) > 2 * e)
//		{
//			x0 = x1;
//			x1 = x0 - function(x0) / f_deriv(x0);
//			++i;
//			if (i > 1000000)
//			{
//				cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
//				break;
//			}
//		}
//		if (i <= 1000000)
//		{
//			double c = (x1 + x0) / 2;
//			cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
//		}
//	}
//}


//void modNewton(pair<double, double>& p, double e)
//{
//	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
//	double x0 = (p.first + p.second) / 2;
//	if (function(x0) * s_deriv(x0) <= 0)
//	{
//		cout << "Не выполнено условие 3 из теоремы о сходимости." << endl;
//	}
//	else
//	{
//		int i = 1;
//		double a = 1 / f_deriv(x0);
//		double x1 = x0 - function(x0) * a;
//		while (abs(x1 - x0) > 2 * e)
//		{
//
//			x0 = x1;
//			x1 = x0 - function(x0) * a;
//			++i;
//			if (i > 1000000)
//			{
//				cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
//				break;
//			}
//		}
//		if (i <= 1000000)
//		{
//			double c = (x1 + x0) / 2;
//			cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
//		}
//	}
//}


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


//void Newton(pair<double, double>& p, double e)
//{
//	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
//	double x0 = (p.first + p.second) / 2;
//	int k = 0;
//	if (function(x0) * s_deriv(x0) <= 0)
//	{
//		while (function(x0) * s_deriv(x0) <= 0)
//		{
//			x0 = p.first + (rand() % 100) / 100 * (p.second - p.first);
//			++k;
//			if (k > 1000000)
//			{
//				cout << "Не выполнено условие 3 из теоремы о сходимости для более чем миллиона точек, сходимость маловероятна." << endl;
//				break;
//			}
//		}
//	}
//	if (k > 1000000)
//		return;
//	if (k > 0)
//		cout << "Шагов для подбора x0: " << k << endl;
//	int i = 1;
//	double x1 = x0 - function(x0) / f_deriv(x0);
//	while (abs(x1 - x0) > 2 * e)
//	{
//		x0 = x1;
//		x1 = x0 - function(x0) / f_deriv(x0);
//		++i;
//		if (i > 1000000)
//		{
//			cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
//			break;
//		}
//	}
//	if (i <= 1000000)
//	{
//		double c = (x1 + x0) / 2;
//		cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
//	}
//}
//
//
//void modNewton(pair<double, double>& p, double e)
//{
//	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
//	double x0 = (p.first + p.second) / 2;
//	int k = 0;
//	if (function(x0) * s_deriv(x0) <= 0)
//	{
//		while (function(x0) * s_deriv(x0) <= 0)
//		{
//			x0 = p.first + (rand() % 100) / 100 * (p.second - p.first);
//			++k;
//			if (k > 1000000)
//			{
//				cout << "Не выполнено условие 3 из теоремы о сходимости для более чем миллиона точек, сходимость маловероятна." << endl;
//				break;
//			}
//		}
//	}
//	if (k > 1000000)
//		return;
//	if (k > 0)
//		cout << "Шагов для подбора x0: " << k << endl;
//	int i = 1;
//	double a = 1 / f_deriv(x0);
//	double x1 = x0 - function(x0) * a;
//	while (abs(x1 - x0) > 2 * e)
//	{
//		x0 = x1;
//		x1 = x0 - function(x0) * a;
//		++i;
//		if (i > 1000000)
//		{
//			cout << "Количество итераций превысило 1000000, сходимость маловероятна." << endl;
//			break;
//		}
//	}
//	if (i <= 1000000)
//	{
//		double c = (x1 + x0) / 2;
//		cout << "xm = " << c << ",  d = " << abs(x0 - x1) / 2 << ",  |f(xm)-0| = " << abs(function(c)) << ". Количество итераций: " << i << endl;
//	}
//}













#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

double func(double x)
{
	//return log(1 + x);
	return sin(x * x);
}

vector<vector<double>> swap(vector<vector<double>> v);
void print(vector<vector<double>> v);
void print_reverse(vector<vector<double>> v, int n);
vector<vector<double>> nodes(int m, double a, double b);
vector<vector<double>> sort(vector<vector<double>> v, double x);
double Lagrange(vector<vector<double>> v, double x, int n);
vector<double> coefficients(vector<vector<double>> v, int n);
double Newton(vector<vector<double>> v, vector<double> A, double x, int n);
vector<pair<double, double>> procedure(vector<vector<double>>& v, int n, int N, double F);

//int main()
//{
//	srand(time(0));
//	setlocale(LC_ALL, "Russian");
//	cout << setprecision(13) << "Задача обратного интерполирования, вариант 2, функция f(x) = ln(1+x)" << endl;
//	int t = 1;
//	cout << "Введите число табличных значений" << endl;
//	int m = 0;
//	cin >> m;
//	--m;
//	double a = 0;
//	double b = 0;
//	double F = 0;
//	cout << "Введите левую границу отрезка а > -1" << endl;
//	cin >> a;
//	cout << "Введите правую границу отрезка b > " << a << endl;
//	cin >> b;
//	cout << "Введите значение функции F" << endl;
//	cin >> F;
//
//	double X = 0;
//
//	int n = 0;
//	vector<vector<double>> v, v1;
//	nodes(m, v, a, b);
//	v1 = sort(v, F);
//	vector < double> coeff = coefficients(v1, F n);
//	int  N = 0;
//	double a = 0;
//	double b = 0;
//	double e = 0;
//	double h = 0;
//	cout << setprecision(18) << "Введите значение A" << endl;
//	cin >> a;
//	cout << "Ведите значение B" << endl;
//	cin >> b;
//	cout << "Ведите значение N" << endl;
//	cin >> N;
//	cout << "Ведите значение e" << endl;
//	cin >> e;
//	cout << "Исходные параметры: [A,B] = [" << a << "," << b << "], f(x) = ln(1+x), e = " << e << "." << endl;
//	h = (b - a) / N;
//	double x1 = a;
//	double x2 = x1 + h;
//	double y2;
//	double y1 = Newton(v, coeff, x1, n);
//	vector <pair<double, double>> f;
//	pair<double, double> p;
//	while (x2 <= b)
//	{
//		y2 = Newton(v, coeff, x2, n);
//		if (y1 * y2 < 0)
//		{
//			cout << "[a" << f.size() << ",b" << f.size() << "]=[" << x1 << "," << x2 << "]" << endl;
//			p.first = x1;
//			p.second = x2;
//			f.push_back(p);
//		}
//		x1 += h;
//		x2 += h;
//		y1 = y2;
//	}
//	cout << "Количество отрезков перемены знака равно " << f.size() << endl << endl;
//	while (t == 1)
//	{
//		print(v);
//		n = m + 1;
//		while (n > m)
//		{
//			cout << "Введите степень интерполирования многочлена n <= " << m << endl;
//			cin >> n;
//		}
//		cout << endl << "Таблица для построения интерполяционного многочлена обратной функции:" << endl;
//		print_reverse(v1, n);
//		X = Lagrange(v1, F, n);
//		cout << endl << "Метод Лагранжа:" << endl;
//		cout << "Значение интерполяционного многочлена X = f^-1(F): " << X << endl;
//		cout << "Модуль невязки |f(X)-F|: " << abs(func(X) - F) << endl;
//
//		X = Newton(v1, coefficients(v1, n), F, n);
//		cout << endl << "Метод Ньютона:" << endl;
//		cout << "Значение интерполяционного многочлена X = f^-1(F): " << X << endl;
//		cout << "Модуль невязки |f(X)-F|: " << abs(func(X) - F) << endl;
//
//		system("pause");
//
//
//		cout << endl << "Чтобы ввести новые значения для точки интерполяции или степени многочлена, введите 1" << endl;
//		cout << "Чтобы закончить работу программы, введите 0" << endl << endl;
//		cin >> t;
//	}
//	return 0;
//}


vector<vector<double>> nodes(int m, double a, double b)
{
	vector<vector<double>> v;
	vector<double> p;
	for (int i = 0; i <= m; ++i)
	{
		p.push_back(i);
		p.push_back(a + (b - a) * double((i + double((rand() % 100)) / 100)) / (m + 1));
		p.push_back(0);
		p.push_back(func(p[1]));
		v.push_back(p);
		p.clear();
	}
	return v;
}

void print(vector<vector< double>> v)
{
	cout << "xk			 |f(xk)" << endl;
	for (auto i : v)
	{
		cout << "x" << i[0] << " =	" << i[1] << "			|f(x" << i[0] << ") = " << i[3] << endl;
	}
}

void print_reverse(vector<vector<double>> v, int n)
{
	int count = 0;
	cout << "f(xk)				||f(xk)-F|				|f^-1(f(xk))" << endl;
	for (auto i : v)
	{
		if (count == n + 1)
			break;
		cout << "f(x" << i[0] << ") = " << i[1] << "			||f(x" << i[0] << ")-F| = " << i[2] << "			|f^-1(f(x" << i[0] << ")) = " << i[3] << endl;
		++count;
	}
}

vector<vector<double>> swap(vector<vector<double>> v)
{
	vector<vector<double>> v1 = v;
	double a = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		v1[i][1] = v[i][3];
		v1[i][3] = v[i][1];
	}
	return v1;
}

vector<vector<double>> sort(vector<vector<double>> v, double x)
{
	vector<double> p;
	double a = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		v[i][2] = abs(v[i][1] - x);
	}
	for (int i = 0; i < v.size() - 1; ++i)
	{
		for (int j = 0; j < v.size() - i - 1; ++j)
		{
			if (v[j][2] > v[j + 1][2])
			{
				p = v[j];
				v[j] = v[j + 1];
				v[j + 1] = p;
			}
		}
	}
	return v;
}

double Lagrange(vector<vector<double>> v, double x, int n)
{
	double a = 1;
	double b = 1;
	double s = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (j != i)
			{
				a *= x - v[j][1];
				b *= v[i][1] - v[j][1];
			}
		}
		s += v[i][3] * a / b;
		a = 1;
		b = 1;
	}
	return s;
}

vector<double> coefficients(vector<vector<double>> v, int n)
{
	double w = 1;
	vector<double> A;
	A.push_back(v[0][3]);
	double s = 0;
	for (int k = 1; k <= n; ++k)
	{
		for (int i = 0; i <= k; ++i)
		{
			for (int j = 0; j <= k; ++j)
			{
				if (j != i)
					w *= (v[i][1] - v[j][1]);
			}
			s += v[i][3] / w;
			w = 1;
		}
		A.push_back(s);
		s = 0;
	}
	return A;
}

double Newton(vector<vector<double>> v, vector<double> A, double x, int n)
{
	double s = A[0];
	double b = 1;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			b *= (x - v[j][1]);
		}
		s += A[i] * b;
		b = 1;
	}
	return s;
}

void bisection(pair<double, double>& p, double e, vector<vector<double>> v, vector<double> coeff, int n, double F)
{
	cout << "Начальное приближение: [" << p.first << "," << p.second << "]" << endl;
	double a = p.first;
	double b = p.second;
	double c = 0;
	int i = 0;
	while (b - a > 2 * e)
	{
		c = (a + b) / 2;
		v = sort(v, a);
		(Newton(v, coefficients(v, n), a, n) - F)* (Newton(sort(v, c), coefficients(sort(v, c), n), c, n) - F) <= 0 ? b = c : a = c;
		++i;
	}
	c = (a + b) / 2;
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ", |f(xm)-F| = " << abs(func(c) - F) << ",		 |Newton(v, coeff, c, n)-F| = " << abs(Newton(sort(v, c), coefficients(sort(v, c), n), c, n) - F) << ". Количество итераций: " << i << endl;
}

vector<pair<double, double>> procedure(vector<vector<double>>& v, int n, int N, double F)
{
	double h = (v[v.size() - 1][1] - v[0][1]) / N;
	double x0 = v[0][1];
	vector<double> A = coefficients(v, n);
	pair<double, double> p;
	vector<pair<double, double>> w;
	vector<double> e;
	double y1 = v[0][3];
	double y2;
	double x1 = x0 + h;
	while (x0 - v[0][1] < v[n + 1][1] - x0)
	{
		y2 = Newton(v, A, x1, n);
		if ((y1 - F) * (y2 - F) < 0)
		{
			cout << "[a" << w.size() << ",b" << w.size() << "]=[" << x0 << "," << x1 << "];		f(a) = " << y1 << ", func(x1) =" << func(x1) << "	f(b) = " << y2 << endl;
			p.first = x0;
			p.second = x1;
			w.push_back(p);
		}
		x0 += h;
		x1 += h;
		y1 = y2;
	}
	int k = n;
	while (k < v.size() - 2)
	{
		v[k + 1].swap(v[(k - n) % (n + 1)]);
		A = coefficients(v, n);
		y1 = Newton(v, A, x0, n);
		while (x0 - v[(k - n) % (n + 1)][1] < v[k + 2][1] - x0)
		{
			y2 = Newton(v, A, x1, n);
			if ((y1 - F) * (y2 - F) < 0)
			{
				cout << "[a" << w.size() << ",b" << w.size() << "]=[" << x0 << "," << x1 << "];		f(a) = " << y1 << ", func(x1) =" << func(x1) << "	f(b) = " << y2 << endl;
				p.first = x0;
				p.second = x1;
				w.push_back(p);
			}
			x0 += h;
			x1 += h;
			y1 = y2;
		}
		++k;
	}
	A = coefficients(v, n);
	y1 = Newton(v, A, x0, n);
	while (x0 < v[(k - n) % (n + 1)][1])
	{
		y2 = Newton(v, A, x1, n);
		if ((y1 - F) * (y2 - F) < 0)
		{
			cout << "[a" << w.size() << ",b" << w.size() << "]=[" << x0 << "," << x1 << "];		f(a) = " << y1 << ", func(x1) =" << func(x1) << "	f(b) = " << y2 << endl;
			p.first = x0;
			p.second = x1;
			w.push_back(p);
		}
		x0 += h;
		x1 += h;
		y1 = y2;
	}
	return w;
}

vector<vector<double>> search(vector<vector<double>> v, pair<double, double> p, double F, int n)
{
	vector<vector<double>> v1 = sort(v, (p.first + p.second) / 2);
	while (v1.size() > n + 1)
	{
		v1.pop_back();
	}
	v1 = sort(swap(v1), F);
	return v1;
}

//int main()
//{
//	srand(time(0));
//	setlocale(LC_ALL, "Russian");
//	cout << setprecision(13) << "Задача обратного интерполирования, вариант 2, функция f(x) = ln(1+x)" << endl;
//	cout << "Введите число табличных значений" << endl;
//	int m = 0;
//	cin >> m;
//	--m;
//	double a = 0;
//	double b = 0;
//	double F = 0;
//	cout << "Введите левую границу отрезка а > -1" << endl;
//	cin >> a;
//	cout << "Введите правую границу отрезка b > " << a << endl;
//	cin >> b;
//	cout << "Введите значение функции F" << endl;
//	cin >> F;
//
//	double X = 0;
//	int n = m + 1;
//	vector<vector<double>> v = nodes(m, a, b);
//	vector<vector<double>> v2;
//	print(v);
//	while (n > m)
//	{
//		cout << "Введите степень интерполирования многочлена n <= " << m << endl;
//		cin >> n;
//	}
//	int N = 0;
//	cout << "Ведите значение N - число начальных промежутков для поиска промежутков монотонности" << endl;
//	cin >> N;
//	vector<pair<double, double>> w = procedure(v, n, N, F);
//	cout << "Количество отрезков перемены знака равно " << w.size() << endl << endl;
//
//	cout << "3.1, первый способ:" << endl;
//	vector<double> coeff;
//	for (int i = 0; i < w.size(); ++i)
//	{
//		v2 = search(v, w[i], F, n);
//		cout << endl << "Таблица для построения интерполяционного многочлена обратной функции:" << endl;
//		print_reverse(v2, n);
//		//X = Lagrange(v2, F, n);
//		coeff = coefficients(v2, n);
//		X = Newton(v2, coeff, F, n);
//		cout << "Значение интерполяционного многочлена X = f^-1(F): " << X << endl;
//		cout << "Модуль невязки |f(X)-F|: " << abs(func(X) - F) << endl;
//	}
//
//	cout << "3.1, второй способ:" << endl;
//	cout << "Введите точность е" << endl;
//	double e;
//	cin >> e;
//	for (int i = 0; i < w.size(); ++i)
//	{
//		v2 = sort(v, (w[i].first + w[i].second) / 2);
//		coeff = coefficients(v, n);
//		bisection(w[i], e, v2, coeff, n, F);
//	}
//
//	return 0;
//}