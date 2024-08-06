#include<iostream>
#include<iomanip>
#include <string>
#include <cstdlib>
#include<fstream>

using namespace std;

bool isMantiss(string str, int& index);
bool isExponent(string str, int& index);
bool isExponent(string str, int& index);
bool isInt(string str, int& index);
bool isDigit(char c);
bool isSign(char c);

bool isReal(string str)
{
	int index = 0;
	if (isMantiss(str, index) && isExponent(str, index))
	{
		return true;
	}
	index = 0;
	if (isSign(str[index++]) && isMantiss(str, index) && isExponent(str, index))
	{
		return true;
	}
	return false;
	//return (isMantiss(str, index) && isExponent(str, index)) or (isSign(str[index++]) && isMantiss(str, index) && isExponent(str, index));
}

bool isMantiss(string str, int& index)
{
	int index1 = index;
	if (str[index++] == '.' && isInt(str, index))
	{
		++index;
		return true;
	}
	index = index1;
	if (isInt(str, index) && str[index++] == '.' && isInt(str, index))
	{
		++index;
		return true;
	}
	index = index1;
	return false;
	//return (str[index++] == '.' && isInt(str, index)) or (isInt(str, index++) && str[index++] == '.' && isInt(str, index));
}

bool isExponent(string str, int& index)
{
	int index1 = index;
	if (str[index++] == 'E' && isInt(str, index))
	{
		++index;
		return true;
	}
	index = index1;
	if (str[index++] == 'E' && isSign(str[index++]) && isInt(str, index))
	{
		++index;
		return true;
	}
	index = index1;
	return false;
	//return (str[index++] == 'E' && isInt(str, index)) or (str[index++] == 'E' && isSign(str[index++]) && isInt(str, index));
}

bool isInt(string str, int& index)
{
	int index1 = index;
	if (isDigit(str[index++]) && isInt(str, index))
	{
		++index;
		return true;
	}
	index = index1;
	if (isDigit(str[index]))
	{
		++index;
		return true;
	}
	return false;
	//return isDigit(str[index++]);
	//return isDigit(str[index]) or (isDigit(str[index++]) && isInt(str, index));
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isSign(char c)
{
	return c == '+' or c == '-';
}

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	while (!fin.eof())
	{
		string str;
		fin >> str;
		cout << str << endl;
		fout << str << endl;
		system("pause");
		if (isReal(str))
		{
			cout << "=)" << endl;
			fout << "=)" << endl;
		}
		else
		{
			cout << "=(" << endl;
			fout << "=(" << endl;
		}
		system("pause");
	}
	fout.close();
	fin.close();
	return 0;
}