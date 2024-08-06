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
	return sin(x)-x*x/2;
}

void print_coeff(vector<double> v)
{
	for (auto x : v)
		cout << x << endl;
	return;
}

vector<vector<double>> nodes(int m, double a, double b)
{
	vector<vector<double>> v;
	vector<double> p;
	for (int i = 0; i <= m; ++i)
	{
		p.push_back(i);
		//p.push_back(a + (b - a) * double((i + double((rand() % 100)) / 100)) / (m + 1));
		p.push_back(a + (b - a) * i/m);
		p.push_back(0);
		p.push_back(func(p[1]));
		v.push_back(p);
		p.clear();
	}
	return v;
}

void print(vector<vector< double>> v)
{
	int k = 0;
	cout << "xk			 |f(xk)" << endl;
	for (auto i : v)
	{
		cout << k<<"	x" << i[0] << " =	" << i[1] << "			|f(x" << i[0] << ") = " << i[3] << endl;
		++k;
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

double leftmost(vector<vector<double>> v, double a, int n)
{
	double x = v[0][1];
	for (int i = 0; i <= n; ++i)
	{
		x = min(x, v[i][1]);
	}
	return x;
}

void bisection(pair<double, double>& p, double e, vector<vector<double>> v, int n, double F)
{
	double a = p.first;
	double b = p.second;
	double c = (a + b) / 2;
	vector<double> coeff;
	int i = 0;
	if (v.size() == n)
	{
		coeff = coefficients(v, n - 1);
		while (b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(v, coeff, a, n - 1) - F)* (Newton(v, coeff, c, n - 1) - F) <= 0 ? b = c : a = c;
			++i;
		}
	}
	else
	{
		vector<vector<double>> va = sort(v, a);
		vector<vector<double>> vc = sort(v, c);
		while (leftmost(va, a, n) != leftmost(vc, c, n) && b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(va, coefficients(va, n), a, n) - F)* (Newton(vc, coefficients(vc, n), c, n) - F) <= 0 ? b = c : a = c;
			va = sort(v, a);
			vc = sort(v, c);
			++i;
		}
		coeff = coefficients(va, n);
		while (b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(va, coeff, a, n) - F)* (Newton(va, coeff, c, n) - F) <= 0 ? b = c : a = c;
			++i;
		}
	}
	c = (a + b) / 2;
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ",		|f(xm)-F| = " << abs(func(c) - F) << ". Количество итераций: " << i << endl;
}

void boolean(int& count, double y1, double y2, vector<pair<double, double>>& w, pair<double, double>& p, int& rise, double& memory, double x0, double x1, double F)
{
	if (y1 <= y2 && rise == 0)
	{
		cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << y2 << endl;
		if ((memory <= F && F <= y2) or (memory >= F && F >= y2))
			w.push_back(p);
		memory = y1;
		p.first = x0;
		p.second = x1;
		rise = 1;
		++count;
	}
	else if ((y1 >= y2 && rise == 0) or (y1 <= y2 && rise == 1))
	{
		p.second = x1;
	}
	else if (y1 >= y2 && rise == 1)
	{
		cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << y2 << endl;
		if ((memory <= F && F <= y2) or (memory >= F && F >= y2))
			w.push_back(p);
		memory = y1;
		p.first = x0;
		p.second = x1;
		rise = 0;
		++count;
	}
}

//void boolean(int& count, double y1, double y2, vector<pair<double, double>>& w, pair<double, double>& p, int& rise, double& memory, double x0, double x1, double F, vector<pair<double, double>>& values)
//{
//	pair<double, double> p1;
//	if (y1 <= y2 && rise == 0)
//	{
//		cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << y2 << endl;
//		w.push_back(p);
//		p1.first = memory;
//		p1.second = y2;
//		values.push_back(p1);
//		memory = y1;
//		p.first = x0;
//		p.second = x1;
//		rise = 1;
//		++count;
//	}
//	else if ((y1 >= y2 && rise == 0) or (y1 <= y2 && rise == 1))
//	{
//		p.second = x1;
//	}
//	else if (y1 >= y2 && rise == 1)
//	{
//		cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << y2 << endl;
//		w.push_back(p);
//		p1.first = memory;
//		p1.second = y2;
//		values.push_back(p1);
//		memory = y1;
//		p.first = x0;
//		p.second = x1;
//		rise = 0;
//		++count;
//	}
//}

