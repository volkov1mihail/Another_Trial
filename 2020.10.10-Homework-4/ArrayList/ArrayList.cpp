#include"ArrayList.h"

using namespace std;


ArrayList::ArrayList()
{
	capacity = 10;
	count = 0;
	data = new int[10]{ 0 };
}


ArrayList::ArrayList(int cap)
{
	capacity = cap;
	count = 0;
	data = new int[cap] {0};
}


ArrayList::~ArrayList()
{
	delete[] data;
}


bool ArrayList::add(int element)
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


bool ArrayList::add(int index, int element)
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


bool ArrayList::addAll(ArrayList& list)
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


bool ArrayList::addAll(int index, ArrayList& list)
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


//bool ArrayList::add_M_Elements()
//{
//	cout << "Вводите элементы, которые хотите добавить в массив." << endl;
//	cout << "Чтобы остановить операцию или добавить в массив 0, введите 0." << endl;
//	int n = 1;
//	while (n != 0)
//	{
//		cin >> n;
//		return add(n);
//	}
//	--count;
//	cout << "Чтобы ввести 0, как элемент массива, введите 1." << endl;
//	cout << "Чтобы закончить операцию, введите 0." << endl;
//	cin >> n;
//	if (n == 1)
//	{
//		return add(0);
//	}
//}


bool ArrayList::add_M_Elements(int index)
{
	int n = 1;
	int j = 0;
	ArrayList b;
	while (n != 0)
	{
		cin >> n;
		b.data[j] = n;
		++b.count;
		++j;
	}
	return addAll(index, b);
	--count;
}


void ArrayList::clear()
{
	for (int i = 0; i < count; ++i)
	{
		data[i] = 0;
	}
	count = 0;
}


bool ArrayList::contains(int element)
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


int ArrayList::get(int index)
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


int ArrayList::indexOf(int element)
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


bool ArrayList::isEmpty()
{
	return(count == 0 ? true : false);
}


void ArrayList::print()
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


bool ArrayList::remove(int index)
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


bool ArrayList::swap(int index1, int index2)
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