#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <armadillo>

arma::mat middle_rectangle(double a, double b, int n);
arma::mat trapeze(double a, double b, int n);
arma::mat trapezeFirstKind(double a, double b, int n);
double kernel(double x, double y) { return 1 / (10 + cos(x + y)); }
arma::mat entries(double a, double b, int n, arma::mat(*function)(double, double, int));
double func_f(double x) { return sin(M_PI * x); }
arma::vec solution(double a, double b, int n, arma::mat(*function)(double, double, int));
void computationalError(double a, double b, int n1, int n2, arma::mat(*function)(double, double, int));
void computationalErrorFirstKind(double a, double b, int n1, int n2, arma::mat(*function)(double, double, int));
arma::vec solutionFirstKind(double a, double b, int n, arma::mat(*function)(double, double, int));

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n = 0;
	double a{ 0 }, b{ 0 };
	std::cout << "„исленное решение интегрального уравнени¤" << std::endl;
	std::cout << "¬ведите границы промежутка [a,b]" << std::endl;
	std::cin >> a >> b;
	std::cout << "¬ведите число разбиений n" << std::endl;
	std::cin >> n;

	//std::cout << "ћетод средних пр¤моугольников:" << std::endl;
	//arma::vec result = solution(a, b, n, middle_rectangle);
	//for (int i = 0; i < result.n_rows; ++i)
	//	std::cout << "u(x" << i << ") = " << result(i) << std::endl;

	//std::cout << std::endl << "ћетод трапеций:" << std::endl;
	//result = solution(a, b, n, trapeze);
	//for (int i = 0; i < result.n_rows; ++i)
	//	std::cout << "u(x" << i << ") = " << result(i) << std::endl;

	std::cout << std::endl << "ћетод трапеций, уравнение первого рода:" << std::endl;
	arma::vec result = solutionFirstKind(a, b, n, trapezeFirstKind);
	for (int i = 0; i < result.n_rows; ++i)
		std::cout << "u(x" << i << ") = " << result(i) << std::endl;


	//std::cout << "—равнение в кратных точках, метод трапеций, уравнение первого рода:" << std::endl;
	//computationalErrorFirstKind(a, b, 9, 19, trapezeFirstKind);
	//std::cout << std::endl;
	//computationalErrorFirstKind(a, b, 19, 39, trapezeFirstKind);
	//std::cout << std::endl;
	//computationalErrorFirstKind(a, b, 39, 79, trapezeFirstKind);
	//std::cout << std::endl;
	//computationalErrorFirstKind(a, b, 79, 159, trapezeFirstKind);
	//std::cout << std::endl;
	//computationalErrorFirstKind(a, b, 159, 319, trapezeFirstKind);
	//std::cout << std::endl;
	//computationalErrorFirstKind(a, b, 319, 639, trapezeFirstKind);
	//std::cout << "—равнение в кратных точках, метод средних пр¤моугольников:" << std::endl;
	//computationalError(a, b, 10, 20, middle_rectangle);
	//std::cout << std::endl;
	//computationalError(a, b, 20, 40, middle_rectangle);
	//std::cout << std::endl;
	//computationalError(a, b, 40, 80, middle_rectangle);
	//std::cout << std::endl;
	//computationalError(a, b, 80, 160, middle_rectangle);
	//std::cout << std::endl;
	//computationalError(a, b, 160, 320, middle_rectangle);
	//std::cout << std::endl;
	//computationalError(a, b, 320, 640, middle_rectangle);

	//std::cout << "—равнение в кратных точках, метод трапеций:" << std::endl;
	//computationalError(a, b, 9, 19, trapeze);
	//std::cout << std::endl;
	//computationalError(a, b, 19, 39, trapeze);
	//std::cout << std::endl;
	//computationalError(a, b, 39, 79, trapeze);
	//std::cout << std::endl;
	//computationalError(a, b, 79, 159, trapeze);
	//std::cout << std::endl;
	//computationalError(a, b, 159, 319, trapeze);
	//std::cout << std::endl;
	//computationalError(a, b, 319, 639, trapeze);

	return EXIT_SUCCESS;
}

arma::mat middle_rectangle(double a, double b, int n)
{
	arma::mat result = arma::zeros(n + 1, n);
	double h = (b - a) / n;
	double a1 = a + h / 2;
	double x = a1;

	for (int j = 0; j < n; ++j) {
		result(0, j) = a1;
		a1 += h;
	}
	a1 = a + h / 2;

	for (int i = 1; i < n + 1; ++i) {
		for (int j = 0; j < n; ++j) {
			result(i, j) = h * kernel(x, a1);
			a1 += h;
		}
		result(i, i - 1) += 1;
		x += h;
		a1 = a + h / 2;
	}
	return result;
}