vector<pair<double, double>> procedure(vector<vector<double>>& v, int n, int N, double F)
{
	double h = (v[v.size() - 1][1] - v[0][1]) / N;
	vector<double> end = v[v.size() - 1];
	double x0 = v[0][1];
	double x1 = x0 + h;
	int count = 0;

	vector<double> A = coefficients(v, n);
	pair<double, double> p;
	p.first = x0;
	p.second = x1;
	vector<pair<double, double>> w;

	double y1 = v[0][3];
	double y2 = Newton(v, A, x1, n);
	int rise = (y1 <= y2 ? 1 : 0);
	double memory = y1;

	int k = n;
	while (k < v.size() - 2)
	{
		v[k + 1].swap(v[(k - n) % (n + 1)]);
		A = coefficients(v, n);
		y1 = Newton(v, A, x0, n);
		while (x0 - v[(k - n) % (n + 1)][1] < v[k + 2][1] - x0)
		{
			y2 = Newton(v, A, x1, n);
			boolean(count, y1, y2, w, p, rise, memory, x0, x1, F);
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
		boolean(count, y1, y2, w, p, rise, memory, x0, x1, F);
		x0 += h;
		x1 += h;
		y1 = y2;
	}
	p.second = end[1];
	cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << end[3] << endl;
	if ((memory <= F && F <= y2) or (memory >= F && F >= y2))
		w.push_back(p);
	++count;
	cout << "Количество промежутков монотонности равно " << count << endl << endl;
	return w;
}

//vector<pair<double, double>> procedure(vector<vector<double>>& v, int n, int N, double F, vector<pair<double, double>>& values)
//{
//	double h = (v[v.size() - 1][1] - v[0][1]) / N;
//	vector<double> end = v[v.size() - 1];
//	double x0 = v[0][1];
//	double x1 = x0 + h;
//	int count = 0;
//
//	vector<double> A = coefficients(v, n);
//	pair<double, double> p, p1;
//	p.first = x0;
//	p.second = x1;
//	vector<pair<double, double>> w;
//
//	double y1 = v[0][3];
//	double y2 = Newton(v, A, x1, n);
//	int rise = (y1 <= y2 ? 1 : 0);
//	double memory = y1;
//
//	int k = n;
//	while (k < v.size() - 2)
//	{
//		v[k + 1].swap(v[(k - n) % (n + 1)]);
//		A = coefficients(v, n);
//		y1 = Newton(v, A, x0, n);
//		while (x0 - v[(k - n) % (n + 1)][1] < v[k + 2][1] - x0)
//		{
//			y2 = Newton(v, A, x1, n);
//			boolean(count, y1, y2, w, p, rise, memory, x0, x1, F, values);
//			x0 += h;
//			x1 += h;
//			y1 = y2;
//		}
//		++k;
//	}
//	A = coefficients(v, n);
//	y1 = Newton(v, A, x0, n);
//	while (x0 < v[(k - n) % (n + 1)][1])
//	{
//		y2 = Newton(v, A, x1, n);
//		boolean(count, y1, y2, w, p, rise, memory, x0, x1, F);
//		x0 += h;
//		x1 += h;
//		y1 = y2;
//	}
//	p.second = end[1];
//	cout << "[a" << count << ",b" << count << "]=[" << p.first << "," << p.second << "],		f'(a) = " << memory << ",	f'(b) = " << end[3] << endl;
//	w.push_back(p);
//	p1.first = memory;
//	p1.second = y2;
//	values.push_back(p1);
//	++count;
//	cout << "Количество промежутков монотонности равно " << count << endl << endl;
//	return w;
//}

void search1(vector<vector<double>> v, pair<double, double> p, double F, int n)
{
	vector<double> coeff;
	vector<vector<double>> x;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i][1] >= p.first && v[i][1] <= p.second)
			x.push_back(v[i]);
	}
	if (x.size() > n + 1)
	{
		x = sort(swap(x), F);
		print(x);
		coeff = coefficients(x, n);
		print_coeff(coeff);
		double answer = Lagrange(x, F, n);
		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
	}
	else if (x.size() == n + 1)
	{
		x = sort(swap(x),F);
		print(x);
		coeff = coefficients(x, n);
		print_coeff(coeff);
		double answer = Lagrange(x, F, n);
		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
	}
	else
	{
		x = sort(swap(x),F);
		print(x);
		coeff = coefficients(x, x.size()-1);
		print_coeff(coeff);
		double answer = Lagrange(x, F, x.size());
		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
	}
}

