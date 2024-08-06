#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

double func(double x)
{
	return log(1 + x);
	//return x*x*x-x*x+3*x-5;
}

void nodes(int m, vector<vector<double>>& v, double a, double b);
void print(vector<vector<double>> v, int n);
vector<vector<double>> sort(vector<vector<double>> v, double x);
double Lagrange(vector<vector<double>> v, double x, int n);
double Newton(vector<vector<double>> v, double x, int n);
double dd(vector<vector<double>> v, int a, int b);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "«адача алгебраического интерполировани¤, вариант 2, функци¤ f(x) = ln(1+x)" << endl;
	int t = 1;
	cout << "¬ведите число табличных значений" << endl;
	int m = 0;
	cin >> m;
	--m;
	double a = 0;
	double b = 0;
	cout << "¬ведите левую границу отрезка а > -1" << endl;
	cin >> a;
	cout << "¬ведите правую границу отрезка b > " << a << endl;
	cin >> b;

	double s = 0;
	int c = -1;
	double x = 0;
	int n = 0;
	vector<vector<double>> v1;

	vector<vector<double>> v;
	nodes(m, v, a, b);
	while (t == 1)
	{
		print(v, m + 1);
		while (c != 1 and c != 0)
		{
			cout << endl << "„тобы выбрать один из узлов за точку интерпол¤ции, введите 0" << endl;
			cout << "„тобы выбрать произвольную точку интерпол¤ции, введите 1" << endl;
			cin >> c;

			if (c == 0)
			{
				cout << "¬ведите номер узла, который хотите выбрать в качестве точки инетрпол¤ции" << endl;
				cin >> c;
				x = v[c][1];
				break;
			}
			else if (c == 1)
			{
				cout << "¬ведите точку интерполировани¤ x > -1" << endl;
				cin >> x;
			}
		}
		n = m + 1;
		while (n > m)
		{
			cout << "¬ведите степень интерполировани¤ многочлена n <= " << m << endl;
			cin >> n;
		}
		v1 = sort(v, x);
		cout << "ќтсортированна¤ таблица значений:" << endl;
		print(v1, n + 1);

		s = Lagrange(v1, x, n);
		cout << endl << "ћетод Ћагранжа:" << endl;
		cout << "«начение интерпол¤ционного многочлена: " << s << endl;
		cout << "«начение абсолютной фактической погрешности: " << abs(func(x) - s) << endl;

		s = Newton(v1, x, n);
		cout << endl << "ћетод Ќьютона:" << endl;
		cout << "«начение интерпол¤ционного многочлена: " << s << endl;
		cout << "«начение абсолютной фактической погрешности: " << abs(func(x) - s) << endl;

		cout << endl << "„тобы ввести новые значени¤ дл¤ точки интерпол¤ции или степени многочлена, введите 1" << endl;
		cout << "„тобы закончить работу программы, введите 0" << endl << endl;
		cin >> t;
	}
	return 0;
}


void nodes(int m, vector<vector<double>>& v, double a, double b)
{
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
}

void print(vector<vector< double>> v, int n)
{
	int k = 0;
	if (v[1][2] == 0)
	{
		cout << "xk		   |f(xk)" << endl;
		for (auto i : v)
		{
			cout << "x" << k << " =	" << i[1] << "			|f(x" << k << ") = " << i[3] << endl;
			++k;
		}
	}
	else
	{
		int count = 0;
		cout << "xk				||xk-x|				|f(xk)" << endl;
		for (auto i : v)
		{
			if (count == n)
				break;
			cout << "x" << i[0] << " = " << i[1] << "			||x" << i[0] << "-x| = " << i[2] << "			|f(x" << i[0] << ") = " << i[3] << endl;
			++k;
			++count;
		}
	}
}

vector<vector<double>> sort(vector<vector<double>> v, double x)
{
	vector<double> p;
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
				/*v[i].swap(v[i + 1]);*/
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

double Newton(vector<vector<double>> v, double x, int n)
{
	double s = func(v[0][1]);
	double c = 1;
	for (int i = 1; i <= n; ++i)
	{
		c *= x - v[i - 1][1];
		s += dd(v, 0, i) * c;
	}
	return s;
}

double dd(vector<vector<double>> v, int a, int b)
{
	if (b - a == 1)
		return (v[b][3] - v[a][3]) / (v[b][1] - v[a][1]);
	else
	{
		return (dd(v, a + 1, b) - dd(v, a, b - 1)) / (v[b][1] - v[a][1]);
	}
}