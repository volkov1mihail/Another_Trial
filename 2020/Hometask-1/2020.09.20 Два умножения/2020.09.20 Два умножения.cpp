#include <iostream>
using namespace std;
int main(int argc, char* argv[])										//задача получить из числа x сумму x^4+x^3+x^2+x+1, используя только 2 умножения
{
	int x = 0;
	int square = 0;
	int answer = 0; 																	//square=x^2, answer=x^4+x^3+x^2+x+1=(x^2+1)*(x^2+x)+1
	cin >> x;
	square = x * x;
	answer = (square + 1) * (square + x) + 1;
	cout << answer << endl;
	return EXIT_SUCCESS;
}