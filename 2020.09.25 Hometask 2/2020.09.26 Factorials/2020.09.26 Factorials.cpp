#include <iostream>
using namespace std;
#include <clocale>

int factorial(int a)
{
	int b = a;
	for (int i = 1; i <= b; i++)
	{
		a *= i;
	}
	return a;
}


int addFactorial(int a, int b)  //a<b
{
	int c = factorial(a);
	for (int i = a+1; i <= b; ++i)
	{
		c = c * i;
	}
	return c;
}


int minArray(int*& arr, int& cap)  //Все то же самое, только номер минимального элемента.
{
	int c = 0;
	int a = 51;
	for (int i = 0; i < cap; ++i)
	{
		for (int j = 0; j < cap; ++j)
		{
			if ((arr[i] <= arr[j]) & (arr[i] <= a))
			{
				a = arr[i];
				c = i;
			}
		}
	}
	return arr[c];
}



int minNumber(int*& arr, int& cap)  //Все то же самое, только номер минимального элемента.
{
	int c = 0;
	int a = 51;
	for (int i = 0; i < cap; ++i)
	{
		for (int j = 0; j < cap; ++j)
		{
			if ((arr[i] <= arr[j]) & (arr[i] <= a))
			{
				a = arr[i];
				c = i;
			}
		}
	}
	return c;
}


int shortMin(int*& arr, int& cap, int x, int n)
{

}



int main(int argc, char* argv[])
{
	int cap = 10;
	int* a = new int[cap];
	cout << "Введите 10 чисел последовательности {Xn}. Xi должно быть меньше 50" << endl;
	for (int i = 0; i < cap; ++i)
	{
		cin >> a[i];
		a[i] = factorial(a[i]);
	}
}