#include <iostream>
#include<set>
using namespace std;


void print(const set <int>& s)
{
	for (const auto& x : s)
		cout << x << endl;

}

set<int> twice()
{
	int a = 0;
	set<int> s;
	set<int> s2;
	set<int> s3;
	while (cin >> a)
	{
		if (s.count(a) == 1)
		{
			if (s2.count(a) == 0)
			{
				s2.insert(a);
			}
			else s3.insert(a);
		}
		else s.insert(a);
	}
	for (const auto& x : s3)
	{
		s2.erase(x);
	}

	return s2;
}


set<int> atLeastTwice()
{
	int a = 0;
	set<int> s;
	set<int> s2;
	while (cin >> a)
	{
		if (s.count(a) == 1)
		{
			s2.insert(a);
		}
		else s.insert(a);
	}
	return s2;
}


template<class T>
set<T> unite(set<T> v, set<T> u)
{
	set<T> result;
	typename set<T>::iterator i;
	for (i = u.begin(); i != u.end(); ++i)
	{
		result.insert(*i);
	}
	for (i = v.begin(); i != v.end(); ++i)
	{
		result.insert(*i);
	}
	return result;
}


int main()
{
	set<int> s;
	int a = 0;
	while (cin >> a)
	{
		s.insert(a);
	}
	cout << endl;
	print(s);
	print(twice());
	cout << endl << "______________" << endl;
	print(atLeastTwice());
	return 0;
}