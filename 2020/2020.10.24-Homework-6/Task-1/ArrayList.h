#pragma once
class ArrayList
{
private:
	int count;
	int capacity;
	int* data;
	char* str;

public:
	ArrayList(int capacity = 10) :count(0), capacity(capacity), data(new int[capacity]), str(nullptr) {}

	ArrayList(const ArrayList& list);

	~ArrayList();

private:
	void expand();

	int numLength(int number);

	void addToStr(int& index, char symbol);

	void addToStr(int& index, int number);

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

	char* toString();

	bool remove(int index);

	bool swap(int index1, int index2);

	int length();
};