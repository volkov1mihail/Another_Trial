#pragma once
#include<iostream>

struct ArrayList {
	int count;
	int capacity;
	int* data;

	ArrayList();

	ArrayList(int cap);

	~ArrayList();

	bool add(int element);

	bool add(int index, int element);

	bool addAll(ArrayList& list);

	bool addAll(int index, ArrayList& list);

	bool add_M_Elements(int index);
	//bool add_M_Elements(int index);
	void clear();

	bool contains(int element);

	int get(int index);

	int indexOf(int element);

	bool isEmpty();

	void print();

	bool remove(int index);

	bool swap(int index1, int index2);
};