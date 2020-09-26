#include <iostream>
using namespace std;
#include <clocale>
#include < ctime >
#include < cstdlib >
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS


void printMenu()    //Просто вывод менюшки ввиде текста
{
	setlocale(LC_ALL, "Russian");
	cout << "Выберите действие:" << endl << endl << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Добавить в массив n случайных чисел в промежутке от a до b " << endl;
	cout << "2 - Развернуть массив" << endl;
	cout << "3 - Поменять элементы массива местами в парах." << endl;
	cout << "4 - Циклический сдвиг вправо на 1" << endl;
	cout << "5 - Развернуть две половинки массива. n - индекс элемента, разделяющего половинки." << endl;
	cout << "6 - Вывести массив на экран" << endl;
}


void addArray(int*& arr, int& cap, int n, int a, int b)
{
	int newCap = cap + n;
	int* temp = new int[newCap] {0};
	for (int i = 0; i < cap; ++i)        //Переписывание значений уже существующих элементов массива
	{
		temp[i] = arr[i];
	}
	for (int i = cap; i < newCap; ++i)
	{
		temp[i] = a + rand() % (b - a + 1);
		cout << "a[" << i << "]=" << temp[i] << endl;
	}
	cap = newCap;
	delete[] arr;
	arr = temp;
}


void expandArray(int*& arr, int& cap, int n)    //Удвоение длинны массива в случае, если оно потребуется
{
	int newCap = n + 1;
	int* temp = new int[newCap] {0};
	for (int i = 0; i < cap; ++i)        //Переписывание значений уже существующих элементов массива
	{
		temp[i] = arr[i];
	}
	cap = newCap;
	delete[] arr;
	arr = temp;
}


void printArray(int*& arr, int& cap)
{
	for (int i = 0; i < cap; ++i)
	{
		cout << "a[" << i << "]=" << arr[i] << endl;
	}
}


void reverseArray(int*& arr, int& cap)
{
	int a = 0;
	for (int i = 0; i < cap / 2; ++i)
	{
		a = arr[i];
		arr[i] = arr[cap - 1 - i];
		arr[cap - 1 - i] = a;
	}
	printArray(arr, cap);
}


void switchArray(int*& arr, int& cap)
{
	int a = 0;
	if (cap % 2 == 0)
	{
		for (int i = 0; i < cap; i += 2)
		{
			a = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = a;
		}
	}
	else
	{
		for (int i = 0; i < cap - 1; i += 2)
		{
			a = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = a;
		}
		cout << "cap-нечетное, поэтому a[cap-1] осталось на своем месте." << endl;
	}
	printArray(arr, cap);
}


void moveArray(int*& arr, int& cap)
{
	int a = arr[0];
	int b = 0;
	int c = arr[cap-1];
	for (int i = 1; i < cap; ++i)
	{
		arr[0] = arr[cap - 1];
		b = arr[i];
		arr[i] = a;
		a = b;
	}
	printArray(arr, cap);
}


void separateArray(int*& arr, int& cap, int n)
{
	int a = 0;
	if ((n == 0)or(n==cap-1))
	{
		reverseArray(arr, cap);
	}
	else if (n < cap-1)
	{
		reverseArray(arr, n);
		for (int i = n; i < (cap + n) / 2; ++i)
		{
			a = arr[i];
			arr[i] = arr[cap + n - 1 - i];
			arr[cap + n - 1 - i] = a;
			cout << "a[" << i << "]=" << arr[i] << endl;
		}
		for (int i = (cap + n) / 2; i < cap; ++i)
		{
			cout << "a[" << i << "]=" << arr[i] << endl;
		}
	}
	else
	{
		--n;
		expandArray(arr, cap, n);
		++n;
		reverseArray(arr, n);
	}
}


void swit(int choice, int*& a, int& cap)
{
	int n = 0;
	int c = 0;
	int b = 0;
	switch (choice)
	{
	case 1:
		cout << "Введите n" << endl;
		cin >> n;
		cout << "Введите a" << endl;
		cin >> c;
		cout << "Введите b" << endl;
		cin >> b;
		addArray(a, cap, n, c, b);
		break;
	case 2:
		reverseArray(a, cap);
		break;
	case 3:
		switchArray(a, cap);
		break;
	case 4:
		moveArray(a, cap);
		break;
	case 5:
		cout << "Введите n" << endl;
		cin >> n;
		separateArray(a, cap, n);
		break;
	case 6:
		printArray(a, cap);
		break;
	}                                     
}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int cap = 8;
	int* a = new int[cap];
	for (int i = 0; i < cap; ++i)   //Присвоение всем элементам массива случайные значения от 0 до 100, иначе они все автоматически сатновятся равны
	{                               //какому-то страшному числу 842150451.
		a[i] = rand() % 101;
	}
	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		printMenu();
		cin >> choice;
		swit(choice, a, cap);
		cout << "Для продолжения нажмите любую клавишу";  //Сделано, чтобы экран не очищался сразу после выполнения вышеуказанных команд
		_getch();                                         //и была возможность прочитать все, что вывела программа.
	}
	delete[] a;
	return EXIT_SUCCESS;
}