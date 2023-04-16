#include <iostream>
#include <iomanip>
#include <ctime>

float* float_array(long n)
{
	float* a = new float[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (float)(rand()) / 32767;
	}
	return a;
}

double* double_array(long n)
{
	double* a = new double[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (double)(rand()) / 32767;
	}
	return a;
}

template <class T>
int moving_average(T* a, long n, int k)
{
	unsigned int start_time = clock();
	T average = 0;
	for (int i = 0; i < k; ++i)
	{
		average += a[i];
	}
	average /= k;

	for (int i = k; i < n; ++i)
	{
		average += (a[i] - a[i - k]) / k;
	}
	unsigned int end_time = clock();
	return end_time - start_time;
}

template <class T>
void sample(T* a, long n, int k)
{
	int c = moving_average(a, n, k);
	std::cout << "Время работы программы: " << c << std::endl;
	std::cout << " Производительность: " << (double)(n - k) / c << std::endl;
}

int main(int argc, char* argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int k = 0;
	long n = 0;
	std::cout << std::setprecision(13) << "Введите общее количество элементов n" << std::endl;
	std::cin >> n;

	int windows[6]{ 4, 8, 16, 32, 64, 128 };
	float* a_f = float_array(n);
	double* a_d = double_array(n);

	std::cout << "float:" << std::endl;
	for (int i = 0; i < 6; ++i)
		sample(a_f, n, windows[i]);

	std::cout << std::endl << "double:" << std::endl;
	for (int i = 0; i < 6; ++i)
		sample(a_d, n, windows[i]);

	std::cout << std::endl << "Чтобы ввести новую длину окна k, введите желаемое значение" << std::endl;
	std::cout << "Чтобы завершить работу программы, нижмите 0" << std::endl;
	std::cin >> k;

	while (k != 0)
	{
		std::cout << "float:" << std::endl;
		sample(a_f, n, k);
		std::cout << std::endl << "double:" << std::endl;
		sample(a_d, n, k);

		std::cout << std::endl << "Чтобы ввести новую длину окна k, введите желаемое значение" << std::endl;
		std::cout << "Чтобы завершить работу программы, нижмите 0" << std::endl;
		std::cin >> k;
	}
	return 0;
}