#include <iostream>
using namespace std;
int main(int argc,char* argv[])				//нахождение неполного частного c при делении числа a на число b
{
	int a = 0; 													//Делимое
	int b = 0; 													//Делитель
	int c = 0; 													//Неполное частное
	cin >> a >> b;
	while (a >= b) {
		a = a - b;
		c++;
	}
	cout << "c=" << c << endl;
	return EXIT_SUCCESS;
}