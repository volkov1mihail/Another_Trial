#include<iostream>
#include<iomanip>
#include <string>
#include <cstdlib>

using namespace std;

bool check(string str)
{
	int index = 0;
	if (!brackets(str))
	{
		return false;
	}
	while (str[index] != '/0')
	{
		if (!isCoefficient(str, index) && !isBrackets(str[index++]) && !isSin(str, index) && !isCos(str, index) && !isE(str, index) && !isNotE(str, index) && !isLn(str, index) && !isLog(str, index) && !isOper(str[index++]) && !isConst(str, index) && str[index++] != 'x')
		{
			cout << "¬веденное выражение не может быть продифференцированно этим калькул€тором" << endl;
			return false;
		}
	}
	return true;
}

string recursion(string s)
{
	string result;
	int index = 1;
	if (isCoefficient(s, index))
}


double coefficient(string& str)
{

}

int brackets(string& str)
{
	int c = 0;
	int l = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		c = (str[i] == '(' ? c + 1 : c);
		l = (str[i] == ')' ? l + 1 : l);
	}
	return (c == l ? c : -1);
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool isSin(string str, int& index)
{
	return str[index++] == 's' && str[index++] == 'i' && str[index++] == 'n' && str[index++] == '(';
}

bool isCos(string str, int& index)
{
	return str[index++] == 'c' && str[index++] == 'o' && str[index++] == 's' && str[index++] == '(';
}

bool isLn(string str, int& index)
{
	return str[index++] == 'l' && str[index++] == 'n' && str[index++] == '(';
}

bool isLog(string str, int& index)
{
	return str[index++] == 'l' && str[index++] == 'o' && str[index++] == 'g' && isConst(str, index) && str[index++] == '(';
}

bool isE(string str, int& index)
{
	return str[index++] == 'e' && str[index++] == '^' && str[index++] == '(';
}

bool isNotE(string str, int& index)
{
	return (isTerm(str, index) or isMult(str, index)) && str[index++] == ')' && str[index++] == '^' && str[index++] == '(';
}

bool isPI(string str, int& index)
{
	return str[index++] == 'p' && str[index++] == 'i';
}

bool isNumber(string str, int& index)
{
	int c = 0;
	int d = 0;
	for (index; str[index] != '\0' && (isDigit(str[index]) or str[index] == '.'); ++index)
	{
		++c;
		if (str[index] == '.')
		{
			d = 1;
			break;
		}
	}
	if (c == 309)
	{
		if (str[0] > '1')
		{
			return false;
		}
		else if (str[1] > '7')
		{
			return false;
		}
	}
	else if (c > 309)
	{
		return false;
	}
	if (d == 1)
	{
		++index;
		d = 0;
		for (index; str[index] != '\0' && isDigit(str[index]); ++index)
		{
			++d;
		}
		if (d > 324)
		{
			return false;
		}
	}
	return true;
}

bool isMult(string str, int& index)
{
	return (isNumber(str, index) or str[index++] == 'e' or isPI(str, index)) && isOper1(str[index++]);
}

bool isPartOfConst(string str, int& index)
{
	return isNumber(str, index) or str[index++] == 'e' or isPI(str, index);
}

bool isConst(string str, int& index)
{
	if (isOper2(str[index]))
	{
		return false;
	}
	while (!isBrackets(str[index]))
	{
		if (!isPartOfConst(str, index) && !isOper2(str[index++]))
		{
			return false;
		}
	}
	return true;
}

bool isOper1(char c)
{
	return c == '*' or c == '/';
}

bool isOper2(char c)
{
	return c == '+' or c == '-';
}

bool isOper(char c)
{
	return c == '*' or c == '/' or c == '+' or c == '-' or c == '^';
}

bool isCoefficient(string str, int& index)
{
	if (isOper1(str[index]))
	{
		return false;
	}
	while (!isBrackets(str[index]))
	{
		if (!isMult(str, index))
		{
			return false;
		}
	}
	return true;
}

bool isBrackets(char c)
{
	return c == '(' or c == ')';
}