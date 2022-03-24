#include<iostream>
#include<map>
#include<string>
using namespace std;

void print(const map<int, int>& M)
{
	for (auto x : M)
		cout << x.first << " -> " << x.second << endl;
}


map<int, int> toInt()
{
	int a = 0;
	int c = 0;
	map<int, int> m;
	cout << "Choose the nubmer of pairs" << endl;
	cin >> c;;
	for (int j = 0; j < c; ++j)
	{
		cin >> a;
		cin >> m[a];
	}
	return m;
}



map<int, int> count()
{
	map<int, int> m;
	int a = 0;
	while (cin >> a)
	{
		m[a]++;
	}
	return m;
}


map<int, int> second()
{
	map<int, int> m = toInt();
	int c = -1;
	while (c != 0)
	{
		cin >> c;
		if (m.count(c) == 0) cout << c << endl;
		else cout << m[c] << endl;
	}
	return m;
}

template<class T, class P>
map<T, P> sum(map<T, P> m1, map<T, P> m2)
{
	map<T, P> result;
	for (auto x : m1)
	{
		result[x.first] = x.second + m2[x.first];
	}
	return result;
}


template <class T1, class T2, class T3>
map<T1, T3> composition(map<T1, T2> m1, map<T2, T3> m2)
{
	map<T1, T3> result;
	for (auto x : m1)
	{
		result[x.fisrt] = m2[x.second];
	}
	return result;
}


int main()
{
	//print(count());

	map<int, int> m1 = toInt();
	map<int, int> m2 = toInt();
	map<int, int> m = composition(m1, m2);
	print(m);
	//map<int, int> m = second();

	return 0;
}