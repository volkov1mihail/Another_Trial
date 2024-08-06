#include<iostream>

using namespace std;

void printBitsInt(int s)
{
	int bitLength = sizeof(s) * 8;
	for (int i = 0; i < bitLength; ++i)
	{
		unsigned int bit = s;
		bit = bit << i;
		bit = bit >> (bitLength - 1);
		cout << bit;
	}
}


void printBitsLongInt(long long int s)
{
	int bitLength = sizeof(s) * 8;
	for (int i = 0; i < bitLength; ++i)
	{
		unsigned long long int bit = s;
		bit = bit << i;
		bit = bit >> (bitLength - 1);
		cout << bit;
	}
}


void printBits(short s)
{
	int bitlength = sizeof(s) * 8;
	for (int i = 0; i < bitlength; ++i)
	{
		unsigned short bit = s;
		bit = bit << i;
		bit = bit >> (bitlength - 1);
		cout << bit;
	}
}


void printBits(float s)
{
	void* ptr = &s;
	int a = *(int*)(ptr);
	printBitsInt(a);
}


void printBits(long long s)
{
	void* ptr = &s;
	long long int a = *(long long int*)(ptr);
	printBitsLongInt(a);
}


void printBits(double s)
{
	void* ptr = &s;
	long long int a = *(long long int*)(ptr);
	printBitsLongInt(a);
}


void printBits(long double s)
{
	void* ptr = &s;
	long long int a = *(long long int*)(ptr);
	printBitsLongInt(a);
}


int main()
{
	long double b = 0.16;
	cout << "long double"  << endl;
	printBits(b);
	return 0;
}