#include <iostream>
#include <iomanip>
#include <ctime>

float* float_array(long n);                 //создание массива с n элементов типа float
double* double_array(long n);               //создание массива с n элементов типа double 
template <class T>
void moving_average(T* a, long n, int k);   //вычисление скользящего среднего  и производительности для конкретного массива

int main(int argc, char* argv[])
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int k = 0;                                             //длина окна
	long n = 0;                                            //общее кличество элементов
	std::cout << std::setprecision(13) << "Введите количество элементов n" << std::endl;
	std::cin >> n;

	int windows[6]{ 4, 8, 16, 32, 64, 128 };               //длины окон, для которых вычислнения производятся автоматически
	float* a_f = float_array(n);                           
	double* a_d = double_array(n);

	std::cout << std::endl << "float:" << std::endl;       //вычисление производительности для случаев 
	for (int i = 0; i < 6; ++i)                            //k = 4, 8, 16, 32, 64 и 128 и типа float
		moving_average(a_f, n, windows[i]);

	std::cout << std::endl << "double:" << std::endl;      //вычисление производительности для случаев
	for (int i = 0; i < 6; ++i)                            //k = 4, 8, 16, 32, 64 и 128 и типа double
		moving_average(a_d, n, windows[i]);

	std::cout << std::endl << "Введите длину окна k, чтобы продолжить" << std::endl;
	std::cout << "Введите 0, чтобы завершить" << std::endl;
	std::cin >> k;

	while (k != 0)                                         //ожидание от пользователя окончания работы программы
	{
		std::cout << "float:" << std::endl;
		moving_average(a_f, n, k);
		std::cout << std::endl << "double:" << std::endl;
		moving_average(a_d, n, k);

		std::cout << std::endl << "Введите длину окна k, чтобы продолжить" << std::endl;
		std::cout << "Введите 0, чтобы завершить" << std::endl;
		std::cin >> k;
	}
	return 0;
}


float* float_array(long n)
{
	float* a = new float[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (float)(rand()) / 32767;                    //заполнение массива числами от 0 до 1 типа float
	}
	return a;
}

double* double_array(long n)
{
	double* a = new double[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = (double)(rand()) / 32767;                   //заполнение массива числами от 0 до 1 типа double
	}
	return a;
}

template <class T>
void moving_average(T* a, long n, int k)
{
	unsigned int start_time = clock();                     //начало работы программы
	T average = 0;                                         //значение скользящего среднего
	for (int i = 0; i < k; ++i)                            
	{
		average += a[i];                                   //вычисление среднего для первых k элементов
	}
	average /= k;

	for (int i = k; i < n; ++i)
	{
		average += (a[i] - a[i - k]) / k;                  //вычисление скользящего среднего от k+1-вого до n-ного элемента
	}
	unsigned int t = clock() - start_time;                 //конец работы программы
	std::cout << "Время действия при k = " << k << ": " << t << std::endl;
	std::cout << "Производительность: " << (double)(n) / t << std::endl;
}