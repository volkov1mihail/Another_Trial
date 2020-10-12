#pragma once
#include<iostream>

using namespace std;

struct ArrayList {
	int count;
	int capacity;
	int* data;

	ArrayList()
	{
		capacity = 10;
		count = 0;
		data = new int[10]{ 0 };
	}

	ArrayList(int cap)
	{
		capacity = cap;
		count = 0;
		data = new int[cap] {0};
	}

	~ArrayList()
	{
		delete[] data;
	}

	bool add(int element)
	{
		if (count == capacity)
		{
			return false;
		}
		else
		{
			data[count] = element;
			++count;
			return true;
		}
	}

	bool add(int index, int element)
	{
		if (count == capacity)
		{
			return false;
		}
		else
		{
			for (int i = count + 1; i > index; --i)
			{
				data[i] = data[i - 1];
			}
			data[index] = element;
			++count;
			return true;
		}
	}

	bool addAll(ArrayList& list)
	{
		if (count > capacity - list.count)
		{
			return false;
		}
		else
		{
			for (int i = count; i < count + list.count; ++i)
			{
				add(list.data[i - count]);
			}
			count += list.count;
			return true;
		}
	}

	bool addAll(int index, ArrayList& list)
	{
		if (count > capacity - list.count)
		{
			return false;
		}
		else
		{
			for (int i = index; i < index + list.count; ++i)
			{
				add(i, list.data[i - index]);
			}
			count += list.count;
			return true;
		}
	}

	bool add_M_Elements()
	{
		cout << "������� ��������, ������� ������ �������� � ������." << endl;
		cout << "����� ���������� �������� ��� �������� � ������ 0, ������� 0." << endl;
		int n = 1;
		while (n != 0)
		{
			cin >> n;
			return add(n);
		}
		--count;
		cout << "����� ������ 0, ��� ������� �������, ������� 1." << endl;
		cout << "����� ��������� ��������, ������� 0." << endl;
		cin >> n;
		if (n == 1)
		{
			return add(0);
		}
	}

	void clear()
	{
		for (int i = 0; i < count; ++i)
		{
			data[i] = 0;
		}
		count = 0;
	}

	bool contains(int element)
	{
		int c = 0;
		for (int i = 0; i < count; ++i)
		{
			if (data[i] == element)
			{
				c = 1;
				break;
				return true;
			}
		}
		if (c == 0)
		{
			return false;
		}
	}

	int get(int index)
	{
		if ((index >= count) or (index < 0))
		{
			return -1;
		}
		else
		{
			return data[index];
		}
	}

	int indexOf(int element)
	{
		int c = 0;
		for (int i = 0; i < count; ++i)
		{
			if (data[i] == element)
			{
				c = 1;
				break;
				return i;
			}
		}
		if (c == 0)
		{
			return -1;
		}
	}

	bool isEmpty()
	{
		return(count == 0 ? true : false);
	}

	void print()
	{
		printf("[%d/%d]{", count, capacity);
		if (count == 0)
		{
			printf("EMPTY");
		}
		else
		{
			for (int i = 0; i < count; ++i)
			{
				printf("%d%s", data[i], (i == count - 1 ? "" : ", "));
			}
		}
		printf("}\n");
	}

	bool remove(int index)
	{
		if ((index >= count) or (index < 0))
		{
			return false;
		}
		else
		{
			for (int i = index; i < count - 1; ++i)
			{
				data[i] = data[i + 1];
			}
			data[count] = 0;
			--count;
			return true;
		}
	}

	bool swap(int index1, int index2)
	{
		if ((index1 >= count) or (index1 < 0) or (index2 >= count) or (index2 < 0))
		{
			return false;
		}
		else
		{
			int c = data[index1];
			data[index1] = data[index2];
			data[index2] = c;
			return true;
		}
	}

};
