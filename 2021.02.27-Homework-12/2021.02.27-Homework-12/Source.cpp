#include<iostream>

using namespace std;

template<class T1, class T2>
T1 sum(T1 a, T2 b)
{
	return a + b;
}

template<class T1, class T2>
T1 diff(T1 a, T2 b)
{
	return a - b;
}

template<class T1, class T2>
T1 prod(T1 a, T2 b)
{
	return a * b;
}


template<class T1, class T2>
T1 div(T1 a, T2 b)
{
	return a / b;
}

template<class T1, class T2>
T1 mod(T1 a, T2 b)
{
	return a % b;
}


bool operand1(char c[])
{
	char a[] = { 'o','p','e','r','a','n','d','1' };
	for (int i = 0; c[i] != 0; ++i)
	{
		if (c[i] != a[i])
		{
			return false;
		}
	}
	return true;
}

bool operat(char c[])
{
	char a[] = { 'o','p','e','r','a','t','o','r' };
	for (int i = 0; c[i] != 0; ++i)
	{
		if (c[i] != a[i])
		{
			return false;
		}
	}
	return true;
}

bool operand2(char c[])
{
	char a[] = { 'o','p','e','r','a','n','d','2' };
	for (int i = 0; c[i] != 0; ++i)
	{
		if (c[i] != a[i])
		{
			return false;
		}
	}
	return true;
}

template<class T1, class T2>
void calc(T1 a, T2 b, char op)
{
	if (op == '+')
	{
		cout << a << " " << op << " " << b << " = " << sum(a, b) << endl;
	}
	if (op == '-')
	{
		cout << a << " " << op << " " << b << " = " << diff(a, b) << endl;
	}
	if (op == '*')
	{
		cout << a << " " << op << " " << b << " = " << prod(a, b) << endl;
	}
	//if (op == '/')
	//{
	//	cout << a << " " << op << " " << b << " = " << div(a, b) << endl;
	//}
	if (op == '%')
	{
		cout << a << " " << op << " " << b << " = " << mod(a, b) << endl;
	}
}

int main(int argc, char* argv[])
{
	int a = 0;
	int b = 0;
	char c = '0';
	for (int i = 1; i < argc; ++i)
	{
		if (operand1(argv[i]))
		{
			for (int j = 0; argv[i + 1][j] != 0; ++j)
			{
				a = a * 10 + argv[i + 1][j] - '0';
			}
		}
		if (operand2(argv[i]))
		{
			for (int j = 0; argv[i + 1][j] != 0; ++j)
			{
				b = b * 10 + argv[i + 1][j] - '0';
			}
		}
		if (operat(argv[i]))
		{
			c = argv[i + 1][0];
		}
	}
	calc(a, b, c);
	return 0;
}