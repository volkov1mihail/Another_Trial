#include<iostream>
#include <vector>

using namespace std;


void fillArray(int* a, int c)
{
	for (int i = 0; i < c; i++)
	{
		a[i] = rand() % 100;
	}
}
void printArray(int* a, int c)
{
	for (int i = 0; i < c; i++)
	{
		cout << a[i] << " ";
	}
}


void countingSort(int* a, int* c, int n, int k)
{
	for (int i = 0; i < k; i++) {
		c[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		c[a[i]] = c[a[i]] + 1;
	}
	int i = 0;
	for (int j = 0; j < k; j++) {
		while (c[j] != 0) {
			a[i] = j;
			c[j]--;
			i++;
		}
	}
}

int* merge(int* a, int* c, int n, int k)
{
	int* p = new int[n + k];
	for (int i = 0; i < k; i++) {
		p[i] = 0;
	}
	int* s = new int[100]{ 0 };
	for (int i = 0; i < n; i++) {
		s[a[i]] = s[a[i]] + 1;
	}
	for (int i = 0; i < n; i++) {
		s[c[i]] = s[c[i]] + 1;
	}
	int i = 0;
	for (int j = 0; j < 100; j++) {
		while (s[j] != 0) {
			p[i] = j;
			s[j]--;
			i++;
		}
	}
	return p;
}


void quickSort(int arr[], int left, int right)
{
	int tmp;
	int current = arr[(left + right) / 2];
	int i = left;
	int j = right;
	while (i <= j)
	{
		while (arr[i] < current) { i++; }
		while (arr[j] > current) { j--; }
		if (i <= j)
		{
			if (arr[i] > arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			i++;
			j--;
		}
	}
	if (left < j)
	{
		quickSort(arr, left, j);
	}
	if (right > i)
	{
		quickSort(arr, i, right);
	}
}


int main()
{
	int c = 30;
	int* a = new int[c];
	int* b = new int[100];
	fillArray(a, c);
	fillArray(b, 100);
	cout << "Array A isn't sorted " << endl;
	printArray(a, c);
	countingSort(a, b, c, 100);
	cout << endl << "Array was sorted (CountingSort) " << endl;
	printArray(a, c);
	cout << endl << endl << endl;
	fillArray(a, c);
	cout << "Array A isn't sorted " << endl;
	printArray(a, c);
	quickSort(a, 0, c - 1);
	cout << endl;
	printArray(a, c);
	cout << endl << "Array was sorted (QuickSort)  " << endl;
	int* p = new int[c];
	fillArray(p, c);
	cout << endl << endl << endl;
	cout << "A   ";
	printArray(a, c);
	cout << endl;
	cout << "P   ";
	printArray(p, c);
	cout << "merge " << endl;
	printArray(merge(a, p, c, c), 2 * c);
	delete[] a;
	delete[] b;
	delete[] p;
	return 0;
}