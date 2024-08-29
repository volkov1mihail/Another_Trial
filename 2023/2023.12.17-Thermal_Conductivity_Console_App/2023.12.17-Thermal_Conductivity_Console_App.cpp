#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include<vector>
//Программа находит численное решение уравнения теплопроводности в дифференциальной форме Lu = f, где
//Lu = Du/Dt - a * D^2u/Dx^2 - b * Du/Dx - c * u - дифференциальный оператор(D/Dt - частная производная по времени, a, b, c - функции от t и от x),
//f - неоднородность, задаваемая функцией func_f(). Заданы начальные условия u(x,0) = phi(x), определяемые функцией initial_conditions()
//Решение производится с помощью явного(explicit) и неявного(implicit) методов, сравнение которых реализовано в функции record()
//Так же численные решения обоих методов визуализируются благодаря вызову файла vscodeSource.exe и использования библиотеки graphics.h

double func_f(double x, double t) { return exp(-x * x / 2) * (-t / 4 + 1); }	//Неоднородность дифференциального уравнения
double initial_conditions(double, int, double);											//Начальные условия
void record(std::string, int, double, int, double**);								//Запись численного решения в текстовый файл
double** explicitMethod(double, int);																//Явный метод
double** implicitMethod(double, int);																//Неявный метод
void comparisonTest(double, int, int, int);													//Сравнение решений двух методов
int min(int N1, int N2) { return N1 <= N2 ? N1 : N2; }							//Минимум двух целых чисел
void visualisation();

int main() {
	double T = 0.01;																									//Ограничение по времени (0 <= t <= T)
	int N1 = 1;																												//Число временных отрезок, на которые будет производиться разбиение
	std::cout << "Set the value of N1" << std::endl;
	std::cin >> N1;

	double** u = explicitMethod(T, N1);																//Массив, хранящий значения функции, полученной явным методом
	record("Explicit_method", N1, T, 2, u);														//Запись численного решения в текстовый файл
	system("start vscodeSource.exe");																	//Визуализация решения
	system("pause");

	u = implicitMethod(T, N1);																				//Неявный метод
	record("Implicit_method", N1, T, 2, u);
	visualisation();
	//system("start vscodeSource.exe");

	//system("pause");
	//comparisonTest(T, 10, 20, 1);																		//Сравнение результатов явного метода при удвоении точности разбиения
	//comparisonTest(T, 20, 40, 1);

	//system("pause");
	//comparisonTest(T, 10, 20, 2);																		//Сравнение результатов неявного метода при удвоении точности разбиения
	//comparisonTest(T, 20, 40, 2);

	for (int i = 0; i <= N1; ++i) delete[] u[i];											//Освобождение памяти
	delete[] u;
	return EXIT_SUCCESS;
}


double initial_conditions(double T, int x, double value) {
	switch (x) {
	case -1:
		return value * value / 2;																				//Значение функции точке x = value в момент времени t = 0
	case 0:
		return value;																										//Значение функции в точке x = 0 в момент времени t = value
	case 1:
		return value + 0.5;																							//Значение функции в точке x = 1 в момент времени t = value
	}
	return 0;
}

void record(std::string text, int N1, double T, int numberOfGraphs, double** array) {
	double h = 1.0 / N1;
	double tau = 0.5 * h * h;
	int N2 = (int)round(T / tau);

	std::cout << text << std::endl;
	int isComparisonTest = (text[text.length() - 1] == 't' ? 1 : 0);
	std::ofstream out;
	out.open("text.txt");
	if (out.is_open()) {
		out << isComparisonTest << std::endl << text << std::endl;
		out << N1 << std::endl << N2 << std::endl;
		out << h << std::endl << tau << std::endl;
		for (int i = 0; i <= N1; ++i)
			for (int j = 0; j <= N2; ++j)
				out << array[i][j] << std::endl;
	}
	out.close();
}

double** explicitMethod(double T, int N1)
{
	double** result = new double* [N1 + 1];														//Вектор, содержащий численное решение уравнения теплопроводности
	double h = 1.0 / N1;																							//Ширина шага вдоль координаты x
	int N2 = (int)round(2 * T / (h * h));															//Ширина шага вдоль координаты t
	double tau = T / N2;
	double alpha = tau / h / h;

	double* X = new double[N1 + 1];																		//Массив значений координаты x
	double* t = new double[N2 + 1];																		//Массив значений координаты t
	for (int i = 0; i <= N1; ++i) {																		//Внесение начальных условий в массив result
		X[i] = i * h;
		result[i] = new double[N2 + 1];
		result[i][0] = initial_conditions(T, -1, X[i]);
	}
	for (int j = 0; j <= N2; ++j) {
		t[j] = j * tau;
		result[0][j] = initial_conditions(T, 0, t[j]);
		result[N1][j] = initial_conditions(T, 1, t[j]);
	}

	for (int j = 0; j < N2; ++j) {																		//Численное решение, полученное явным методом
		for (int i = 1; i <= N1 - 1; ++i) {
			result[i][j + 1] = alpha * (result[i - 1][j] + result[i + 1][j]) + tau * func_f(X[i], t[j]);
		}
	}
	return result;
}

double** implicitMethod(double T, int N1)
{
	double** result = new double* [N1 + 1];														//Вектор, содержащий численное решение уравнения теплопроводности
	double h = 1.0 / N1;																							//Ширина шага вдоль координаты x
	int N2 = (int)round(2 * T / (h * h));															//Ширина шага вдоль координаты t
	double tau = T / N2;
	double alpha = tau / h / h;
	double constant = 1 / alpha + 2;

	double* X = new double[N1 + 1];																		//Массив значений координаты x
	double* t = new double[N2 + 1];																		//Массив значений координаты t
	for (int i = 0; i <= N1; ++i) {																		//Внесение начальных условий в массив result
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
	for (int j = 1; j <= N2; ++j) {																		//Численное решение, полученное неявным методом
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
	return result;
}

void comparisonTest(double T, int N1, int N2, int choice)
{
	double** u1;																											//Решение с разбиением N1
	double** u2;																											//Решение с разбиением N2
	std::string text;
	if (choice == 1) {																								//Сравнение решений, полученных явным(choice == 1) или неявным методом(choice == 2)
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
	if (N1 <= N2) {																										//Сравнение двух решений в кратных точках, случай N1 <= N2
		k = N2 / N1;
		length = M1 + 1;
		quotient = M2 / M1;
		for (int i = 0; i <= N1; ++i) {
			for (int j = 0; j < length; ++j)
				std::cout << "|u1[" << i << "," << j << "] - u2[" << i * k << "," << j * quotient << "]| = "
				<< abs(u1[i][j] - u2[i * k][j * quotient]) << std::endl;
		}
	}
	else {																														//Случай N1 > N2
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
}