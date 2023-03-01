//#include<iostream>
//#include<iomanip>
//#include <string>
//#include <cstdlib>
//
//string recursion(string s)
//{
//	string result;
//	result = coefficient(s) * recursion(s);
//}
//
//
//double coefficient(string& str)
//{
//	double result = 0;
//	int c = 0;
//	int k = 0;
//	for (int i = 0; str[i] != '.' && str[i] != '('; ++i)
//	{
//		result = 10 * result + str[i] - '0';
//		++c;
//		++k;
//	}
//	if (str[c] == '(')
//	{
//		++k;
//		for (int i = 0; str[i+k] != '\0'; ++i)
//		{
//			str[i] = str[i + k];
//			if (str[i + k + 1] == '\0')
//			{
//				str[i] = '\0';
//			}
//		}
//		return result;
//	}
//	else
//	{
//		++k;
//		int d = 10;
//		for (int i = c + 1; str[i] != '(' && isDigitInt(str[i]); ++i)
//		{
//			result = result + 1.0 * (str[i] - '0') / d;
//			d *= 10;
//			++k;
//		}
//		for (int i = 0; str[i + k] != '\0'; ++i)
//		{
//			str[i] = str[i + k];
//			if (str[i + k + 1] == '\0')
//			{
//				str[i] = '\0';
//			}
//		}
//		return result;
//	}
//}
//
//
//double stringToDouble(string& str)
//{
//	double result = 0;
//	int c = 0;
//	for (int i = 0; str[i] != '.' && str[i] != '\0'; ++i)
//	{
//		result = 10 * result + str[i] - '0';
//		++c;
//	}
//	if (str[c] == '\0')
//	{
//		return result;
//	}
//	else
//	{
//		for (int i = c + 1; str[i] != '\0' && isDigitInt(str[i]); ++i)
//		{
//			if (i - c == 1)
//			{
//				result = result + 1.0 * (str[i] - '0') / 10;
//			}
//			else if (i - c == 2)
//			{
//				result = result + 1.0 * (str[i] - '0') / 100;
//			}
//			else
//			{
//				result = result + 1.0 * (str[i] - '0') / 1000;
//			}
//		}
//		return result;
//	}
//}
//
//
//int brackets(string& str)
//{
//	int c = 0;
//	for (int i = 0; str[i] != '\0'; ++i)
//	{
//		c = (str[i] == '(' ? c + 1 : c);
//	}
//	return c;
//}