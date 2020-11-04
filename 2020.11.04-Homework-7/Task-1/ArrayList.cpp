#include "ArrayList.h"


ArrayList::ArrayList(const ArrayList& list)
{
	count = list.count;
	capacity = list.capacity;
	for (int i = 0; i < count; ++i)
	{
		data[i] = list.data[i];
	}
}


ArrayList::~ArrayList()
{
	delete[] data;
}


void ArrayList::expand()
{
	int* temp = new int[capacity * 2];
	for (int i = 0; i < count; ++i)
	{
		temp[i] = data[i];
	}
	capacity *= 2;
	delete[] data;
	data = temp;
}


bool ArrayList::add(int element)
{
	if (count == capacity)
	{
		expand();
	}
	data[count] = element;
	++count;
	return true;
}


bool ArrayList::add(int index, int element)
{
	if (count == capacity)
	{
		expand();
	}
	for (int i = count + 1; i > index; --i)
	{
		data[i] = data[i - 1];
	}
	data[index] = element;
	++count;
	return true;
}


bool ArrayList::addAll(ArrayList& list)
{
	while (count > capacity - list.count)
	{
		expand();
	}
	for (int i = count; i < count + list.count; ++i)
	{
		add(list.data[i - count]);
	}
	return true;
}


bool ArrayList::addAll(int index, ArrayList& list)
{
	if (count > capacity - list.count)
	{
		expand();
	}
	for (int i = index; i < index + list.count; ++i)
	{
		add(i, list.data[i - index]);
	}
	return true;
}


void ArrayList::clear()
{
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


bool ArrayList::set(int index, int element)
{
	if ((index >= count) or (index < 0))
	{
		return false;
	}
	else
	{
		data[index] = element;
		return true;
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


int ArrayList::length()
{
	return count;
}


void ArrayList::operator+= (int item)
{
	add(item);
}


void ArrayList::operator-= (int item)
{
	remove(count - 1);
}


ArrayList& ArrayList::operator= (const ArrayList& list)
{
	if (&list != this)
	{
		delete[] data;
		capacity = list.capacity;
		int* data = new int[capacity] {0};
		count = list.count;
		for (int i = 0; i < count; ++i)
		{
			data[i] = list.data[i];
		}
	}
	return *this;
}


ArrayList operator+ (const ArrayList& list, int item)
{
	ArrayList result(list);
	result += item;
	return result;
}


ArrayList operator+ (int item, const ArrayList& list)
{
	ArrayList result(list);
	result.add(0, item);
	return result;
}


ArrayList operator+ (const ArrayList& list1, const ArrayList& list2)
{
	ArrayList result(list1);
	for (int i = 0; i < list2.count; ++i)
	{
		result += list2.data[i];
	}
	return result;
}


ArrayList operator- (const ArrayList& list, int item)
{
	ArrayList result(list);
	int c = -1;
	for (int i = result.count - 1; i >= 0; --i)
	{
		if (result.data[i] == item)
		{
			c = i;
		}
	}
	if (c >= 0)
	{
		result.remove(c);
	}
	return result;
}


ArrayList operator- (int item, const ArrayList& list)
{
	ArrayList result(list);
	if (result.indexOf(item) >= 0)
	{
		result.remove(result.indexOf(item));
	}
	return result;
}


std::ostream& operator<<(std::ostream& stream, const ArrayList& list)
{
	std::cout << "[" << list.count << "/" << list.capacity << "]  {";
	for (int i = 0; i < list.count - 1; ++i)
	{
		std::cout << list.data[i] << " ";
	}
	std::cout << list.data[list.count - 1] << "}" << std::endl;
	return stream;
}