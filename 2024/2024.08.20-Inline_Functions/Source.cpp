//Сумма двух чисел
//Вычисление факториала
//Поиск максимума в массиве
//Быстрая сортировка
//Умножение двух матриц
//Вычисление чисел Фибоначчи
#include <iostream>
#include <chrono>
#include <clocale>

#define PRINT(var_) {std::cout << #var_ << ": " << (var_) << std::endl;}

const int additionIterations = 10000000;
template <typename T>
void timer(T(*function)(std::string&, T, T), std::string& name, T a, T b) {
	auto start{ std::chrono::high_resolution_clock::now() };
	for (int i = 0; i < additionIterations; ++i)
		function(name, a, b);
	auto end{ std::chrono::high_resolution_clock::now() };
	std::cout << "Время " << name << ":: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " мкс" << std::endl;
}
int addition_int(std::string& name, int a, int b) {
	name = __FUNCTION__;
	return a + b;
}
inline int inline_addition_int(int a, int b) { return a + b; }
double addition_double(double a, double b) { return a + b; }
inline double inline_addition_double(double a, double b) { return a + b; }

int factorial(int n) { return (n <= 1) ? 1 : n * factorial(n - 1); }
inline int inline_factorial(int n) { return (n <= 1) ? 1 : n * inline_factorial(n - 1); }

int maximum(int a, int b) { return (a > b) ? a : b; }
inline int inline_maximum(int a, int b) { return (a > b) ? a : b; }
double maximum(double a, double b) { return (a > b) ? a : b; }
inline double inline_maximum(double a, double b) { return (a > b) ? a : b; }

int maxElement_int(int*, int);
inline int inline_maxElement_int(int*, int);
double maxElement_double(double*, int);
inline double inline_maxElement_double(double*, int);

int maxElement_int_inlineMaximum(int*, int);
inline int inline_maxElement_int_inlineMaximum(int*, int);
double maxElement_double_inlineMaximum(double*, int);
inline double inline_maxElement_double_inlineMaximum(double*, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int* intArray = new int[2 * additionIterations];
	double* doubleArray = new double[2 * additionIterations];

	int a = 4;
	int b = 9;
	double c = 3.27;
	double d = 7.01;
	std::string name;

	timer(addition_int, name, a, b);
	/*timer(inline_addition_int, a, b);
	timer(addition_double, c, d);
	timer(inline_addition_double, c, d);*/

	/*for (int i = 0; i < 2 * additionIterations; ++i) {
		intArray[i] = rand() % 100;
		doubleArray[i] = rand() % 10000 / 100;
	}

	auto start{ std::chrono::high_resolution_clock::now() };
	for (int i = 0; i < additionIterations; i += 2)
		addition_int(intArray[i], intArray[i + 1]);
	auto end{ std::chrono::high_resolution_clock::now() };
	std::cout << "Время addition_int:: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " мкс" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < additionIterations; i += 2)
		inline_addition_int(intArray[i], intArray[i + 1]);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Время inline_addition_int:: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " мкс" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < additionIterations; i += 2)
		addition_double(doubleArray[i], doubleArray[i + 1]);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Время addition_double:: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " мкс" << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < additionIterations; i += 2)
		inline_addition_double(doubleArray[i], doubleArray[i + 1]);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Время inline_addition_double:: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " мкс" << std::endl*/;


	return 0;
}


int maxElement_int(int* array, int length) {
	if (length == 0)
		return 0;

	int max = array[0];
	for (int i = 0; i < length; ++i)
		max = maximum(max, array[i]);
	return max;
}

inline int inline_maxElement_int(int* array, int length) {
	if (length == 0)
		return 0;

	int max = array[0];
	for (int i = 0; i < length; ++i)
		max = maximum(max, array[i]);
	return max;
}

double maxElement_double(double* array, int length) {
	if (length == 0)
		return 0;

	double max = array[0];
	for (int i = 0; i < length; ++i)
		max = maximum(max, array[i]);
	return max;
}

inline double inline_maxElement_double(double* array, int length) {
	if (length == 0)
		return 0;

	double max = array[0];
	for (int i = 0; i < length; ++i)
		max = maximum(max, array[i]);
	return max;
}

int maxElement_int_inlineMaximum(int* array, int length) {
	if (length == 0)
		return 0;

	int max = array[0];
	for (int i = 0; i < length; ++i)
		max = inline_maximum(max, array[i]);
	return max;
}

inline int inline_maxElement_int_inlineMaximum(int* array, int length) {
	if (length == 0)
		return 0;

	int max = array[0];
	for (int i = 0; i < length; ++i)
		max = inline_maximum(max, array[i]);
	return max;
}

double maxElement_double_inlineMaximum(double* array, int length) {
	if (length == 0)
		return 0;

	double max = array[0];
	for (int i = 0; i < length; ++i)
		max = inline_maximum(max, array[i]);
	return max;
}

inline double inline_maxElement_double_inlineMaximum(double* array, int length) {
	if (length == 0)
		return 0;

	double max = array[0];
	for (int i = 0; i < length; ++i)
		max = inline_maximum(max, array[i]);
	return max;
}


template <typename T>
void timer(T (*function)(T, T), T a, T b) {

}