void search2(vector<vector<double>> v, pair<double, double> p, double F, int n, double e)
{
	vector<vector<double>> x;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i][1] >= p.first && v[i][1] <= p.second)
			x.push_back(v[i]);
	}

	if (x.size() > n + 1)
	{
		bisection(p, e, x, n, F);
	}
	else
	{
		bisection(p, e, x, x.size(), F);
	}
}
//
//void search1(vector<vector<double>> v, pair<double, double> p, double F, int n, pair<double, double> p1)
//{
//	vector<vector<double>> x;
//	for (int i = 0; i < v.size(); ++i)
//	{
//		if ((F >= p1.first && F <= p1.second or F <= p1.first && F >= p1.second) && (v[i][1] >= p.first && v[i][1] <= p.second))
//			x.push_back(v[i]);
//	}
//	if (x.size() > n + 1)
//	{
//		x = sort(swap(x), F);
//		double answer = Lagrange(x, F, n);
//		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
//	}
//	else if (x.size() == n + 1)
//	{
//		x = swap(x);
//		double answer = Lagrange(x, F, n);
//		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
//	}
//	else
//	{
//		x = swap(x);
//		double answer = Lagrange(x, F, x.size());
//		cout << "X = f^-1(F) = " << answer << ",	|f(X)-F| = " << abs(F - func(answer)) << endl;
//	}
//}
//
//void search2(vector<vector<double>> v, pair<double, double> p, double F, int n, double e, pair<double, double> p1)
//{
//	vector<vector<double>> x;
//	for (int i = 0; i < v.size(); ++i)
//	{
//		if ((F>=p1.first && F<=p1.second or F <= p1.first && F >= p1.second)&&(v[i][1] >= p.first && v[i][1] <= p.second))
//			x.push_back(v[i]);
//	}
//
//	if (x.size() > n + 1)
//	{
//		bisection(p, e, x, n, F);
//	}
//	else
//	{
//		bisection(p, e, x, x.size(), F);
//	}
//}
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Задача обратного интерполирования, вариант 2, функция f(x) = ln(1+x)" << endl;
	cout << "Введите число табличных значений" << endl;
	int m = 0;
	cin >> m;
	--m;
	double a = 0;
	double b = 0;
	double F = 0;
	cout << "Введите левую границу отрезка а > -1" << endl;
	cin >> a;
	b = a;
	while (b <= a)
	{
		cout << "Введите правую границу отрезка b > " << a << endl;
		cin >> b;
	}

	double X = 0;
	int n = m + 1;
	vector<vector<double>> v = nodes(m, a, b);
	vector<vector<double>> v2 = v;
	//vector<pair<double, double>> values;
	print(v);

	int t = 1;
	while (t == 1)
	{
		cout << "Введите значение функции F" << endl;
		cin >> F;
		while (n > m)
		{
			cout << "Введите степень интерполирования многочлена n <= " << m << endl;
			cin >> n;
		}
		int N = 0;
		cout << "Ведите значение N - число начальных промежутков для поиска промежутков монотонности" << endl;
		cin >> N;

		cout << endl << "3.1, первый способ:" << endl << endl;
		//vector<pair<double, double>> w = procedure(v2, n, N, F, values);
		//for (int i = 0; i < w.size(); ++i)
		//{
		//	search1(v2, w[i], F, n, values[i]);
		//}

		vector<pair<double, double>> w = procedure(v2, n, N, F);
		for (int i = 0; i < w.size(); ++i)
		{
			search1(v2, w[i], F, n);
		}


		cout << endl << "3.1, второй способ:" << endl;
		cout << "Введите точность е" << endl << endl;
		double e;
		cin >> e;

		for (int i = 0; i < w.size(); ++i)
		{
			search2(v2, w[i], F, n, e);
		}
		cout << endl << "Найдено решений: " << w.size() << endl;
		w.clear();
		v2 = v;

		cout << endl << "Чтобы ввести новые значения F, n или e, введите 1" << endl;
		cout << "Чтобы закончить работу программы, введите 0" << endl << endl;
		cin >> t;
	}
	return 0;
}



//vector<pair<double, double>> procedure2(vector<vector<double>>& v, int n, int N, double F)
//{
//	double h = (v[v.size() - 1][1] - v[0][1]) / N;
//	double x0 = v[0][1];
//	double x1 = x0 + h;
//
//	vector<double> A = coefficients(v, n);
//	pair<double, double> p;
//	vector<pair<double, double>> w;
//	double y1 = v[0][3];
//	double y2;
//
//	int k = n;
//	while (k < v.size() - 2)
//	{
//		v[k + 1].swap(v[(k - n) % (n + 1)]);
//		A = coefficients(v, n);
//		y1 = Newton(v, A, x0, n);
//		while (x0 - v[(k - n) % (n + 1)][1] < v[k + 2][1] - x0)
//		{
//			y2 = Newton(v, A, x1, n);
//			if ((y1 - F) * (y2 - F) < 0)
//			{
//				cout << "[a" << w.size() << ",b" << w.size() << "]=[" << x0 << "," << x1 << "];		f'(a) = " << y1 << ", 	f'(b) = " << y2 << endl;
//				p.first = x0;
//				p.second = x1;
//				w.push_back(p);
//			}
//			x0 += h;
//			x1 += h;
//			y1 = y2;
//		}
//		++k;
//	}
//	A = coefficients(v, n);
//	y1 = Newton(v, A, x0, n);
//	while (x0 < v[(k - n) % (n + 1)][1])
//	{
//		y2 = Newton(v, A, x1, n);
//		if ((y1 - F) * (y2 - F) < 0)
//		{
//			cout << "[a" << w.size() << ",b" << w.size() << "]=[" << x0 << "," << x1 << "];		f'(a) = " << y1 << ", 	f'(b) = " << y2 << endl;
//			p.first = x0;
//			p.second = x1;
//			w.push_back(p);
//		}
//		x0 += h;
//		x1 += h;
//		y1 = y2;
//	}
//	cout << "Количество промежутков смены знака функции f'(x)-F равно " << w.size() << endl;
//	return w;
//}