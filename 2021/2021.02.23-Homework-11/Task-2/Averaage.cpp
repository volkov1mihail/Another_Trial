#include<iostream>

using namespace std;


double average(int n, ...)
{
	int result = 0;
	for (int i = 0; i < n; ++i)
	{
		int* ptr = &n + 1 + i;
		result += *ptr;
	}

	return result / n;
}


int main()
{
	return 0;
}