arma::mat trapeze(double a, double b, int n)
{
	arma::mat result = arma::zeros(n + 2, n + 1);
	double a1 = a;
	double x = a1;
	double h = (b - a) / n;

	for (int j = 0; j < n + 1; ++j)
	{
		result(0, j) = a1;
		a1 += h;
	}
	a1 = a;

	for (int i = 1; i < n + 2; ++i) {
		for (int j = 1; j < n; ++j) {
			a1 += h;
			result(i, j) = h * kernel(x, a1);
		}
		result(i, 0) = h * kernel(x, a) / 2;
		result(i, n) = h * kernel(x, b) / 2;
		result(i, i - 1) += 1;
		x += h;
		a1 = a;
	}
	for (int i = 1; i < n + 2; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			std::cout << result(i, j) << "   ";
		}
		std::cout << std::endl;
	}
	return result;
}

arma::mat entries(double a, double b, int n, arma::mat(*function)(double, double, int))
{
	arma::mat result = arma::eye(n, n);
	arma::mat coefficients = function(a, b, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			result(i, j) -= coefficients(j, 1);
	}
	return result;
}

arma::vec solution(double a, double b, int n, arma::mat(*function)(double, double, int))
{
	arma::mat matrix = function(a, b, n);
	int length = matrix.n_cols;
	arma::vec RHS = arma::zeros(length, 1);
	for (int i = 0; i < length; ++i)
		RHS(i) = func_f(matrix(0, i));

	arma::mat LHS = arma::zeros(length, length);
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length; ++j)
			LHS(i, j) = matrix(i + 1, j);
	}
	return solve(LHS, RHS);
}

void computationalError(double a, double b, int n1, int n2, arma::mat(*function)(double, double, int))
{
	arma::vec result1 = solution(a, b, n1, function);
	arma::vec result2 = solution(a, b, n2, function);
	int k = 0;
	if (result1.n_rows >= result2.n_rows) {
		k = result1.n_rows / result2.n_rows;
		for (int i = 0; i < result2.n_rows; ++i)
			std::cout << "|u1(x" << i * k << ") - u2(x" << i << ")| = " << abs(result1(i * k) - result2(i)) << std::endl;
	}
	else {
		k = result2.n_rows / result1.n_rows;
		for (int i = 0; i < result1.n_rows; ++i)
			std::cout << "|u1(x" << i << ") - u2(x" << i * k << ")| = " << abs(result1(i) - result2(i * k)) << std::endl;
	}
}

void computationalErrorFirstKind(double a, double b, int n1, int n2, arma::mat(*function)(double, double, int))
{
	arma::vec result1 = solutionFirstKind(a, b, n1, function);
	arma::vec result2 = solutionFirstKind(a, b, n2, function);
	int k = 0;
	if (result1.n_rows >= result2.n_rows) {
		k = result1.n_rows / result2.n_rows;
		for (int i = 0; i < result2.n_rows; ++i)
			std::cout << "|u1(x" << i * k << ") - u2(x" << i << ")| = " << abs(result1(i * k) - result2(i)) << std::endl;
	}
	else {
		k = result2.n_rows / result1.n_rows;
		for (int i = 0; i < result1.n_rows; ++i)
			std::cout << "|u1(x" << i << ") - u2(x" << i * k << ")| = " << abs(result1(i) - result2(i * k)) << std::endl;
	}
}

arma::mat trapezeFirstKind(double a, double b, int n)
{
	arma::mat result = arma::zeros(n + 2, n + 1);
	double a1 = a;
	double x = a1;
	double h = (b - a) / n;

	for (int j = 0; j < n + 1; ++j)
	{
		result(0, j) = a1;
		a1 += h;
	}
	a1 = a;

	for (int i = 1; i < n + 2; ++i) {
		for (int j = 1; j < n; ++j) {
			a1 += h;
			result(i, j) = h * kernel(x, a1);
		}
		result(i, 0) = h * kernel(x, a) / 2;
		result(i, n) = h * kernel(x, b) / 2;
		x += h;
		a1 = a;
	}
	return result;
}

arma::vec solutionFirstKind(double a, double b, int n, arma::mat(*function)(double, double, int))
{
	double alpha = 0.00000001;
	arma::mat matrix = function(a, b, n);
	int length = matrix.n_cols;
	arma::vec RHS = arma::zeros(length, 1);
	for (int i = 0; i < length; ++i)
		RHS(i) = func_f(matrix(0, i));

	arma::mat LHS = arma::zeros(length, length);
	for (int i = 0; i < length; ++i) {
		for (int j = 0; j < length; ++j)
			LHS(i, j) = matrix(i + 1, j);
	}
	//LHS.print();
	arma::mat LHS_transposed = arma::trans(LHS);
	//LHS_transposed.print();
	arma::mat LHS_FirstKind = LHS_transposed * LHS - alpha * arma::eye(length, length);
	//LHS_FirstKind.print();
	arma::vec RHS_FirstKind = LHS_transposed * RHS;
	//RHS_FirstKind.print();
	return solve(LHS_FirstKind, RHS_FirstKind);
}


//double answer(double x, arma::vec )