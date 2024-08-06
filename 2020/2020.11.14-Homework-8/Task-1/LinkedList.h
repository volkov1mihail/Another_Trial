#pragma once
#include<iostream>

struct Node 
{
public:
	int data;
	Node* next;
	Node(int data, Node* next = nullptr) :data(data), next(next) {}
};


class LinkedList
{
private:
	int count;
	Node* head;
	Node* tail;
public:
	LinkedList() : count(0), head(nullptr), tail(nullptr) {}
	LinkedList(const LinkedList& list);
	~LinkedList();
private:
	bool indexValid(int index);

public:
	int length();

	bool addToHead(int element);

	bool addToTail(int element);

	bool add(int index, int element);

	int get(int index);

	bool set(int index, int element);

	int& operator[](int index);

	friend std::ostream& operator<<(std::ostream& stream, const LinkedList list);

	void operator+=(int element);

	/// <summary>
	/// удалить начало списка
	/// </summary>
	/// <returns>значение элемента, стоявшего в начале</returns>
	int extractHead();

	/// <summary>
	/// удалить хвост списка
	/// </summary>
	/// <returns>значение элемента, стоявшего в конце</returns>
	int extractTail();

	/// <summary>
	/// удалить элемент, стоящий на месте index
	/// </summary>
	/// <returns>значение элемента, стоявшего на месте index</returns>
	int extract(int index);

	/// <summary>
	/// удалить элемент
	/// </summary>
	/// <param name="">индекс удаляемого элемента</param>
	void operator-=(int index);

	LinkedList& operator=(const LinkedList& list);

	/// <summary>
	/// поиск элемента
	/// </summary>
	/// <param name="">значение искомого</param>
	/// <returns>-1, если элемента в списке нет</returns>
	int indexOf(int element);

	/// <summary>
	/// содержится ли элемент в списке. в функции нужно обойтись одной строкой
	/// </summary>
	/// <param name="">значение элемента</param>
	bool contains(int element);

	/// <summary>
	/// поменять два элемента местами.
	/// Переписывать значения элементов нельзя.
	/// Можно только менять значения полей next.
	/// </summary>
	/// <param name="">индекс первого элемента</param>
	/// <param name="">индекс второго элемента</param>
	/// <returns>false - если индексы были некорректны</returns>
	bool swap(int, int);


	bool last(Node* last);
	bool prelast(Node* prelast);
	bool get_ptr(int n, Node* node);
};
