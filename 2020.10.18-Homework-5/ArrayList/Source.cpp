#include <iostream>
#include <ctime>
#include "ArrayList.h"

using namespace std;

void printMenu()
{
	 cout << "МЕНЮ" <<  endl;
	 cout << "0 - Выход из программы" <<  endl;
	 cout << "1 - Добавить в список 10 случайных положительных двузначных чисел и вывести список" <<  endl;
	 cout << "2 - Добавить в список 10 случайных отрицательных двузначных чисел и вывести список" <<  endl;
	 cout << "3 - Поменять местами первый минимальный и последний максимальный элемент и вывести список" <<  endl;
	 cout << "4 - Перемешать все элементы массива и вывести массив" <<  endl;
	 cout << "5 - Заменить каждый отрицательный элемент массива на 0" <<  endl;
}


void processChoice(ArrayList& a, int choice)
{
	switch (choice)
	{
	case 1:
	{
		for (int i = 0; i <= 10; ++i)
		{
			a.add(rand() % 90 + 10);
		}
		a.toString();
		break;
	}
	case 2:
	{
		for (int i = 0; i <= 10; ++i)
		{
			a.add(-(rand() % 90 + 10));
		}
		a.toString();
		break;
	}
	case 3:
	{
		ArrayList b(a.capacity);
		for (int i = 0; i < a.length(); ++i)
		{
			b.data[i] = a.data[i];
		}
		int c = 0;
		for (int i = 0; i < b.length() - 1; ++i)
		{
			for (int j = 0; j < b.length() - 1; ++j)
			{
				if (b.data[i] >= b.data[i + 1])
				{
					c = b.data[i];
					b.data[i] = b.data[i + 1];
					b.data[i + 1] = c;
				}
			}
		}
		a.swap(a.indexOf(b.data[0]), a.indexOf(b.data[b.length()]));
		a.toString();
		break;
	}
	case 4:
	{
		int* d = new int[a.length()];
		int* f = new int[a.length()];
		d[0] = rand() % (a.length());
		f[0] = a.data[d[0]];
		for (int i = 1; i < a.length() - 1; ++i)
		{
			d[i] = d[i - 1];
			for (int j = 0; j < i; ++j)
			{
				if (d[i] == d[j])
				{
					d[i] = rand() % (a.length());
				}
			}
			f[i] = a.data[d[i]];
		}
		for (int i = 0; i < a.length(); ++i)
		{
			a.data[i] = f[i];
		}
		a.toString();
		break;
	}
	case 5:
	{
		for (int i = 0; i < a.length(); ++i)
		{
			a.data[i] = (a.data[i] < 0 ? 0 : a.data[i]);
		}
		break;
	}
	}
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	ArrayList a;
	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		std::cin >> choice;
		processChoice(a, choice);
		system("pause");
	} while (choice != 0);

	return EXIT_SUCCESS;
}