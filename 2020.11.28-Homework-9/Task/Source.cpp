#include<iostream>
#include<iomanip>
#include<clocale>
#include<ctime>
using namespace std;

void printMenu()
{
	cout << "Нажмите 0, чтобы завершить работу программы" << endl;
	cout << "Нажмите 1, чтобы ввести число типа long long" << endl;
	cout << "Нажмите 2, чтобы ввести число типа double" << endl;
	cout << "Нажмите 3, чтобы вычислить сумму чисел типа long long и double" << endl;
	cout << "Нажмите 4, чтобы вывести на экран число типа long long" << endl;
	cout << "Нажмите 5, чтобы вывести на экран число типа double" << endl;
}


bool isDigitInt(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
	{
		return true;
	}
	else
	{
		int c = rand() % 2;
		if (c == 0)
		{
			cout << "Не все введенные вами сиволы не являются цифрами, попадите по нужным клавишам, пожалуйста" << endl;
		}
		else
		{
			cout << "Числа состоят из цифр: 1, 2, 6, знаете? Попробуйте, все-таки, ввести комбинацию цифр" << endl;
		}
		return false;
	}
}


long long stringToInt(string& str)
{
	int result = 0;
	for (int i = 0; str[i] != '\0' && isDigitInt(str[i]); ++i)
	{
		result = 10 * result + str[i] - '0';
	}
	return result;
}


void trim(string& str)
{
	int startIndex = 0;
	while (str[startIndex] == ' ')
	{
		startIndex++;
	}
	str = str.substr(startIndex);
}


bool megaKostyl1(string& str)
{
	if ((str[1] - '0') > 2)
	{
		return false;
	}
	if ((str[2] - '0') > 2)
	{
		return false;
	}
	if ((str[3] - '0') > 3)
	{
		return false;
	}
	if ((str[4] - '0') > 3)
	{
		return false;
	}
	if ((str[5] - '0') > 7)
	{
		return false;
	}
	if ((str[6] - '0') > 2)
	{
		return false;
	}
	if ((str[8] - '0') > 3)
	{
		return false;
	}
	if ((str[9] - '0') > 6)
	{
		return false;
	}
	if ((str[10] - '0') > 8)
	{
		return false;
	}
	if ((str[11] - '0') > 5)
	{
		return false;
	}
	if ((str[12] - '0') > 4)
	{
		return false;
	}
	if ((str[13] - '0') > 7)
	{
		return false;
	}
	if ((str[14] - '0') > 7)
	{
		return false;
	}
	if ((str[15] - '0') > 5)
	{
		return false;
	}
	if ((str[16] - '0') > 8)
	{
		return false;
	}
	if ((str[18] - '0') > 8)
	{
		return false;
	}
	return true;
}


bool sizeOfInt(string& str)
{
	cout << "Введите число типа long long" << endl;
	cin >> str;
	trim(str);
	int c = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		++c;
		if (!isDigitInt(str[i]))
		{
			return false;
		}
	}
	if (c == 19)
	{
		if (!megaKostyl1(str))
		{
			int b = rand() % 2;
			if (b == 0)
			{
				cout << "Введенное число не входит в long long, слишком большой модуль числа" << endl;
			}
			else
			{
				cout << "В long long входят целые числа, модулем меньшие 9 223 372 036 854 775 808, введите число, входящее в этот диапазон" << endl;
			}
			return false;
		}
	}
	else if (c > 19)
	{
		int b = rand() % 2;
		if (b == 0)
		{
			cout << "Введенное число не входит в long long, слишком большой модуль числа" << endl;
		}
		else
		{
			cout << "В long long входят целые числа, модулем меньшие 9 223 372 036 854 775 808, введите число, входящее в этот диапазон" << endl;
		}
		return false;
	}
	else
	{
		return true;
	}
}


int signOfNumber()
{
	char c = '0';
	char d = '0';
	cout << "Чтобы ввести положительное число, нажмите 1" << endl;
	cout << "Чтобы ввести отрицательное число, нажмите 0" << endl;
	d = getchar();
	c = getchar();
	if (c == '1')
	{
		return 1;
	}
	else if (c == '0')
	{
		return -1;
	}
	else
	{
		int b = rand() % 2;
		if (b == 0)
		{
			cout << "Введенный символ не является '1' или '0', выберите нужный знак числа" << endl;
		}
		else
		{
			cout << "Введите '1' или '0', другого варианта тут нет" << endl;
		}
		return 0;
	}
}


