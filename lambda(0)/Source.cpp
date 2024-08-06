#include<iostream>
#include<armadillo>
#include <iomanip>

using namespace std;
using namespace arma;

double find_diff(vec& L0, vec& L1)
{
	double min[2] = { L0(0) / L1(0), 0 };
	double max[2] = { L0(0) / L1(0), 0 };
	for (int i = 1; i < 4; ++i) {
		if (L0(i) / L1(i) < min[0]) {
			min[0] = L0(i) / L1(i);
			min[1] = i;
		}
		if (L0(i) / L1(i) > max[0]) {
			max[0] = L0(i) / L1(i);
			max[1] = i;
		}
	}
	cout << "L0(" << min[1] << ")/L1(" << min[1] << ") = " << min[0] << " <= w^2 <= " << "L0(" << max[1] << ")/L1(" << max[1] << ") = " << max[0] << endl;
	cout << "difference = " << max[0] - min[0] << endl;
	return max[0] - min[0];
}

void iteration(vec& L0, vec& L1)
{
	double a = 0;
	for (int i = 0; i < 5; ++i) {
		a += L0(i) * L1(i);
	}
	for (int i = 0; i < 5; ++i) {
		L0(i) -= a * L1(i);
	}
	return;
}

void normalize(vec& L)
{
	double n = 0;
	for (int i = 0; i < 5; ++i) {
		n += L(i) * L(i);
	}
	n = sqrt(n);
	for (int i = 0; i < 5; ++i) {
		L(i) /= n;
	}
	return;
}

int main()
{
	cout.precision(10);
	mat A = { {1,0,1 / sqrt(2),0,1 / sqrt(5)},{0,1,0,1 / sqrt(3),1 / sqrt(5)},{1 / sqrt(2),0,2,0,2 * sqrt(2 / 5)},
		{0,1 / sqrt(3),0,1,sqrt(3 / 5)},{1 / sqrt(5),1 / sqrt(5),2 * sqrt(2 / 5),sqrt(3 / 5),11 / 5} };

	A.print();

	double difference = 1;
	vec L0 = { 9.81 / 5 * 26, 9.81 / 5 * 21, 9.81 / 5 * 21, 9.81 / 5 * 16, 9.81 / 5 * 11 };
	L0.raw_print(cout, "L0:");
	normalize(L0);
	cout << endl << "normalized:" << endl;
	L0.raw_print(cout, "L0:");
	cout << endl;

	vec L1(5, fill::ones);
	while (difference > 0.001) {
		L1 = A * L0;
		normalize(L1);
		cout << endl << "normalized:" << endl;
		L1.raw_print(cout, "L1:");
		difference = find_diff(L0, L1);
		L0 = L1;
	}

	cout << endl << "Second form" << endl;

	L0 = { 9.81 / 5 * 26, 9.81 / 5 * 21, 9.81 / 5 * 21, 9.81 / 5 * 16, 9.81 / 5 * 11 };
	normalize(L0);

	cout << endl << "Iterations:" << endl;
	cout << "i = " << 0 << endl;
	L0.raw_print(cout, "L0:");
	iteration(L0, L1);
	cout << endl << "Weighted list:" << endl;
	L0.raw_print(cout, "L0:");
	vec L2 = L0;
	cout << endl;
	for (int i = 1; i <= 100; ++i) {
		L0 = A * L0;
		cout << "i = " << i << endl;
		L0.raw_print(cout, "L0:");
		normalize(L0);
		iteration(L0, L1);
		cout << endl << "Weighted list:" << endl;
		L0.raw_print(cout, "L0:");
		difference = find_diff(L2, L0);
		L2 = L0;
		cout << endl;
	}

	return 0;
}