#include<iostream>
#include <clocale>
#include < ctime >
#include < cstdlib >
#include<conio.h>

using namespace std;

void swap(int& a, int& b, double& d);
void fillArray(int* a, int len);
void inputArray(int* a, int len);
void printArray(int* a, int len);
void mixArray(int* a, int len);
bool isSorted(int* a, int len, bool ascending = true);
void bubbleSort(int* a, int len, double& c, double& d);
void insertionSort(int* a, int len, double& c, double& d);
void selectionSort(int* a, int len, double& c, double& d);
void ascendindArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		a[i] = i;
	}
}
void descendindArray(int* a, int len)
{
	for (int i = len - 1; i > 0; --i)
	{
		a[i] = i;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	double c = 0;
	double d = 0;
	int len = 5;
	{
		cout << "len=5" << endl;
		int* a = new int[len];
		fillArray(a, len);
		for (int i = 0; i < 1000; ++i)
		{
			bubbleSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Пузырек:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			insertionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Вставка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;

		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			selectionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Выборка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl << endl;
	}
	c = 0;
	d = 0;
	{
		len = 10;
		cout << "len=10" << endl;
		int* a = new int[len];
		fillArray(a, len);
		for (int i = 0; i < 1000; ++i)
		{
			bubbleSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Пузырек:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			insertionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Вставка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			selectionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Выборка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl << endl;
	}
	c = 0;
	d = 0;
	{
		len = 15;
		cout << "len=15" << endl;
		int* a = new int[len];
		fillArray(a, len);
		for (int i = 0; i < 1000; ++i)
		{
			bubbleSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Пузырек:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			insertionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Вставка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			selectionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Выборка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl << endl;
	}
	c = 0;
	d = 0;
	{
		len = 20;
		cout << "len=20" << endl;
		int* a = new int[len];
		fillArray(a, len);
		for (int i = 0; i < 1000; ++i)
		{
			bubbleSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Пузырек:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			insertionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Вставка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
		c = 0;
		d = 0;
		for (int i = 0; i < 1000; ++i)
		{
			selectionSort(a, len, c, d);
			mixArray(a, len);
		}
		cout << "Выборка:" << endl;
		cout << "Среднее количество сравнений = " << c / 1000 << endl;
		cout << "Среднее количество перестановок = " << d / 1000 << endl;
	}
	return 0;
}

void swap(int& a, int& b, double& d)
{
	int c = a;
	a = b;
	b = c;
	++d;
}

void fillArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		a[i] = rand() % 90 + 10;
	}
}

void inputArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cin >> a[i];
	}
}

void printArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
}

void mixArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		swap(a[i], a[rand() % len]);
	}
}

bool isSorted(int* a, int len, bool ascending)
{
	for (int i = 0; i < len - 1; ++i)
	{
		if (a[i] > a[i + 1] == ascending)
		{
			return false;
		}
	}
	return true;
}

void bubbleSort(int* a, int len, double& c, double& d)
{
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1], d);
				++c;
			}
		}
	}
}

void insertionSort(int* a, int len, double& c, double& d)
{
	for (int i = 1; i < len; ++i)
	{
		int t = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > t)
		{
			a[j] = a[j - 1];
			--j;
			++c;
			++d;
		}
		a[j] = t;
	}
}

void selectionSort(int* a, int len, double& c, double& d)
{
	for (int i = 0; i < len - 1; ++i)
	{
		int index = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (a[j] < a[index])
			{
				index = j;
				++c;
			}
		}
		swap(a[i], a[index], d);
	}
}