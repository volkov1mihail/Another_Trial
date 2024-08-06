#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int n = 0; //¬водимое число
	int f = 1; //‘акториал вводимого числа
	cin >> n;
	for (int i = 1; i <= n; i++)
		{
			f = f * i;
		}
	cout << "f=" << f << endl;
	return EXIT_SUCCESS;
}