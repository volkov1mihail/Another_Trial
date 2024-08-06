#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int n = 0; //Заданное число
	int a = 0; //Произвольное число, не привосходящее заданное
	int k = 0; //Количество простых чисел, не привосходящих заданного числа
	cin >> n;
	if (n <= 1)
	{
		cout << "k=" << 0 << endl;
	}
	else if (n == 2)
	{
		cout << "k=" << 1 << endl; // Учитывается 2
		cout << 2 << endl;
	}
	else if (n < 5)
	{
		cout << "k=" << 2 << endl; //Учитываются 2 и 3
		cout << 2 << " " << 3 << endl;
	}
	else
	{
		cout << 2 << " " << 3 << " " << 5 << " ";
		for (int i = 1; 6 * i - 1 <= n; i++)
		{
			if ((6 * i - 1) % 5 != 0)
			{
				k++;
				cout << 6 * i - 1 << " ";
			}
			if (((6 * i + 1) <= n) & ((6 * i + 1) % 5 != 0))
			{
				k++;
				cout << 6 * i + 1 << " ";
			}
		}
		cout << endl;
		cout << "k=" << k + 3 << endl; //Выводим k+3, чтобы учесть 2, 3 и 5.
	}
	return EXIT_SUCCESS;
}