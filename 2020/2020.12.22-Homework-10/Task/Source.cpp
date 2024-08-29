#include<iostream>
#include<clocale>
using namespace std;


void printMenu()
{
	cout << "Закончить работу программы - 0" << endl;
	cout << "Реализовать первый вариант заполнения матрицы - 1" << endl;
	cout << "Реализовать второй вариант заполнения матрицы - 2" << endl;
	cout << "Реализовать третий вариант заполнения матрицы - 3" << endl;
	cout << "Реализовать четвертый вариант заполнения матрицы - 4" << endl;
	cout << "Реализовать пятый вариант заполнения матрицы - 5" << endl;
}


void print(int n, int** data)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << data[j][i] << ' ';
		}
		cout << endl;
	}
}


void free(int n, int** data)
{
	for (int i = 0; i < n; ++i)
	{
		delete[] data[i];
	}
	delete[] data;
}


void case5(int n, int** data)
{
	int i = 1;
	int j = 1;
	for (int k = 0; k < n; ++k)
	{
		data[k][0] = k + 1;
	}
	for (int k = 1; k < n; ++k)
	{
		data[n - 1][k] = k + n;
	}
	for (int k = n - 2; k >= 0; --k)
	{
		data[k][n - 1] = data[k + 1][n - 1] + 1;
	}
	for (int k = n - 2; k > 0; --k)
	{
		data[0][k] = data[0][k + 1] + 1;
	}
	int c = data[0][1];
	while (c < n * n - 1)
	{
		if ((data[i][j - 1] > 0) & (i < n - 1) & (data[i + 1][j] == 0))
		{
			data[i][j] = c + 1;
			++c;
			++i;
		}
		else if ((data[i + 1][j] > 0) & (j < n - 1) & (data[i][j + 1] == 0))
		{
			data[i][j] = c + 1;
			++c;
			++j;
		}
		else if ((data[i][j + 1] > 0) & (i > 1) & (data[i - 1][j] == 0))
		{
			data[i][j] = c + 1;
			++c;
			--i;
		}
		else if ((data[i - 1][j] > 0) & (j > 1) & (data[i][j - 1] == 0))
		{
			data[i][j] = c + 1;
			++c;
			--j;
		}
	}
	if (n % 2 == 1)
	{
		data[n / 2][n / 2] = n * n;
	}
	else
	{
		data[n / 2 - 1][n / 2] = n * n;
	}
}


void processChoice(int n, int choice)
{
	switch (choice)
	{
	case 1:
	{
		cout << "Введите число n" << endl;
		cin >> n;
		int** data = new int* [n] {0};
		for (int i = 0; i < n; ++i)
		{
			data[i] = new int[n] {0};
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				data[i][j] = i + j + 1;
			}
		}
		print(n, data);
		free(n, data);
		break;
	}
	case 2:
	{
		cout << "Введите число n" << endl;
		cin >> n;
		int** data = new int* [n] {0};
		for (int i = 0; i < n; ++i)
		{
			data[i] = new int[n] {0};
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				data[i][j] = 2 * n - 1 - i - j;
			}
		}
		print(n, data);
		free(n, data);
		break;
	}
	case 3:
	{
		cout << "Введите число n" << endl;
		cin >> n;
		int** data = new int* [n] {0};
		for (int i = 0; i < n; ++i)
		{
			data[i] = new int[n] {0};
		}
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				data[i][j] = i + 1;
			}
		}
		print(n, data);
		free(n, data);
		break;
	}
	case 4:
	{
		cout << "Введите число n" << endl;
		cin >> n;
		int** data = new int* [n] {0};
		for (int i = 0; i < n; ++i)
		{
			data[i] = new int[n] {0};
		}
		for (int c = 0; c < n; ++c)
		{
			for (int i = c; i < n; ++i)
			{
				for (int j = c; j < n; ++j)
				{
					data[i][j] = data[i][j] + 1;
				}
			}
		}
		print(n, data);
		free(n, data);
		break;
	}
	case 5:
	{
		cout << "Введите число n" << endl;
		cin >> n;
		int** data = new int* [n] {0};
		for (int i = 0; i < n; ++i)
		{
			data[i] = new int[n] {0};
		}
		case5(n, data);
		print(n, data);
		free(n, data);
		break;
	}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int n = 0;
	int choice = 0;
	do {
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(n, choice);
		system("pause");
	} while (choice != 0);
	return 0;
}