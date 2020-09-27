#include <iostream>
using namespace std;
#include <clocale>

int factorial(int a)
{
	int b = a;
	for (int i = 1; i < b; i++)
	{
		a *= i;
	}
	return a;
}


//int deltaFactorial(int a, int b)  //a<b
//{
//	int c = factorial(a);
//	if (a < b)
//	{
//		for (int i = a + 1; i <= b; i++)
//		{
//			c = c * i;
//		}
//	}
//	else if (a == b)
//	{
//		c = c;
//	}
//	return c;
//}


int deltaFactorial(int a, int b, int a1)  //a<b
{
	int c = a1;
	if (a < b)
	{
		for (int i = a + 1; i <= b; i++)
		{
			c = c * i;
		}
	}
	else if (a == b)
	{
		c = a1;
	}
	return c;
}



void sorting(int*& arr, int& cap)
{
	int c = 0;
	for (int j = 0; j < cap; ++j)
	{
		for (int i = 0; i < cap-1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				c = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = c;
			}
		}
	}
	for (int i = 0; i < cap; ++i)
	{
		cout << "a[" << i << "]=" << arr[i] << endl;
	}
}



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	double s = 0;
	int cap = 0;
	cout << "¬ведите число элементов в последовательности {Xn}" << endl;
	cin >> cap;
	int* a = new int[cap] {0};
	int* b = new int[cap] {0};
	cout << "¬ведите "<<cap<<" чисел последовательности {Xn}. Xi должно быть меньше 10" << endl;
	for (int i = 0; i < cap; ++i)
	{
		cin >> a[i];
	}
	sorting(a, cap);
	b[0] = factorial(a[0]);
	cout << "b[0]=" << b[0] << endl;
	for (int i = 1; i < cap; ++i)

	{
		b[i] = deltaFactorial(a[i-1], a[i], b[i-1]);
		s = s + b[i];
		cout << "b[" << i << "]=" << b[i] << endl;
	}
	cout << "—реднее арифметическое факториалов=" << (s + b[0]) / cap << endl;
}