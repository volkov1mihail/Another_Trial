#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int s = 0; //Сумма цифр в билете
	int n = 0; //Счетчик подходящих чисел
	int a = 0; //Сумма цифр в произвольном числе
	cin >> s;
	for (int b = 0; b <= 999; b++)
	{
		a = b % 10 + (b % 100 - b % 10) / 10 + (b - b % 100) / 100;
		if (a == s)
		{
			n++;
		}
	}
	cout << "n=" << n * n << endl; //Т.к. мы считали трехзначные числа, то количество счастливых билетов будет в n раз больше.
	return EXIT_SUCCESS;
}