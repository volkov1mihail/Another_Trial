#include <iostream>
#include <ctime>
#include "ArrayList.h"

using namespace std;

void printMenu()
{
	cout << "МЕНЮ" << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Добавить в список 10 случайных положительных двузначных чисел и вывести список" << endl;
	cout << "2 - Добавить в список 10 случайных отрицательных двузначных чисел и вывести список" << endl;
	cout << "3 - Поменять местами первый минимальный и последний максимальный элемент и вывести список" << endl;
	cout << "4 - Перемешать все элементы массива и вывести массив" << endl;
	cout << "5 - Заменить каждый отрицательный элемент массива на 0" << endl;
}


void processChoice(ArrayList& a, int choice)
{
	switch (choice)
	{
	case 1:
	{
		for (int i = 0; i < 10; ++i)
		{
			a.add(rand() % 90 + 10);
		}
		cout << a.toString() << endl;
		break;
	}
	case 2:
	{
		for (int i = 0; i < 10; ++i)
		{
			a.add(0 - (rand() % 90 + 10));
		}
		cout << a.toString() << endl;
		break;
	}
	case 3:
	{
		ArrayList b(a.length());
		for (int i = 0; i < a.length(); ++i)
		{
			b.set(i, a.get(i));
		}
		int c = 0;
		for (int i = 0; i < b.length() - 1; ++i)
		{
			for (int j = 0; j < b.length() - 1; ++j)
			{
				if (b.get(i) >= b.get(i + 1))
				{
					b.swap(i, i + 1);
				}
			}
		}
		a.swap(a.indexOf(b.get(0)), a.indexOf(b.get(b.length())));
		cout << a.toString() << endl;
		break;
	}
	case 4:
	{
		//int* d = new int[a.length()];
		//int* f = new int[a.length()];
		//d[0] = rand() % (a.length());
		//f[0] = a.get(d[0]);
		//for (int i = 1; i < a.length() - 1; ++i)
		//{
		//	d[i] = d[i - 1];
		//	for (int j = 0; j < i; ++j)
		//	{
		//		if (d[i] == d[j])
		//		{
		//			d[i] = rand() % (a.length());
		//		}
		//	}
		//	f[i] = a.get(d[i]);
		//}
		//for (int i = 0; i < a.length(); ++i)
		//{
		//	a.set(i, f[i]);
		//}
		//cout<<a.toString()<<endl;
		for (int i = 1; i < a.length() - 1; ++i)
		{
			a.swap(i, rand() % a.length());
		}
		cout << a.toString() << endl;
		break;
	}
	case 5:
	{
		for (int i = 0; i < a.length(); ++i)
		{
			a.set(i, (a.get(i) < 0 ? 0 : a.get(i)));
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
		cin >> choice;
		processChoice(a, choice);
		system("pause");
	} while (choice != 0);

	return EXIT_SUCCESS;
}