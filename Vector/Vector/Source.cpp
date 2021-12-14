#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

template <typename T>
void print(vector<T> v);

template <typename T>
void enlarge(vector<T>& v);

template <typename T>
void del(vector<T>& v);

template <typename T>
vector<T> concat(vector<T> a, vector<T> b);

template <typename T>
vector<T> repeat(int n, vector<T> a);

template <typename T>
auto second_occurrence(vector<T>& v, T a)
{
	{
		auto i = find(v.begin(), v.end(), a);
		i = find(++i, v.end(), a);
		return i;
	}
}

template<typename T>
auto last_occurrence(vector<T>& v, T a)
{
	auto i = find(v.begin(), v.end(), a);
	auto j = i;
	while (i != v.end())
	{
		j = i;
		i = find(++i, v.end(), a);
	}
	return j;
}

template<typename T>
bool subseq(vector<T> a, vector<T> b);


template <typename T>
auto last2(vector<T>& v, T a)
{
	return upper_bound(v.begin(), v.end(), a) - 1;
}


void ij(vector<double>& v, double x, int& i, int& j);

int main()
{
	vector<int> v{ 2, 4, 6, 8, 10 };

	print(v);
	enlarge(v);
	print(v);
	del(v);
	print(v);

	cout << endl;
	vector<int> v2{ 1, 2, 3, 4, 5, 6 };
	int* arr = new int[v2.size()];
	copy(v2.begin(), v2.end(), arr);
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	vector<int> v3 = concat(v, v2);
	print(v3);

	vector<int> v4 = repeat(5, v);
	print(v4);


	for (auto i = v4.begin(); i != second_occurrence(v4, 5); ++i)
	{
		cout << *i << " ";
	}
	cout << *second_occurrence(v4, 5);
	cout << endl;

	for (auto i = v4.begin(); i != last_occurrence(v4, 5); ++i)
	{
		cout << *i << " ";
	}
	cout << *last_occurrence(v4, 5);
	cout << endl;

	vector<int> v5{ 5, 5, 7, 3, 7, 7, 7 };
	if (subseq(v5, v4))
	{
		cout << "v5 in v4" << endl;
	}
	else
	{
		cout << "v5 not in v4" << endl;
	}

	// #9
	vector<int> v6{ 1, 2, 3, 4, 4, 4, 5, 5, 5, 6, 7 , 9 };
	for (auto i = v6.begin(); i != last2(v6, 5); ++i)
	{
		cout << *i << " ";
	}
	cout << *last2(v4, 5);
	cout << endl;
	// #10
	vector<double> v7{ 1.8, 2.6, 3.4, 4.3, 4.3, 5.2, 6.6 };
	int i = 0;
	int j = 0;
	ij(v7, 4.5, i, j);
	print(v7);
	cout << i << " " << j;



	return EXIT_SUCCESS;
}

template<typename T>
void print(vector<T> v)
{
	for (auto x : v)
	{
		cout << x << " ";
	}
	cout << endl;
}

template<typename T>
void enlarge(vector<T>& v)
{
	T a;
	for (auto i = v.begin(); i != --v.end(); ++i)
	{
		a = *i;
		++i;
		i = v.insert(i, (*i + a) / 2);
	}

}

template<typename T>
void del(vector<T>& v)
{
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		i = v.erase(i);
		if (i == v.end())
		{
			return;
		}

	}
}

template<typename T>
vector<T> concat(vector<T> a, vector<T> b)
{
	vector<T> v;
	v.resize(a.size() + b.size());
	copy(a.begin(), a.end(), v.begin());
	copy(b.begin(), b.end(), v.begin() += a.size());

	return v;
}

template<typename T>
vector<T> repeat(int n, vector<T> a)
{
	vector<T> v;
	v.resize(n * a.size());
	for (int i = 0; i < n; ++i)
	{
		copy(a.begin(), a.end(), v.begin() += (a.size() * i));
	}
	return v;
}

template<typename T>
bool subseq(vector<T> a, vector<T> b)
{
	auto i = b.begin();
	for (auto x : a)
	{
		i = find(i, b.end(), x);
		if (i == b.end())
		{
			return false;
		}
		++i;
	}
	return true;
}

void ij(vector<double>& v, double x, int& i, int& j)
{
	vector<double>::iterator ii;
	vector<double>::iterator jj;
	ii = lower_bound(v.begin(), v.end(), x) - 1;
	i = 0;
	for (jj = v.begin(); jj != ii; ++jj)
	{
		++i;
	}
	j = i;
	if (ii == v.end() || *ii == x)
	{
		return;
	}
	else
	{
		jj = upper_bound(v.begin(), v.end(), x);
		for (ii; ii != jj; ++ii)
		{
			++j;
		}
	}


}