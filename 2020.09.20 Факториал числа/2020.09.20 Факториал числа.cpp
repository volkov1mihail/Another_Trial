#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
	int n = 0; //�������� �����
	int f = 1; //��������� ��������� �����
	cin >> n;
	if (n == 0)
	{
		cout << 1 << endl;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			f = f * i;
		}
		cout << "f=" << f << endl;
	}
	return EXIT_SUCCESS;
}