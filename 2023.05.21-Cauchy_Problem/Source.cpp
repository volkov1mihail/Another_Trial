#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

double c1;
double max(double x1, double x2)
{
	return x1 >= x2 ? x1 : x2;
}
double func(double x, double y)
{
	return -y + x;
}
vector<double> Taylor_poly(double x0, double y0, int m);
pair<double, double> Taylor(vector<double> Taylor_0, double x);
double exact_value(double x)
{
	return c1 * exp(-x) + x - 1;
}
double error(double x, vector<double> Taylor_0, double d);
void Adams(vector<pair<double, double>>& v1, vector<vector<double>>& q, int N);
vector<double> difference(vector<double> q);
vector<pair<double, double>> Runge_Kutta(double x0, double y0, double h, int N);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Численное решение Задачи Коши для обыкновенного дифференциального уравнения первого порядка" << endl;
	double x0, y0;
	cout << "Введите значение x0" << endl;
	cin >> x0;
	cout << "Введите значение y0" << endl;
	cin >> y0;
	c1 = exp(x0) * (y0 - x0 + 1);

	cout << "Задача Коши: y'(x) = -y(x) + x, y(" << x0 << ") = " << y0 << endl;
	cout << "Точное решение: y(x) = " << c1 << "*exp(-x)+x-1" << endl;
	double h;
	int N;
	cout << "Введите значение h" << endl;
	cin >> h;
	cout << "Введите значение N" << endl;
	cin >> N;

	vector<pair<double, double>> v;
	pair<double, double> p;
	p.first = x0 - 2 * h;
	p.second = exact_value(p.first);
	v.push_back(p);
	cout << "Значения точного решения:" << endl;
	cout << "y(x_" << -2 << ") = " << p.second << endl;
	for (int i = -1; i <= N; ++i)
	{
		p.first += h;
		p.second = exact_value(p.first);
		v.push_back(p);
		cout << "y(x_" << i << ") = " << p.second << endl;
	}

	double m;
	cout << "Введите, до какой производной считать многочлен Тейлора" << endl;
	cin >> m;
	vector<double> Taylor_0 = Taylor_poly(x0, y0, m);
	cout << "Метод разложения в ряд Тейлора" << endl;
	vector<pair<double, double>> v1;
	for (int i = -2; i <= N; ++i)
	{
		p = Taylor(Taylor_0, v[i + 2].first);
		cout << "y(x_" << i << ") = " << p.first << ", значение абсолютной погрешности: " << abs(v[i + 2].second - p.first) << endl;
		p.second = p.first;
		p.first = v[i + 2].first;
		v1.push_back(p);
	}


	vector<pair<double, double>> v2;
	vector<vector<double>> q;
	q.push_back(Taylor_0);
	q[0].clear();
	for (int i = 0; i < 5; ++i)
	{
		v2.push_back(v1[i]);
		q[0].push_back(func(v1[i].first, v1[i].second) * h);
	}
	Adams(v2, q, N);

	cout << endl << "Экстраполяционный метод Адамса:" << endl;
	for (int i = -2; i <= N; ++i)
		cout << "y(x_" << i << ") = " << v2[i + 2].second << ", значение абсолютной погрешности: " << abs(v2[i + 2].second - v[i + 2].second) << endl;

	cout << endl << "Метод Рунге-Кутты:" << endl;
	vector<pair<double, double>> v3 = Runge_Kutta(x0, y0, h, N);
	for (int i = 0; i <= N; ++i)
		cout << "y(x_" << i << ") = " << v3[i].second << ", значение абсолютной погрешности: " << abs(v3[i].second - v[i + 2].second) << endl;

	cout << endl << "Метод Эйлера:" << endl;
	vector<pair<double, double>> v4;
	p.first = x0;
	p.second = y0;
	v4.push_back(p);
	for (int i = 1; i <= N; ++i)
	{
		p.second += h * func(p.first, p.second);
		p.first += h;
		v4.push_back(p);
		cout << "y(x_" << i << ") = " << v4[i].second << ", значение абсолютной погрешности: " << abs(v4[i].second - v[i + 2].second) << endl;
	}

	cout << endl << "Улучшенный метод Эйлера I:" << endl;
	vector<pair<double, double>> v5;
	p.first = x0;
	p.second = y0;
	double t;
	v5.push_back(p);
	for (int i = 1; i <= N; ++i)
	{
		t = p.second + h * func(p.first, p.second) / 2;
		p.second += h * func(p.first + h / 2, t);
		p.first += h;
		v5.push_back(p);
		cout << "y(x_" << i << ") = " << v5[i].second << ", значение абсолютной погрешности: " << abs(v5[i].second - v[i + 2].second) << endl;
	}

	cout << endl << "Улучшенный метод Эйлера II:" << endl;
	vector<pair<double, double>> v6;
	p.first = x0;
	p.second = y0;
	v6.push_back(p);
	for (int i = 1; i <= N; ++i)
	{
		t = p.second + h * func(p.first, p.second);
		p.second += h * (func(p.first, p.second) + func(p.first + h, t)) / 2;
		p.first += h;
		v6.push_back(p);
		cout << "y(x_" << i << ") = " << v6[i].second << ", значение абсолютной погрешности: " << abs(v6[i].second - v[i + 2].second) << endl;
	}
	return 0;
}



