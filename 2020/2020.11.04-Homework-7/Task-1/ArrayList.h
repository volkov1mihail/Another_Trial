#pragma once
#include<iostream>
class ArrayList
{
private:
	int count;
	int capacity;
	int* data;

public:
	ArrayList(int capacity = 10) : count(0), capacity(capacity), data(new int[capacity]) {}
	ArrayList(const ArrayList& list);
	~ArrayList();

private:

	void expand();

public:

	bool add(int element);

	bool add(int index, int element);

	bool addAll(ArrayList& list);

	bool addAll(int index, ArrayList& list);

	void clear();

	bool contains(int element);

	int get(int index);

	bool set(int index, int element);

	int indexOf(int element);

	bool isEmpty();

	bool remove(int index);

	bool swap(int index1, int index2);

	int length();

	/// <summary>
	/// Добавление элемента в конец списка
	/// </summary>
	void operator+= (int item);
	/// <summary>
	/// удаление последнего вхождения элемента item из списка
	/// </summary>
	void operator-= (int item);
	/// <summary>
	/// оператор присваивания
	/// </summary>
	ArrayList& operator= (const ArrayList& list);
	/// <summary>
	/// добавление элемента в конец списка
	/// </summary>
	friend ArrayList operator+ (const ArrayList& list, int item);
	/// <summary>
	/// добавление элемента в начало списка
	/// </summary>
	friend ArrayList operator+ (int item, const ArrayList& list);
	/// <summary>
	/// сложение списков (list1 встает в конец list2)
	/// </summary>
	friend ArrayList operator+ (const ArrayList& list1, const ArrayList& list2);
	/// <summary>
	/// удаление последнего вхождения элемента item из списка
	/// </summary>
	/// <returns>новый список, в котором отсутствует последний элемент item</returns>
	friend ArrayList operator- (const ArrayList& list, int item);
	/// <summary>
	/// удаление первого элемента из списка
	/// </summary>
	friend ArrayList operator- (int item, const ArrayList& list);
	/// <summary>
	/// вывод списка в поток
	/// </summary>
	friend std::ostream& operator<<(std::ostream& stream, const ArrayList& list);

};