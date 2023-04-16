#include <iostream>

float* float_array(int n)
{
	float* a = new float[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (float)(rand()) / 32767;
	}
	return a;
}

double* double_array(int n)
{
	double* a = new double[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (double)(rand()) / 32767;
	}
	return a;
}

template <class T>
void moving_average(T* a, int n, int k)
{
	T average = 0;
	for (int i = 0; i < k; ++i)
	{
		average += a[i];
	}
	average /= k;
	//std::cout << average << "  ";
	for (int i = k; i < n; ++i)
	{
		average += (a[i] - a[i - k]) / k;
		//std::cout << average << "  ";
	}
}


int main(int argc, char* argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int k = 0;
	int n = 0;
	std::cout << "¬ведите общее количество элементов n" << std::endl;
	std::cin >> n;
	std::cout << "¬ведите количество отслеживаемых элементов k" << std::endl;
	std::cin >> k;


	float* a_f = float_array(n);
	double* a_d = double_array(n);
	//for (int i = 0; i < n; ++i)
	//{
	//	std::cout << a_f[i] << std::endl;
	//}
	int start_time = clock();
	std::cout << "float:" << std::endl;
	moving_average(a_f, n, k);
	std::cout << std::endl << "double:" << std::endl;
	moving_average(a_d, n, k);

	std::cout << "¬рем€ работы программы:" << clock() - start_time << std::endl;
	return 0;
}