long long readInt(string& str, int& check)
{
	int c = 0;
	while (c == 0)
	{
		c = signOfNumber();
	}
	if (sizeOfInt(str))
	{
		check = 1;
		return c * stringToInt(str);
	}
	else
	{
		check = 0;
		return -1;
	}
}


bool isDigitDouble(char symbol)
{
	if ((symbol >= '0' && symbol <= '9') or symbol == '.')
	{
		return true;
	}
	else
	{
		int c = rand() % 2;
		if (c == 0)
		{
			cout << "Не все введенные вами сиволы не являются цифрами, попадите по нужным клавишам, пожалуйста" << endl;
		}
		else
		{
			cout << "Числа состоят из цифр: 1, 2, 6, знаете? Попробуйте, все-таки, ввести комбинацию цифр" << endl;
		}
		return false;
	}
}


double stringToDouble(string& str)
{
	double result = 0;
	int c = 0;
	for (int i = 0; str[i] != '.' && str[i] != '\0'; ++i)
	{
		result = 10 * result + str[i] - '0';
		++c;
	}
	if (str[c] == '\0')
	{
		return result;
	}
	else
	{
		for (int i = c + 1; str[i] != '\0' && isDigitInt(str[i]); ++i)
		{
			if (i - c == 1)
			{
				result = result + 1.0 * (str[i] - '0') / 10;
			}
			else if (i - c == 2)
			{
				result = result + 1.0 * (str[i] - '0') / 100;
			}
			else
			{
				result = result + 1.0 * (str[i] - '0') / 1000;
			}
		}
		return result;
	}
}


bool sizeOfDouble(string& str)
{
	cout << "Введите число типа double" << endl;
	cin >> str;
	trim(str);
	int c = 0;
	int d = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		++c;
		if (!isDigitDouble(str[i]))
		{
			return false;
		}
		if (str[i] == '.')
		{
			d = 1;
			break;
		}
	}
	if (c == 309)
	{
		if (str[0] > 1)
		{
			int b = rand() % 2;
			if (b == 0)
			{
				cout << "Введенное число не входит в double, слишком большой модуль числа" << endl;
			}
			else
			{
				cout << "В double входят целые числа, модулем меньшие 1.8*10^308, введите число, входящее в этот диапазон" << endl;
			}
			return false;
		}
		else if (str[1] > 7)
		{
			int b = rand() % 2;
			if (b == 0)
			{
				cout << "Введенное число не входит в double, слишком большой модуль числа" << endl;
			}
			else
			{
				cout << "В double входят целые числа, модулем меньшие 1.8*10^308, введите число, входящее в этот диапазон" << endl;
			}
			return false;
		}
	}
	else if (c > 309)
	{
		int b = rand() % 2;
		if (b == 0)
		{
			cout << "Введенное число не входит в double, слишком большой модуль числа" << endl;
		}
		else
		{
			cout << "В double входят целые числа, модулем меньшие 1.8*10^308, введите число, входящее в этот диапазон" << endl;
		}
		return false;
	}
}


double readDouble(string& str, int& check)
{
	int c = 0;
	while (c == 0)
	{
		c = signOfNumber();
	}
	if (sizeOfDouble(str))
	{
		check = 1;
		return c * stringToDouble(str);
	}
	else
	{
		check = 0;
		return -1;
	}
}


void processChoice(string& str, long long& ll, double& d, int choice)
{
	switch (choice)
	{
	case 1:
	{
		int check = -1;
		int choice2 = 1;
		do
		{

			system("cls");
			printMenu();
			ll = readInt(str, check);
			choice2 = (check == 1 ? 0 : 1);
			system("pause");
		} while (choice2 != 0);
		break;
	}
	case 2:
	{
		int check = -1;
		int choice2 = 1;
		do
		{
			system("cls");
			printMenu();
			d = readDouble(str, check);
			choice2 = (check == 1 ? 0 : 1);
			system("pause");
		} while (choice2 != 0);
		break;
	}
	case 3:
	{
		double g = ll * 1.0 + d;
		cout << "Сумма равна  " << g << endl;
		break;
	}
	case 4:
		cout << ll << endl;
		break;
	case 5:
		cout << d << endl;
		break;
	}
}


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	string str;
	long long ll = 0;
	double d = 0;
	int check;
	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(str, ll, d, choice);
		system("pause");
	} while (choice != 0);
	//double d = -173333300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000111111;
	//cout << d;
	return 0;
}
