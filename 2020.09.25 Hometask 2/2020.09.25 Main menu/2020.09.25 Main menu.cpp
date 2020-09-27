#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <clocale>
#include < ctime >
#include < cstdlib >
#include<conio.h>
using namespace std;


void printMenu()    //Просто вывод менюшки ввиде текста
{
	setlocale(LC_ALL, "Russian");
	cout << "Выберите действие:" << endl << endl << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Добавить число в массив" << endl;
	cout << "2 - Вывести массив на экран" << endl;
	cout << "3 - Найти номер максимального элемента массива" << endl;
	cout << "4 - Найти номер минимального элемента массива" << endl;
	cout << "5 - Посчитать сумму элементов массива" << endl;
	cout << "6 - Вывести массив в обратном порядке" << endl;
}


void printArray(int*& arr, int& cap)
{
	if (cap >= 0)
	{
		for (int i = 0; i < cap; ++i)
		{
			cout << "a[" << i << "]=" << arr[i] << endl;
		}
	}
	else
	{
		for (int i = 1; i <= abs(cap); ++i)
		{
			cout << "a[" << abs(cap) - i << "]=" << arr[abs(cap) - i] << endl;
		}
	}
}


void expandArray(int*& arr, int& cap)    //Удвоение длинны массива в случае, если оно потребуется
{
	int newCap = cap * 2;
	int* temp = new int[newCap] {0};
	for (int i = 0; i < cap; ++i)        //Переписывание значений уже существующих элементов массива
	{
		temp[i] = arr[i];
	}
	cap = newCap;
	delete[] arr;
	arr = temp;
}


int sumArray(int*& arr, int& cap)
{
	int s = 0;
	for (int i = 0; i < cap; ++i)  //Подсчет суммы элементов массива
	{
		s = arr[i] + s;
	}
	return s;
}


int minArray(int*& arr, int& cap)  //Все то же самое, только номер минимального элемента.
{
	int c = 0;
	int a = 101;
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


int maxArray(int*& arr, int& cap)  //Нахождение номера макимального элемента массива(на самом деле, если таких элементов несколько,
{                                   //то выдается номер последнего из них. Можно было запариться и выводить номера всех таких элементов,
	int c = 0;                      //но...........)
	int a = 0;
	for (int i = 0; i < cap; ++i)
	{
		for (int j = 0; j < cap; ++j)
		{
			if ((arr[i] >= arr[j]) & (arr[i] >= a))
			{
				a = arr[i];
				c = i;
			}
		}
	}
	return c;
}


int swit(int choice, int*& arr, int& cap)
{
	int n = 0;
	int m = 0;
	char g = 'g';
	switch (choice)
	{
	case 1:
		while (g == 'g')  //Проверка, продолжать ли операцию замены значений элементов массива
		{
			cout << "Введите номер элемента массива, который хотите заменить" << endl;
			cin >> n;
			while (n >= cap)
			{
				expandArray(arr, cap);
			}
			cout << "Введите число" << endl;
			cin >> m;
			arr[n] = m;
			cout << "a[" << n << "]=" << arr[n] << endl;
			cout << "Если хотите продолжить, введите \"g\"" << endl;
			cout << "Если хотите вернуться в главное меню, введите \"e\"" << endl;
			g = _getch();
		}
		g = 'g';
		break;
	case 2:
		printArray(arr, cap);
		break;
	case 3:
		n = maxArray(arr, cap);
		cout << "Номер максимального элемента=" << n << ", a[" << n << "]=" << arr[n] << endl;
		break;
	case 4:
		n = minArray(arr, cap);
		cout << "Номер минимального элемента=" << n << ", a[" << n << "]=" << arr[n] << endl;
		break;
	case 5:
		n = sumArray(arr, cap);
		cout << "Сумма элементов массива=" << n << endl;
		n = 0;
		break;
	case 6:
		cap = -cap;
		printArray(arr, cap);
		cap = -cap;
		break;
	}
	cout << "Для продолжения нажмите любую клавишу";  //Сделано, чтобы экран не очищался сразу после выполнения вышеуказанных команд
	system("pause");
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int cap = 20;
	int* a = new int[cap];
	for (int i = 0; i < cap; ++i)
	{
		a[i] = rand() % 101;
	}
	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		printMenu();
		cin >> choice;
		swit(choice, a, cap);
	}
	delete[] a;
	return EXIT_SUCCESS;
}
