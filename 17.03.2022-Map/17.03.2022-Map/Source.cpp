#include<iostream>
#include<map>
using namespace std;

void print(const map<int, int>& M)
{
	for (auto x : M)
		cout << x.first << " -> " << x.second << endl;
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


int main()
{
	print(count());
	return 0;
}