#include<iostream>
#include<algorithm>
#include<string>
#include <stack>

using namespace std;

double f2();

void f1();

int main()
{
	f1();
	cout << f2() << endl;
	return EXIT_SUCCESS;
}

double f2()
{
	stack<double> s;
	char x = '1';
	double a;
	double b;
	while (x != '=')
	{
		cin >> x;
		if (isdigit(x))
		{
			cin.putback(x);
			cin >> a;
			s.push(a);
		}
		else if (x == '+')
		{
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			s.push(b + a);
		}
		else if (x == '-')
		{
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			s.push(b - a);
		}
		else if (x == '*')
		{
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			s.push(b * a);
		}
		else if (x == '/')
		{
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			s.push(b / a);
		}
	}
	return s.top();
}

void f1()
{
	stack<char> s;
	string result;
	char x = '1';
	double a;
	while (x != '=')
	{
		cin >> x;

		if (isdigit(x))
		{
			cin.putback(x);
			cin >> a;
			result += to_string(a);
			result += " ";
		}

		if (x == '*' || x == '/')
		{
			while (!s.empty() && s.top() == '*' || s.top() == '/')
			{
				result.push_back(s.top());
				result += " ";
				s.pop();
			}
			s.push(x);
		}

		if (x == '-' || x == '+')
		{
			while (!s.empty() && s.top() != '(')
			{
				result.push_back(s.top());
				result += " ";
				s.pop();
			}
			s.push(x);
		}

		if (x == '(')
		{
			s.push(x);
		}

		if (x == ')')
		{
			while (s.top() != '(')
			{
				cout << "sssss" << endl;
				result.push_back(s.top());
				result += " ";
				s.pop();
			}
			s.pop();
		}
		cout << result << endl;
	}
	while (!s.empty())
	{
		cout << s.top() << endl;
		result.push_back(s.top());
		result += " ";
		s.pop();
	}
	cout << result << endl;
}