double error(double x, vector<double> Taylor_0, double d)
{
	double x0 = (Taylor_0[1] + Taylor_0[0]);
	if (Taylor_0.size() == 1)
		return max(abs(1 - c1 * exp(-x0)), abs(1 - c1 * exp(-x))) * d;
	if (Taylor_0.size() > 1)
		return max(abs(c1 * exp(x0)), abs(c1 * exp(x))) * d;
	else
	{
		cout << "error could not be calculated" << endl;
		return 0;
	}
}

vector<double> Taylor_poly(double x0, double y0, int m)
{
	vector<double> result;
	result.push_back(y0);
	result.push_back(-y0 + x0);
	result.push_back(-result[1] + 1);
	for (int i = 3; i < m + 1; ++i)
		result.push_back(-result[i - 1]);
	return result;
}

pair<double, double> Taylor(vector<double> Taylor_0, double x)
{
	pair<double, double> result;
	double result1 = Taylor_0[0];
	double d = 1;
	double c = x - (Taylor_0[1] + Taylor_0[0]);
	for (int i = 1; i < Taylor_0.size(); ++i)
	{
		d *= c / i;
		result1 += Taylor_0[i] * d;
	}
	d *= c / Taylor_0.size();
	result.first = result1;
	result.second = error(x, Taylor_0, d);
	return result;
}

void Adams(vector<pair<double, double>>& v1, vector<vector<double>>& q, int N)
{
	if (q[0].size() == 5)
	{
		q.push_back(difference(q[0]));
		q.push_back(difference(q[1]));
		q.push_back(difference(q[2]));
		q.push_back(difference(q[3]));
	}
	pair<double, double> p;
	double h = v1[v1.size() - 1].first - v1[v1.size() - 2].first;
	while (v1.size() <= N + 2)
	{
		p.first = v1[v1.size() - 1].first + h;
		p.second = v1[v1.size() - 1].second + q[0][q[0].size() - 1] + q[1][q[1].size() - 1] / 2 + 5 * q[2][q[2].size() - 1] / 12 + 3 * q[3][q[3].size() - 1] / 8 + 251 * q[4][q[4].size() - 1] / 720;
		v1.push_back(p);
		q[0].push_back(h * func(p.first, p.second));
		q[1].push_back(q[0][q[0].size() - 1] - q[0][q[0].size() - 2]);
		q[2].push_back(q[1][q[1].size() - 1] - q[1][q[1].size() - 2]);
		q[3].push_back(q[2][q[2].size() - 1] - q[2][q[2].size() - 2]);
		q[4].push_back(q[3][q[3].size() - 1] - q[3][q[3].size() - 2]);
	}
}

vector<double> difference(vector<double> q)
{
	vector<double> result;
	for (int i = 0; i < q.size() - 1; ++i)
		result.push_back(q[i + 1] - q[i]);
	return result;
}

vector<pair<double, double>> Runge_Kutta(double x0, double y0, double h, int N)
{
	vector<pair<double, double>> result;
	pair<double, double> p;
	p.first = x0;
	p.second = y0;
	result.push_back(p);
	double k1, k2, k3, k4;
	while (result.size() < N + 1)
	{
		k1 = h * func(result[result.size() - 1].first, result[result.size() - 1].second);
		k2 = h * func(result[result.size() - 1].first + h / 2, result[result.size() - 1].second + k1 / 2);
		k3 = h * func(result[result.size() - 1].first + h / 2, result[result.size() - 1].second + k2 / 2);
		k4 = h * func(result[result.size() - 1].first + h, result[result.size() - 1].second + k3);
		p.first += h;
		p.second += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		result.push_back(p);
	}
	return result;
}