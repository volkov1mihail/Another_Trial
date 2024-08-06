#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>

double func_f(double x, double t) { return exp(-x * x / 2) * (-t / 4 + 1); }
double initial_conditions(double T, int x, double value);
void record(std::string text, int N1, double T, int numberOfGraphs, double** array);
double** explicitMethod(double T, int N1);
double** implicitMethod(double T, int N1);
int min(int N1, int N2) { return N1 <= N2 ? N1 : N2; }
void comparisonTest(double T, int N1, int N2, int choice);

int main() {
	double T = 0.01;
	int N1 = 1;
	std::cout << "Set the value of N1" << std::endl;
	std::cin >> N1;

	double** u = explicitMethod(T, N1);
	record("Explicit_method", N1, T, 2, u);
	system("start vscodeSource.exe");
	system("pause");

	u = implicitMethod(T, N1);
	record("Implicit_method", N1, T, 2, u);
	system("start vscodeSource.exe");

	//system("pause");
	//comparisonTest(T, 10, 20, 1);
	//comparisonTest(T, 20, 40, 1);

	//system("pause");
	//comparisonTest(T, 10, 20, 2);
	//comparisonTest(T, 20, 40, 2);

	for (int i = 0; i <= N1; ++i) delete[] u[i];
	delete[] u;
	return EXIT_SUCCESS;
}


double initial_conditions(double T, int x, double value) {
	switch (x) {
	case -1:
		return value * value / 2;
	case 0:
		return value;
	case 1:
		return value + 0.5;
	}
	return 0;
}

void record(std::string text, int N1, double T, int numberOfGraphs, double** array) {
	double h = 1.0 / N1;
	double tau = 0.5 * h * h;
	int N2 = (int)round(T / tau);
	std::cout << text << std::endl;
	int isComparisonTest = text[text.size() - 1] == 't' ? 1 : 0;
	std::ofstream out;
	out.open("text.txt");
	if (out.is_open()) {
		out << isComparisonTest << std::endl << text << std::endl;
		out << N1 << std::endl << N2 << std::endl;
		out << h << std::endl << tau << std::endl;
		for (int i = 0; i <= N1; ++i) {
			for (int j = 0; j <= N2; ++j) {
				out << array[i][j] << std::endl;
			}
		}
	}
	out.close();
}

double** explicitMethod(double T, int N1)
{
	double** result = new double* [N1 + 1];
	double h = 1.0 / N1;
	double tau = 0.5 * h * h;
	int N2 = (int)round(T / tau);
	double alpha = tau / h / h;

	double* X = new double[N1 + 1];
	double* t = new double[N2 + 1];
	for (int i = 0; i <= N1; ++i) {
		X[i] = i * h;
		result[i] = new double[N2 + 1];
		result[i][0] = initial_conditions(T, -1, X[i]);
	}
	for (int j = 0; j <= N2; ++j) {
		t[j] = j * tau;
		result[0][j] = initial_conditions(T, 0, t[j]);
		result[N1][j] = initial_conditions(T, 1, t[j]);
	}

	for (int j = 0; j < N2; ++j) {
		for (int i = 1; i <= N1 - 1; ++i) {
			result[i][j + 1] = alpha * (result[i - 1][j] + result[i + 1][j]) + tau * func_f(X[i], t[j]);
		}
	}
	delete[] X; delete[] t;
	return result;
}

double** implicitMethod(double T, int N1)
{
	double** result = new double* [N1 + 1];
	double h = 1.0 / N1;
	double tau = 0.5 * h * h;
	int N2 = (int)round(T / tau);
	double alpha = tau / h / h;
	double constant = 1 / alpha + 2;
	double* X = new double[N1 + 1];
	double* t = new double[N2 + 1];

	for (int i = 0; i <= N1; ++i) {
		X[i] = i * h;
		result[i] = new double[N2 + 1];
		result[i][0] = initial_conditions(T, -1, X[i]);
	}
	for (int j = 0; j <= N2; ++j) {
		t[j] = j * tau;
		result[0][j] = initial_conditions(T, 0, t[j]);
		result[N1][j] = initial_conditions(T, 1, t[j]);
	}

	double* L = new double[N2 + 1];
	double* K = new double[N2 + 1];
	double denominator = 0;
	for (int j = 1; j <= N2; ++j) {
		L[1] = 0;
		K[1] = result[0][j];
		for (int k = 2; k <= N1; ++k) {
			denominator = constant - L[k - 1];
			L[k] = 1 / denominator;
			K[k] = (K[k - 1] + h * h * func_f(X[k - 1], t[j]) + result[k - 1][j - 1] / alpha) / denominator;
		}
		for (int i = N1 - 1; i >= 1; --i)
			result[i][j] = L[i + 1] * result[i + 1][j] + K[i + 1];
	}
	//delete[] t; 
	//delete[] X;
	//delete[] K;
	//delete[] L;
	return result;
}

void comparisonTest(double T, int N1, int N2, int choice)
{
	double** u1;
	double** u2;
	std::string text;
	if (choice == 1) {
		u1 = explicitMethod(T, N1);
		u2 = explicitMethod(T, N2);
		text = "Explicit_Method_Comparison_Test";
	}
	else {
		u1 = implicitMethod(T, N1);
		u2 = implicitMethod(T, N2);
		text = "Implicit_Method_Comparison_Test";
	}
	std::cout << text << ",    N1 = " << N1 << ",    N2 = " << N2 << std::endl;

	int k, quotient, length;
	int M1 = (int)round(T * N1 * N1 * 2);
	int M2 = (int)round(T * N2 * N2 * 2);
	if (N1 <= N2) {
		k = N2 / N1;
		length = M1 + 1;
		quotient = M2 / M1;
		for (int i = 0; i <= N1; ++i) {
			for (int j = 0; j < length; ++j)
				std::cout << "|u1[" << i << "," << j << "] - u2[" << i * k << "," << j * quotient << "]| = " 
				<< abs(u1[i][j]-u2[i*k][j*quotient]) << std::endl;
		}
	}
	else {
		k = N1 / N2;
		length = M2 + 1;
		quotient = M1 / M2;
		for (int i = 0; i <= N2; ++i) {
			for (int j = 0; j < length; ++j)
				std::cout << "|u1[" << i * k << "," << j * quotient << "] - u2[" << i << "," << j << "]| = " 
				<< abs(u1[i * k][j * quotient] - u2[i][j]) << std::endl;
		}
	}

	//record(text, min(N1, N2), T, 2, points);
	//for (int i = 0; i <= min(N1, N2); ++i) delete[] points[i];
	//for (int i = 0; i <= N2; ++i) delete[] u2[i];
	//for (int i = 0; i <= N1; ++i) delete[] u1[i];

	//delete[] u1; delete[] u2; 
	//delete[] points;
}