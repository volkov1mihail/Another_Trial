#include "ArrayList.h"


ArrayList::~ArrayList()
{
	delete[] data;
}


void ArrayList::expand()
{
	ArrayList temp(capacity * 2);
	for (int i = 0; i < count; ++i)
	{
		temp.data[i] = data[i];
	}
	temp.count = count;
	delete[] data;
	data = temp.data;
}


int ArrayList::numLength(int number)
{
	int result = 1;
	while (number > 9)
	{
		number /= 10;
		result++;
	}
	return result;
}


void ArrayList::addSymbolToStr(int& index, char symbol)
{
	str[index] = symbol;
	++index;
}


void ArrayList::addNumberToStr(int& index, int number)
{
	int length = numLength(number);
	for (int i = 0; i < length; ++i)
	{
		int digit = number % 10;
		str[index + length - 1 - i] = '0' + digit;
		number /= 10;
	}
	index += length;
}


bool ArrayList::add(int element)
{
	if (count == capacity)
	{
		expand();
	}
	data[count++] = element;
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


int ArrayList::swap(int index1, int index2)
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


//int ArrayList::length()
//{
//	int length = 0;
//	for (int i = 0; i < count; ++i)
//	{
//		length += numLength(data[i]);
//	}
//	return length;
//}


int ArrayList::length()
{
	return count;
}


//char* ArrayList::toString()
//{
//	int totalLength = 5 + length();
//	int index = 0;
//	addSymbolToStr(index, '(');
//	for (int i = 0; i < count - 1; ++i)
//	{
//		addNumberToStr(index, data[i]);
//		addSymbolToStr(index, ',');
//		addSymbolToStr(index, ' ');
//	}
//	addNumberToStr(index, data[count - 1]);
//	addSymbolToStr(index, ')');
//	addSymbolToStr(index, '\0');
//	return str;
//}


char* ArrayList::toString()
{
	int s = 0;
	for (int i = 0; i < count; ++i)
	{
		s += numLength(data[i]);
	}
	int length = 5 + s;
	str = new char[length];
	int index = 0;
	addSymbolToStr(index, '(');
	for (int i = 0; i < count - 1; ++i)
	{
		addNumberToStr(index, data[i]);
		addSymbolToStr(index, ',');
		addSymbolToStr(index, ' ');
	}
	addNumberToStr(index, data[count - 1]);
	addSymbolToStr(index, ')');
	addSymbolToStr(index, '\0');
	return str;
}