#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
using namespace std;


void printMenu(){														//Вывод меню на экран
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

void printArray(int*& arr, int& capacity){								//вывод элементов массива от нулевого до capacity-1
	if (capacity >= 0)													//если capacity < 0, массив будет выводиться в обратном порядке
		for (int i = 0; i < capacity; ++i)
			cout << "a[" << i << "]=" << arr[i] << endl;
	else
		for (int i = 1; i <= abs(capacity); ++i)
			cout << "a[" << abs(capacity) - i << "]=" << arr[abs(capacity) - i] << endl;
}

void expandArray(int*& arr, int& capacity){								//функция, удваивающая длину массива путем инициализации нового массива с 
	int newcapacity = capacity * 2;										//увеличенной длиной и переписывания в него элементов из предыдущего массива
	int* temp = new int[newcapacity] {0};
	for (int i = 0; i < capacity; ++i)
		temp[i] = arr[i];

	capacity = newcapacity;
	delete[] arr;
	arr = temp;
}

int sumArray(int*& arr, int& capacity){									//подсчет суммы элементов массива
	int s = 0;
	for (int i = 0; i < capacity; ++i)
		s = arr[i] + s;

	return s;
}

int minArray(int*& arr, int& capacity){									//нахождение минимального элемента в массиве
	int c = 0;															//если таких элементов несколько, вернется номер последнего из них
	for (int i = 0; i < capacity; ++i)
		c = (arr[c] >= arr[i] ? i : c);

	return c;
}

int maxArray(int*& arr, int& capacity){									//нахождение макимального элемента в массиве
	int c = 0;															//если таких элементов несколько, вернется номер последнего из них
	int a = 0;									
	for (int i = 0; i < capacity; ++i)										
		c = (arr[c] <= arr[i] ? i : c);

	return c;
}

void swit(int choice, int*& arr, int& capacity){						//функция, с помощью которой пользователь может выбирать опции, предложенные в меню
	int n = 0;
	int m = 0;
	char g = 'g';
	switch (choice)
	{
	case 1:
		while (g == 'g')												//Проверка, продолжать ли операцию замены значений элементов массива
		{																//таким образом, можно последовательно заменить или добавить несколько элементов в массив, не возвращаясь в меню
			cout << "Введите номер элемента массива, который хотите заменить" << endl;
			cin >> n;
			while (n >= capacity)
				expandArray(arr, capacity);

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
		printArray(arr, capacity);
		break;
	case 3:
		n = maxArray(arr, capacity);
		cout << "Номер максимального элемента=" << n << ", a[" << n << "]=" << arr[n] << endl;
		break;
	case 4:
		n = minArray(arr, capacity);
		cout << "Номер минимального элемента=" << n << ", a[" << n << "]=" << arr[n] << endl;
		break;
	case 5:
		n = sumArray(arr, capacity);
		cout << "Сумма элементов массива=" << n << endl;
		n = 0;
		break;
	case 6:
		capacity = -capacity;
		printArray(arr, capacity);
		capacity = -capacity;
		break;
	}
	cout << "Для продолжения нажмите любую клавишу";					//Сделано, чтобы экран не очищался сразу после выполнения вышеуказанных команд
	system("pause");
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int capacity = 20;
	int* a = new int[capacity];
	for (int i = 0; i < capacity; ++i)
		a[i] = rand() % 101;

	int choice = -1;
	while (choice != 0)
	{
		system("cls");
		printMenu();
		cin >> choice;
		swit(choice, a, capacity);
	}
	delete[] a;
	return EXIT_SUCCESS;
}
