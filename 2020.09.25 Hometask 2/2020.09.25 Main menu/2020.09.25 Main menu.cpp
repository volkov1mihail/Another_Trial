#include <iostream>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#include<conio.h>
#include <clocale>
#include < ctime >
#include < cstdlib >


void printMenu()    //Просто вывод менюшки ввиде текста
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


void expandArray(int* &arr, int &cap)    //Удвоение длинны массива в случае, если оно потребуется
{
	int newCap = cap * 2;
	int* temp = new int[newCap];
	for (int i = 0; i < cap; ++i)        //Переписывание значений уже существующих элементов массива
	{
		temp[i] = arr[i];
	}
	for (int i = cap; i < newCap; ++i)   //Присвоение новым элементам массива значение 0, чтобы сумма элементов массива не изменилась
	{
		temp[i] = 0;
	}
	cap = newCap;
	delete[] arr;
	arr = temp;
}


void maxArray(int*& arr, int& cap)  //Нахождение номера макимального элемента массива(на самом деле, если таких элементов несколько,
{                                   //то выдается номер последнего из них. Можно было запариться и выводить номера всех таких элементов,
	int c = 0;                      //но...........
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


void minArray(int*& arr, int& cap)  //Все то же самое, только номер минимального члена.
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
	int n = 0;     //Номер элемента массива, который хотят заменить
	int m = 0;     //Число, на которое заменяют элемент массива
	char g = 'g';  //Переменная для считывания буквы с клавиатуры
	int s = 0;     //Сумма элементов массива
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int cap = 20;
	int* a = new int[cap];
	for (int i = 0; i < cap; ++i)   //Присвоение всем элементам массива случайные значения от 0 до 100, иначе они все автоматически сатновятся равны
	{                               //какому-то страшному числу 842150451.
		a[i] = rand() % 101;        //При каждом запуске получаются одинаковые "случайные" числа, и не ясно, как это исправить.......
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
			while (g == 'g')  //Проверка, продолжать ли операцию замены значений элементов массива
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
				cout << "a[" << n << "]=" << a[n] << endl;
				cout << "Если хотите продолжить, введите \"g\"" << endl;
				cout << "Если хотите вернуться в главное меню, введите \"e\"" << endl;
				g = _getch();
			}
			break;
		case 2:
			for (int i = 0; i < cap; ++i)  //Вывод элементов массива
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
			for (int i = 0; i < cap; ++i)  //Подсчет суммы элементов массива
			{
				s = a[i] + s;
			}
			cout << "Сумма элементов массива=" << s << endl;
			s = 0;
			break;
		case 6:
			for (int i = cap - 1; i >= 0; --i)  //Вывод в обратном порядке
			{
				cout << "a[" << i << "]=" << a[i] << " ";
			}
			cout << endl;
			break;
		}
		cout << "Для продолжения нажмите любую клавишу";  //Сделано, чтобы экран не очищался сразу после выполнения вышеуказанных команд
		_getch();                                         //и была возможность прочитать все, что вывела программа.
	}
	delete[] a;
	return EXIT_SUCCESS;
}