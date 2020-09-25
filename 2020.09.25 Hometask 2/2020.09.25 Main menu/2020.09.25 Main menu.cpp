#include <iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include <clocale>


void printMenu()
{
		setlocale(LC_ALL, "Russian");
		cout << "Выберите действие:" << endl << endl << endl;
		cout << "0 - Выход из программы" << endl;
		cout << "1 - Добавить число в массив" << endl;
		cout << "2 - Вывести массив на экран" << endl;
		cout << "3 - Найти номер максимального элемента массива" << endl;
		cout << "4 - Найти минимальный элемент массива" << endl;
		cout << "5 - Посчитать сумму элементов массива" << endl;
		cout << "6 - Вывести массив в обратном порядке" << endl;
}


void expandArray(int* &arr, int &cap)
{
	int newCap = cap * 2;
	int* temp = new int[newCap];
	for (int i = 0; i < cap; ++i)
	{
		temp[i] = arr[i];
	}
	cap = newCap;
	delete[] arr;
	arr = temp;
}


void maxArray(int*& arr, int& cap)
{
	int c = 0;
	for (int i = 0; i < cap; ++i)
	{
		for (int j = 0; j < cap-1; ++j)
		{
			if ((j != i)&(arr[i]<arr[j]))
			{
				break;
			}
			else
			{
				c=i;
			}
		}
	}
	cout<<"Номер максимального элемента="<<c<<endl;
}


void minArray(int*& arr, int& cap)
{
	int c = 0;
	for (int i = 0; i < cap; ++i)
	{
		for (int j = 0; j < cap - 1; ++j)
		{
			if ((j != i) & (arr[i] > arr[j]))
			{
				break;
			}
			else
			{
				c = i;
			}
		}
	}
	cout << "Номер минимального элемента=" << c << endl;
}


int main(int argc, char* argv[])
{
	int n = 0;
	int m = 0;
	char g = 'g';
	int s = 0;
	setlocale(LC_ALL, "Russian");
	int cap = 20;
	int* a = new int[cap];
	for (int i = 0; i < cap; ++i)
	{
		a[i] = 0;
	}
	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			while (g == 'g')
			{
				cout << "Введите номер элемента массива, который хотите заменить" << endl;
				cin >> n;
				while (n >= cap)
				{
					expandArray(a, cap);
				}
				cout << "Введите число" << endl;
				cin >> m;
				a[n] = m;
				cout << "a["<<n<<"]=" << a[n] << endl;
				cout << "Если хотите продолжить, введите \"g\"" << endl;
				cout << "Если хотите вернуться в главное меню, введите \"e\"" << endl;
				g = _getch();
			}
			break;
		case 2:
			for (int i = 0; i < cap; ++i)
			{
				cout << "a[" << i << "]=" << a[i] << " ";
			}
			cout << endl;
			break;
		case 3:
			maxArray(a, cap);
			break;
		case 4:
			minArray(a, cap);
			break;
		case 5:
			for (int i = 0; i < cap; ++i)
			{
				s = a[i] + s;
			}
			cout << "Сумма элементов массива=" << s << endl;
			break;
		case 6:
			for (int i = cap-1; i >=0; --i)
			{
				cout << "a[" << i << "]=" << a[i] << " ";
			}
			cout << endl;
			break;
		}
		cout << "Для продолжения нажмите любую клавишу";
		_getch();
	}


	delete[] a;
	return EXIT_SUCCESS;
}