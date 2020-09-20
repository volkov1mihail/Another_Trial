#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int n = 0; //Вводимое число
	int k = 0; //Количество делителей вводимого числа
	cin >> n;
	if (n == 0)
	{
		cout << "k=" << 0 << endl;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			if (n % i == 0)
			{
				k++;
				cout << i << " ";
			}
		}
		cout << endl;
		cout << "k=" << k << endl;
	}
	return EXIT_SUCCESS;
}