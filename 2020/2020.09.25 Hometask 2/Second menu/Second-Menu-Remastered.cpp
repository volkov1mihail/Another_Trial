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
	cout << "1 - Добавить в массив n случайных чисел в промежутке от a до b " << endl;
	cout << "2 - Развернуть массив" << endl;
	cout << "3 - Поменять элементы массива местами в парах." << endl;
	cout << "4 - Циклический сдвиг вправо на 1" << endl;
	cout << "5 - Развернуть две половинки массива. n - индекс элемента, разделяющего половинки." << endl;
	cout << "6 - Вывести массив на экран" << endl;
}

void expandArray(int*& arr, int& cap, int n){							//функция, увеличивающая длину массива путем инициализации нового массива с 
	int newCap = n + 1;													//требуемой длиной и переписывания в него элементов из предыдущего массив
	int* temp = new int[newCap] {0};
	for (int i = 0; i < cap; ++i)       
		temp[i] = arr[i];

	cap = newCap;
	delete[] arr;
	arr = temp;
}

void addArray(int*& arr, int& cap, int n, int a, int b, int& count){	//добавление в конец массива n случайных чисел в промежутке от a до b
	if (count + n > cap - 1){
		int d = n;
		n = count + n - 1;
		expandArray(arr, cap, n);
		for (int i = count; i < cap; ++i)
			arr[i] = a + rand() % (b - a + 1);
		n = d;
	}
	else
		for (int i = count; i < count + n; ++i)
			arr[i] = a + rand() % (b - a + 1);

	count = count + n;
}

void printArray(int* arr, int count){									//вывод массива на экран
	for (int i = 0; i < count; ++i)
		cout << "a[" << i << "]=" << arr[i] << endl;
}

void reverseArray(int* arr, int count){									//разворот массива
	int a = 0;
	for (int i = 0; i < count / 2; ++i){
		a = arr[i];
		arr[i] = arr[count - 1 - i];
		arr[count - 1 - i] = a;
	}
}

void swapPairsArray(int* arr, int count){								//массив разбивается на последовательные пары чисел, после чего в каждой паре						
	int a = 0;															//порядок чисел меняется местами
	int i = 0;
	while (i < count - 1){
		a = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = a;
		i += 2;
	}
}

void shiftArray(int* arr, int count){									//циклический сдвиг элементов массива вправо на 1
	int c = arr[count - 1];
	for (int i = count - 1; i > 0; --i)
		arr[i] = arr[i - 1];
	arr[0] = c;
}

void separateArray(int* arr, int count, int n){							//массив разделяется индексом n на два подмассива, после чего каждый подмассив разворачивается
	if ((n < 0) || (n >= count)){										//если число n меньше 0 или больше длины массива, то считается, что весь массив считается за 
		reverseArray(arr, count);										//один из подмассивов и разворачивается
		return;
	}
	else{
		reverseArray(arr, n);
		reverseArray(arr + n, count - n);
	}
}

void swit(int choice, int*& a, int& cap, int count){
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
		addArray(a, cap, n, c, b, count);
		printArray(a, cap);
		break;
	case 2:
		reverseArray(a, cap);
		printArray(a, cap);
		break;
	case 3:
		swapPairsArray(a, cap);
		printArray(a, cap);
		break;
	case 4:
		shiftArray(a, cap);
		printArray(a, cap);
		break;
	case 5:
		cout << "Введите n" << endl;
		cin >> n;
		separateArray(a, cap, n);
		printArray(a, cap);
		break;
	case 6:
		printArray(a, cap);
		break;
	}
}

int main(int argc, char* argv[])
{
	int count = 0;
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int cap = 6;
	int* a = new int[cap] {0};
	for (int i = 0; i < cap; ++i)										//всем элементам массива присваиваются случайные значения от 0 до 100
		a[i] = rand() % 101;											

	int choice = -1;
	while (choice != 0){
		system("cls");
		printMenu();
		cin >> choice;
		swit(choice, a, cap, count);
		system("pause");
		cout << "Для продолжения нажмите любую клавишу" << endl;		//Сделано, чтобы экран не очищался сразу после выполнения вышеуказанных команд                                       //и была возможность прочитать все, что вывела программа.
	}

	delete[] a;
	return EXIT_SUCCESS;
}