#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int n = -1; 																	//Вводимое число
	int k = 0; 																		//Количество делителей вводимого числа
	int c = 0;
	cin >> n;
	if (n == 0)
		cout << "k=" << 0 << endl;
	else{
		for (int i = 1; i*i <= n; i++){
			if (n % i == 0)
				k++;
			if (i * i == n)
				c = i * i;
		}
		cout << endl;
		if (c == n)

			cout << "k=" << 2 * k - 1 << endl;
		else
			cout << "k=" << 2 * k << endl;
	}
	return EXIT_SUCCESS;
}