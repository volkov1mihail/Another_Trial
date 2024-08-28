#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
//Программа решает задачу интерполирования заданной функции func() на промежутке [a;b]
//Для этого по значениям функции строится интерполяционный многочлен заданной степени power
//Используется интерполяционный многочлен в форме Лагранжа и в форме Ньютона
//Точность, с которой было найдено решение, выводится на экран для сравнения двух интерполяционных многочленов
typedef vector<vector<double>> vecVector;

double func(double x)
{
	return log(1 + x);
	//return x*x*x-x*x+3*x-5;
}
void print(vecVector const&);
void printSorted(vecVector const&, int);
vecVector nodes(int, double, double);
vecVector sort(vecVector, double);
double Lagrange(vecVector const&, double, int);
double Newton(vecVector const&, double, int);
double dividedDifference(vecVector const&, int, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Задача алгебраического интерполирования, вариант 2, функция f(x) = ln(1+x)" << endl;
	cout << "Введите число табличных значений" << endl;
	int points = 0;
	cin >> points;
	int power = points;

	double a = 0;
	double b = 0;
	cout << "Введите левую границу отрезка а > -1" << endl;
	cin >> a;
	cout << "Введите правую границу отрезка b > " << a << endl;
	cin >> b;

	int index = -1;
	double Point = 0;

	vecVector basicNodes = nodes(points, a, b);
	vecVector nodes;

	double result = 0;
	int timer = 1;
	while (timer == 1)																								//Индикатор, определяющий, когда нужно закончить работу программы
	{
		print(basicNodes);
		while (index < 0 or index > 1)
		{
			cout << endl << "Чтобы выбрать один из узлов за точку интерполяции, введите 0" << endl;
			cout << "Чтобы выбрать произвольную точку интерполяции, введите 1" << endl;
			cin >> index;
		}
		switch (index) {
		case 0:
			cout << "Введите номер узла, который хотите выбрать в качестве точки инетрполяции" << endl;
			cin >> index;
			Point = basicNodes[index][1];
			break;
		case 1:
			cout << "Введите точку интерполирования Point > -1" << endl;
			cin >> Point;
			break;
		}

		while (power >= points)
		{
			cout << "Введите степень интерполирования многочлена power <= " << points - 1 << endl;
			cin >> power;
		}
		nodes = sort(basicNodes, Point);
		cout << "Отсортированная таблица значений:" << endl;
		printSorted(nodes, power);

		result = Lagrange(nodes, Point, power);													//Решение через интерполяционный многочлен Лагранжа
		cout << endl << "Метод Лагранжа:" << endl;
		cout << "Значение интерполяционного многочлена: " << result << endl;
		cout << "Значение абсолютной фактической погрешности: " << abs(func(Point) - result) << endl;	//Точность решения

		result = Newton(nodes, Point, power);														//Решение через интерполяционный многочлен Ньютона
		cout << endl << "Метод Ньютона:" << endl;
		cout << "Значение интерполяционного многочлена: " << result << endl;
		cout << "Значение абсолютной фактической погрешности: " << abs(func(Point) - result) << endl;	//Точность решения

		index = -1;																											//Возврат к начальным значениям переменных для повтороного выполнения программы
		power = points;
		nodes.clear();
		cout << endl << "Чтобы ввести новые значения для точки интерполяции или степени многочлена, введите 1" << endl;
		cout << "Чтобы закончить работу программы, введите 0" << endl << endl;
		cin >> timer;
	}
	return 0;
}

vecVector nodes(int points, double a, double b)											//Заполнение вектора точками, случайно расположенными на промежутке [a;b]
{
	vector<double> Node;																							//Вектор, представляющий собой одну точку на промежутке
	vecVector nodes;																									//Итоговый вектор точек
	for (int i = 0; i < points; ++i)
	{
		Node.push_back(i);																							//Номер точки
		Node.push_back(a + (b - a) * (double(i) + double((rand() % 100)) / 100) / points);	//Положение точки на промежутке [a;b]
		Node.push_back(0);																							//Выделяется память для будущего заполнения расстоянием от точки i до точки point(см. функцию sort())
		Node.push_back(func(Node[1]));																	//Значение функции func() в данной точке
		nodes.push_back(Node);
		Node.clear();
	}
	return nodes;
}

void print(vecVector const& nodes)																	//Вывод вектора точек на экран
{	//Выводится i[0] - номер точки , i[1] - ее положение на промежутке [a;b], i[3] - значение функции func() в этой точке
	int k = 0;
	cout << "xk		   |f(xk)" << endl;
	for (auto i : nodes)
	{
		cout << "x" << k << " =	" << i[1] << "			|f(x" << k << ") = " << i[3] << endl;
		++k;
	}
}

void printSorted(vecVector const& nodes, int power)										//Вывод отсортированного вектора точек на экран
{	//Выводится i[0] - номер точки , i[1] - ее положение на промежутке [a;b], i[2] - расстояние от точки до point(см. sort)
	//i[3] - значение функции func() в этой точке. Выводятся ближайшие power + 1 точки, что обеспечивается счетчиком count
	int count = 0;
	cout << "xk				||xk-x|				|f(xk)" << endl;
	for (auto i : nodes)
	{
		if (count == power + 1)
			break;
		cout << "x" << i[0] << " = " << i[1] << "			||x" << i[0] << "-x| = " << i[2] << "			|f(x" << i[0] << ") = " << i[3] << endl;
		++count;
	}
}

vecVector sort(vecVector nodes, double point)												//Сортировка вектора точек в зависимости от расстояние от точки до point
{
	for (int i = 0; i < nodes.size(); ++i)
		nodes[i][2] = abs(nodes[i][1] - point);													//Вычисление расстояния от i-той точки до point

	for (int i = 0; i < nodes.size() - 1; ++i)
		for (int j = 0; j < nodes.size() - i - 1; ++j)
			if (nodes[j][2] > nodes[j + 1][2])														//Сортировка вектора nodes в порядке увеличения расстояния до точки Fvalue
				nodes[j].swap(nodes[j + 1]);

	return nodes;
}

double Lagrange(vecVector const& nodes, double x, int power)	//Значение интерполяционного многочлена Лагранжа степени power в точке x,
{																															//построенного на точках nodes[i][1] с соответствующими значениями функции nodes[i][3]
	double a = 1;
	double b = 1;
	double result = 0;
	for (int i = 0; i <= power; ++i)
	{
		for (int j = 0; j <= power; ++j)
			if (j != i)
			{
				a *= x - nodes[j][1];
				b *= nodes[i][1] - nodes[j][1];
			}
		result += nodes[i][3] * a / b;
		a = 1;
		b = 1;
	}
	return result;
}

double Newton(vecVector const& nodes, double point, int power)
{	//Значение интерполяционного многочлена Ньютона степени power в точке x, построенного
	//на точках nodes[i][1] с соответствующими значениями функции nodes[i][3]
	double result = func(nodes[0][1]);
	double product = 1;
	for (int i = 1; i <= power; ++i)
	{
		product *= point - nodes[i - 1][1];
		result += dividedDifference(nodes, 0, i) * product;							//Используется формула с разделенной разностью
	}
	return result;
}

double dividedDifference(vecVector const& nodes, int index1, int index2)	//Вычисление разделенной разности
{
	if (index2 - index1 == 1)
		return (nodes[index2][3] - nodes[index1][3]) / (nodes[index2][1] - nodes[index1][1]);
	else
		return (dividedDifference(nodes, index1 + 1, index2) - dividedDifference(nodes, index1, index2 - 1)) / (nodes[index2][1] - nodes[index1][1]);
}