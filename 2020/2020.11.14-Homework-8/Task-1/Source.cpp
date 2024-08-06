/*продемонстрировать работу всех функций
показать, что все функции и операторы корректно работают:
1). С пустым списком.
2). Со списком из 1 элемента.
3). Со списком из нескольких элементов.
*/

#include<iostream>
#include "LinkedList.h"

using namespace std;

void printList(LinkedList list)
{
	cout << "PRINTED LIST : " << list << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	LinkedList list1;
	LinkedList list2;
	LinkedList list3;

	for (int i = 1; i < 6; ++i) 
	{
		list1.addToHead(6 - i);
	}
	for (int i = 6; i < 11; ++i) 
	{
		list1.addToTail(i);
	}
	list3.addToHead(99);
	cout << "list 1 = " << list1 << endl;
	cout << "list 2 = " << list2 << endl;
	cout << "list 3 = " << list3 << endl;

	list1.extractHead();
	cout << "list 1 = " << list1 << endl;

	list1.extractHead();
	cout << "list 1 = " << list1 << endl;
	list1.extractTail();
	cout << "list 1 = " << list1 << endl;
	list1.extract(2);
	cout << "list 1 = " << list1 << endl;
	list1.extract(22);
	cout << "list 1 = " << list1 << endl;
	list1 -= 4;
	list1 -= 44;
	cout << "list 1 = " << list1 << endl;
	cout << "list 3.indexOf(99)=" << list3.indexOf(99) << endl;
	cout << "list 1.indexOf(3)=" << list1.indexOf(3) << endl;
	cout << "list 1.indexOf(4)=" << list1.indexOf(4) << endl;
	cout << "list 1.indexOf(6)=" << list1.indexOf(6) << endl;
	cout << "list 1.indexOf(7)=" << list1.indexOf(7) << endl;
	cout << "list 1.indexOf(9)=" << list1.indexOf(9) << endl;

	cout << list1.indexOf(56) << endl;
	cout << (list1.contains(8) == true ? "8 is in the list 1" : "8 is not in the list 1") << endl;
	cout << (list1.contains(999) == true ? "999 is in the list 1" : "999 is not in the list 1") << endl;
	cout << (list2.contains(99) == true ? "99 is in the list 2" : "99 is not in the list 2") << endl;
	cout << (list2.contains(8) == true ? "8 is in the list 2" : "8 is not in the list 2") << endl;
	cout << (list3.contains(99) == true ? "99 is in the list 3" : "99 is not in the list 3") << endl;
	cout << (list3.contains(8) == true ? "8 is in the list 3" : "8 is not in the list 3") << endl;

	cout << endl;
	cout << "LIST" << list1 << endl;
	cout << list1.get(5) << endl;
	cout << list1.get(2) << endl;
	list1.set(4, 65);
	cout << list1 << endl;

	list1.set(3, 4);
	cout << list1 << endl;
	list1.set(4, 65);
	cout << list1 << endl;
	cout << "Some shit" << endl;
	list1.addToTail(10);
	cout << list1 << endl;
	list1.set(5, 44);


	cout << "list 1[2] = " << list1[2] << endl;
	list1[1] = 12354;
	cout << "list 1[1] = " << list1[1] << endl;
	cout << list1 << endl;
	list1[-12] = -12;
	list1[5123] = 1;
	cout << list1 << endl;

	cout << "SWAP" << endl;
	list1.swap(2, 3);
	cout << "list 1 = " << list1 << endl;
	list1.swap(0, 1);
	cout << "list 1 = " << list1 << endl;
	list1.swap(1, 2);
	cout << "list 1 = " << list1 << endl;
	list1.swap(1, 3);
	cout << "list 1 = " << list1 << endl;

	return 0;
}