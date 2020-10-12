#include<iostream>
#include<clocale>
#include<ctime>
#include"ArrayList.h"

using namespace std;


void printMenu()
{
	cout << "МЕНЮ" << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Вывести массив на экран" << endl;
	cout << "2 - Добавить элемент" << endl;
	cout << "3 - Добавить элемент в позицию" << endl;
	cout << "4 - Удалить элемент по индексу" << endl;
	cout << "5 - Найти элемент" << endl;
	cout << "6 - Добавить несколько элементов" << endl;
	cout << "7 - Добавить несколько элементов, начиная с некоторой позиции" << endl;
}



void processChoice(ArrayList& a, ArrayList& b, int choice, int element, int index)
{
	switch (choice)
	{
	case 1:
		a.print();
		break;
	case 2:
		cout << "Введите элемент, который хотите добавить в список" << endl;
		cin >> element;
		cout << a.add(element) << endl;
		break;
	case 3:
		cout << "Введите элемент, который хотите добавить в список" << endl;
		cin >> element;
		cout << "Введите индекс, который хотите присвоить введенному элементу" << endl;
		cin >> index;
		cout << a.add(index, element) << endl;
		break;
	case 4:
		cout << "Введите индекс элемента, который хотите удалить" << endl;
		cin >> index;
		cout << a.remove(index) << endl;
		break;
	case 5:
		cout << "Введите элемент, который хотите найти" << endl;
		cin >> element;
		cout << a.indexOf(element) << endl;
		break;
	case 6:
		b.add_M_Elements();
		cout << a.addAll(b) << endl;
		break;
	case 7:
		cout << "Введите индекс, с которого хотите добавлять элементы в список" << endl;
		cin >> index;
		b.add_M_Elements();
		cout << a.addAll(index, b) << endl;
		break;
	}
}



int main()
{
	int element = 0;
	int index = 0;
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	ArrayList a;
	ArrayList b;
	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(a, b, choice, element, index);
		system("pause");
	} while (choice != 0);

	return EXIT_SUCCESS;
}