#include<iostream>
#include<cmath>
#include<iomanip>
#include<clocale>

using namespace std;

double myFunction(double x, int n)
{
	double s = 1;
	double d = -x * x / 2;
	for (int i = 2; abs(d) >= pow(10, -n); i += 2)
	{
		s += d;
		d = -d * x * x / (i + 1) / (i + 2);
	}
	return s;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	double x = 0;
	int n = 0;
	cout << "¬ведите x - размер угла в градусах" << endl;
	cin >> x;
	x = x * acos(-1) / 180;
	cout << "¬ведите n - пор€док точности" << endl;
	cin >> n;
	cout << "p=" << p << endl;
	cout << "cos(" << setprecision(n)<< x << ")=" << cos(x) << endl;
	cout << "cos(" << x << ")~" << myFunction(x, n) << endl;
	return 0;
}