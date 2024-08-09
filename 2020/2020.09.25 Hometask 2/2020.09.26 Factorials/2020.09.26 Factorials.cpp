#include <iostream>

int factorial(int a) {																//функция, вычисляющая факториал числа a
	int b = a;																					//нужна для вычисления факториала наименьшего элемента в массиве
	for (int i = 1; i < b; i++)													//не обязательная функция, т.к. эту же цель можно добиться, используя функцию deltaFactorial
		a *= i;

	return a;
}

int deltaFactorial(int a, int b, int a1) {						//функция, вычисляющая факториал числа b, если известен факториал числа a(a!=a1)
	int c = a1;																					//подразумевается, что a <= b и для вычисления b! достаточно домножить a! на недостающие множители
	if (a < b)																					//чтобы не использовать функцию factorial, достаточно вычислить факториал наименьшего 
		for (int i = a + 1; i <= b; i++)									//элемента в массиве, как a! = deltaFacrotial(1, a, 1) (пользуясь тем, что 1! = 1) 
			c = c * i;
	else if (a == b)
		c = a1;

	return c;
}

void sorting(int*& arr, int& cap) {										//bubbleSort, позволяющий убедиться в том, что в функцию deltaFactorial подаются числа a < b
	int c = 0;
	for (int j = 0; j < cap; ++j) {
		for (int i = 0; i < cap - 1; ++i) {
			if (arr[i] > arr[i + 1]) {
				c = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = c;
			}
		}
	}
	std::cout << "Отсортированный массив:" << std::endl;
	for (int i = 0; i < cap; ++i)
		std::cout << "a[" << i << "] = " << arr[i] << std::endl;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	double s = 0;
	int cap = 0;
	std::cout << "Введите число элементов в последовательности {Xn}" << std::endl;
	std::cin >> cap;

	int* a = new int[cap] {0};
	int* b = new int[cap] {0};
	std::cout << "Введите " << cap << " чисел последовательности {Xn}. Xi должно быть меньше 10" << std::endl;
	for (int i = 0; i < cap; ++i)
		std::cin >> a[i];

	sorting(a, cap);
	std::cout << std::endl << "Массив факториалов:" << std::endl;
	b[0] = factorial(a[0]);
	std::cout << "b[0] = " << b[0] << std::endl;
	for (int i = 1; i < cap; ++i) {
		b[i] = deltaFactorial(a[i - 1], a[i], b[i - 1]);
		s = s + b[i];
		std::cout << "b[" << i << "] = " << b[i] << std::endl;
	}
	std::cout << "Среднее арифметическое факториалов = " << (s + b[0]) / cap << std::endl;

	return EXIT_SUCCESS;
}