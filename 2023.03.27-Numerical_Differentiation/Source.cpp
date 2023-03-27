#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

double func(double x)
{
	return exp(3 * x);
}

double f_deriv(double x)
{
	return 3 * exp(3 * x);
}

double s_deriv(double x)
{
	return 9 * exp(3 * x);
}

vector<vector<double>> nodes(int m, double a, double h)
{
	vector<vector<double>> v;
	vector<double> p;
	for (int i = 0; i <= m; ++i)
	{
		p.push_back(a + i * h);
		p.push_back(func(p[0]));
		v.push_back(p);
		p.clear();
	}
	return v;
}

void print(vector<vector<double>> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			if (j == 0)
			{
				cout << "x" << i << " = " << v[i][j] << "   ";
			}
			else if (j == 1)
			{
				cout << "f(x" << i << ") = " << v[i][j] << "   ";
			}
			else if (j == 2)
			{
				cout << "f'(x" << i << ")чд = " << v[i][j] << "   ";
			}
			else if (j == 3)
			{
				cout << "|f'(x" << i << ")т - f'(x" << i << ")чд| = " << v[i][j] << "   ";
			}
			else if (j == 4)
			{
				cout << "f''(x" << i << ")чд = " << v[i][j] << "   ";
			}
			else if (j == 5)
			{
				cout << "|f''(x" << i << ")т - f''(x" << i << ")чд| = " << v[i][j] << "   ";
			}
		}
		cout << endl;
	}
}


int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Нахождение производных таблично-заданной функции по формулам численного дифференцирования" << endl;
	cout << "Вариант 2, функция f(x) = exp(3x)" << endl;

	int m;
	double a, h;
	cout << "Введите число узлов m + 1" << endl;
	cin >> m;
	cout << "Введите начало промежутка a" << endl;
	cin >> a;
	cout << "Введите шаг h" << endl;
	cin >> h;

	vector<vector<double>> v = nodes(m, a, h);
	print(v);

	v[0].push_back((-3 * v[0][1] + 4 * v[1][1] - v[2][1]) / (2 * h));
	v[0].push_back(abs(v[0][2] - f_deriv(v[0][0])));
	v[v.size()-1].push_back((3 * v[v.size()-1][1] - 4 * v[v.size() - 2][1] + v[v.size() - 3][1]) / (2 * h));
	v[v.size()-1].push_back(abs(v[v.size() - 1][2] - f_deriv(v[v.size() - 1][0])));

	v[0].push_back((2 * v[0][1] - 5 * v[1][1] + 4 * v[2][1] - v[3][1]) / (h * h));
	v[0].push_back(abs(v[0][4] - s_deriv(v[0][0])));
	v[v.size()-1].push_back((2 * v[v.size()-1][1] - 5 * v[v.size() - 2][1] + 4 * v[v.size() - 3][1] - v[v.size() - 4][1]) / (h * h));
	v[0].push_back(abs(v[v.size() - 1][4] - s_deriv(v[v.size() - 1][0])));
	for (int i = 1; i < v.size() - 1; ++i)
	{
		v[i].push_back((v[i + 1][1] - v[i - 1][1]) / (2*h));
		v[i].push_back(abs(v[i][2] - f_deriv(v[i][0])));
		v[i].push_back((v[i + 1][1] - 2 * v[i][1] + v[i - 1][1]) / (h * h));
		v[i].push_back(abs(v[i][4] - s_deriv(v[i][0])));
	}
	print(v);
	return 0;
}