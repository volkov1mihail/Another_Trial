#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <utility>
#include <clocale>
using namespace std;


typedef vector<vector<double>> vecVector;
typedef pair<double, double> Pair;
typedef vector<Pair> vecPair;

struct Point {
	double x;
	double y;
	Point(double data_x = 0, double data_y = 0) : x{ data_x }, y{ data_y }{};
};

double func(double x)																	//Функция, приближенное представление которой нужно получить благодаря обратному интерполированию
{
	//return log(1 + x);
	return sin(x) - x * x / 2;
}

void print_coeff(vector<double> vector)										//Вывод коэффициентов многочлена на экран
{
	for (auto x : vector)
		cout << x << endl;
	return;
}

vecVector nodes(int points, double a, double b)						//Заполнение вектора точками, равномерно распределенными на промежутке [a;b]
{
	vecVector Nodes;																				//Итоговый веткор
	vector<double> node;																		//Вектор, представляющий собой одну точку на промежутке
	for (int i = 0; i <= points; ++i)
	{
		node.push_back(i);																		//Номер точки
		node.push_back(a + (b - a) * i / points);							//Положение точки на промежутке [a;b]
		node.push_back(0);																		//Выделяется память для будущего заполнения расстоянием от точки i до точки x(см. функцию sort())
		node.push_back(func(node[1]));												//Значение функции func() в данной точке
		Nodes.push_back(node);
		node.clear();
	}
	return Nodes;
}

void print(vecVector nodes)									//Вывод вектора точек на экран
{//Выводится i[0] - номер точки , i[1] - ее положение на промежутке [a;b], i[3] - значение функции func() в этой точке
	int k = 0;
	cout << "xk			 |f(xk)" << endl;
	for (auto i : nodes)
	{
		cout << k << "	x" << i[0] << " =	" << i[1] << "			|f(x" << i[0] << ") = " << i[3] << endl;
		++k;
	}
}

void print_reverse(vecVector nodes, int power)		//Вывод "перевернутого" вектора, в котором поменялись местами положение точки и значение функции func()
{																									//Здесь i[0] - номер точки , i[1] - значение функции func(), i[3] - ее положение на промежутке [a;b]
	int count = 0;
	cout << "f(xk)				||f(xk)-F|				|f^-1(f(xk))" << endl;
	for (auto i : nodes)
	{
		if (count == power + 1)												//Если искомая степень многочлена power меньше количества точек - 1, то часть точек не потребуется для интерполяции
			break;
		cout << "f(x" << i[0] << ") = " << i[1] << "			||f(x" << i[0] << ")-F| = " << i[2] << "			|f^-1(f(x" << i[0] << ")) = " << i[3] << endl;
		++count;
	}
}

vecVector swap(vecVector nodes)	//"Переворачивание" вектора путем перестановки местами положения точки i[1] и значения функции в ней i[3]
{
	vecVector swappedNodes = nodes;
	double a = 0;
	for (int i = 0; i < nodes.size(); ++i)
	{
		swappedNodes[i][1] = nodes[i][3];
		swappedNodes[i][3] = nodes[i][1];
	}
	return swappedNodes;
}

vecVector sort(vecVector nodes, double Fvalue)									//Сортировка вектора точек в зависимости от расстояния до точки Fvalue
{
	double a = 0;
	int length = nodes.size() - 1;
	for (int i = 0; i < length; ++i)
		nodes[i][2] = abs(nodes[i][1] - Fvalue);										//Вычисление расстояния от i-той точки до точки Fvalue

	for (int i = 0; i < length; ++i)
		for (int j = 0; j < length - i; ++j)
			if (nodes[j][2] > nodes[j + 1][2])												//Сортировка вектора nodes в порядке увеличения расстояния до точки Fvalue
				nodes[j].swap(nodes[j + 1]);

	return nodes;
}

double Lagrange(vecVector nodes, double x, int power)	//Значение интерполяционного многочлена Лагранжа степени power в точке x,
{																											//построенного на точках nodes[i][1] с соответствующими значениями функции nodes[i][3]
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

vector<double> coefficients(vecVector nodes, int power)	//Вычисление коэффициентов интерполяционного многочлена Ньютона степени power
{																												//nodes - вектор точек на числовой прямой и соответствующих им значений функции func()			
	double a = 1;
	vector<double> coeffVector{ nodes[0][3] };						//Вектор коэффициентов при соответствующих слагаемых в выражении для интерполяционного многочлена
	double sum = 0;
	for (int k = 1; k <= power; ++k)
	{
		for (int i = 0; i <= k; ++i)
		{
			for (int j = 0; j <= k; ++j)
				if (j != i)
					a *= (nodes[i][1] - nodes[j][1]);

			sum += nodes[i][3] / a;
			a = 1;
		}
		coeffVector.push_back(sum);
		sum = 0;
	}
	return coeffVector;
}

double Newton(vecVector nodes, vector<double> coeffArray, double x, int power)//Значение интерполяционного многочлена Ньютона степени power в точке x,
{																																							//построенного на точках nodes[i][1] с соответствующими значениями функции nodes[i][3]
	double result = coeffArray[0];																							//и коэффициентами coeffArray[i] перед i-тыми степенями многочлена 
	double a = 1;
	for (int i = 1; i <= power; ++i)
	{
		for (int j = 0; j < i; ++j)
			a *= (x - nodes[j][1]);
		result += coeffArray[i] * a;
		a = 1;
	}
	return result;
}

double leftmost(vecVector v, double a, int n)
{
	double x = v[0][1];
	for (int i = 0; i <= n; ++i)
		x = min(x, v[i][1]);
	return x;
}

void bisection(Pair& p, double e, vecVector v, int n, double F)
{
	double a = p.first;
	double b = p.second;
	double c = (a + b) / 2;
	vector<double> coeff;
	int i = 0;
	if (v.size() == n)
	{
		coeff = coefficients(v, n - 1);
		while (b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(v, coeff, a, n - 1) - F)* (Newton(v, coeff, c, n - 1) - F) <= 0 ? b = c : a = c;
			++i;
		}
	}
	else
	{
		vecVector va = sort(v, a);
		vecVector vc = sort(v, c);
		while (leftmost(va, a, n) != leftmost(vc, c, n) && b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(va, coefficients(va, n), a, n) - F)* (Newton(vc, coefficients(vc, n), c, n) - F) <= 0 ? b = c : a = c;
			va = sort(v, a);
			vc = sort(v, c);
			++i;
		}
		coeff = coefficients(va, n);
		while (b - a > 2 * e)
		{
			c = (a + b) / 2;
			(Newton(va, coeff, a, n) - F)* (Newton(va, coeff, c, n) - F) <= 0 ? b = c : a = c;
			++i;
		}
	}
	c = (a + b) / 2;
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ",		|f(xm)-F| = " << abs(func(c) - F) << ". Количество итераций: " << i << endl;
}

void boundaries(int& count, Point& point_1, Point& point_2, vecPair& monotVector, Pair& monotInterval, bool& isIncreasing, double& boundaryValue, double Fvalue)
{ //Функция, определяющая границы промежутков монотонности и вносящая их в вектор monotVector

	//Если происходило убывание, но значение point_1.y меньше либо равно значению point_2.y,
	//то достигнут конец промежутка монотонности, на котором интерполяционный многочлен убывал
	//В таком случае на экран выводится номер этого промежутка с его границами
	//После этого, если число Fvalue лежит между значениями интерполяционного многочлена в крайних точках
	//промежутка(boundaryValue - значение на левой границе, point_2.y - на правой), промежуток монотонности вносится в monotVector для обратного интерполирования
	if (point_1.y <= point_2.y && isIncreasing == 0)
	{
		cout << "[a" << count << ",b" << count << "]=[" << monotInterval.first << "," << monotInterval.second
			<< "],		f'(a) = " << boundaryValue << ",	f'(b) = " << point_2.y << endl;
		if ((boundaryValue <= Fvalue && Fvalue <= point_2.y) or (boundaryValue >= Fvalue && Fvalue >= point_2.y))
			monotVector.push_back(monotInterval);

		monotInterval.first = point_1.x;											//Начало нового промежутка монотонности(возрастания)
		monotInterval.second = point_2.x;											//Его конец(до тех пор, пока не станет известно обратное)
		boundaryValue = point_1.y;														//Значение на левой границе промежутка возрастания
		isIncreasing = 1;																			//Индикатор того, что происходит возрастание
		++count;																							//Общий счетчик промежутков монотонности
	}
	//Случай, аналогичный первому, но с концом промежутка возрастания
	else if (point_1.y >= point_2.y && isIncreasing == 1)
	{
		cout << "[a" << count << ",b" << count << "]=[" << monotInterval.first << "," << monotInterval.second
			<< "],		f'(a) = " << boundaryValue << ",	f'(b) = " << point_2.y << endl;
		if ((boundaryValue <= Fvalue && Fvalue <= point_2.y) or (boundaryValue >= Fvalue && Fvalue >= point_2.y))
			monotVector.push_back(monotInterval);

		boundaryValue = point_1.y;
		monotInterval.first = point_1.x;
		monotInterval.second = point_2.x;
		isIncreasing = 0;
		++count;
	}
	//Если не произошел ни один из вышеперечисленных случаев, граница промежутка монотонности еще не достигнута
	//Тогда граница monotInterval сдвигается до позиции point_2.x для продолжения поиска
	else   monotInterval.second = point_2.x;
}

vecPair monotonicityIntervals(vecVector& nodes, int power, int N, double Fvalue)
{	//Функция разбивает промежуток [a;b] на последовательные промежутки монотонности и возвращает их внутри одного вектора с проверкой на содержание величины Fvalue
	int length = nodes.size() - 1;
	double step = (nodes[length][1] - nodes[0][1]) / N;						//Шаг, с которым изменяется точка интерполирования
	vector<double> endpoint = nodes[length];											//Наиболее отдаленная точка промежтка на числовой прямой
	int count = 0;																								//Общий счетчик промежутков монотонности

	vector<double> coeffVector = coefficients(nodes, power);//Вектор коэффициентов интерполяционного многочлена Ньютона степени power в крайней левой точке промежутка [a;b]
	vecPair monotVector;																					//Вектор, хранящий все найденные промежутки монотонности, содержащие в себе значение Fvalue

	Point point_1{ nodes[0][1], nodes[0][3] };										//Пара (x,y) в левой границе промежутка [a;b] (x = a, y = func(a))
	Point point_2;																								//Пара (x,y) на расстоянии степ от границы a
	point_2.x = point_1.x + step;																	//(x = a + step, y вычисляется с помощью интерполяционного многочлена Ньютона)
	point_2.y = Newton(nodes, coeffVector, point_1.x + step, power);

	Pair monotInterval{ point_1.x, point_2.x };										//Границы промежутка монотонности, в котором сейчас находятся точки points_1 и point_2
	bool isIncreasing = (point_1.y <= point_2.y ? 1 : 0);					//Индикатор того, является данный промежуток монотонности промежутком возрастания(1) или убывания(0)
	double boundaryValue = point_1.y;															//Фиксирование значения функции/интерполяционного многочлена на левой границе промежутка монотонности

	int k = power;																								//Итератор, перебирающий вершины в векторе nodes
	int swapIndex = 0;																						//Индекс, указывающий на вершину в веторке nodes, которую нужно поменять местами с (k + 1)-ой вершиной
	//Цикл перемещает точки point_1 и point_2 до тех пор, пока дойдет до последней вершины в векторе nodes(тогда k == length)
	while (k < length){
		//Во время работы внешнего цикла приведенный ниже цикл меняет порядок вершин в векторе nodes
		//Это делается, чтобы вершины, наиболее близкие к точке point_1.x(в которой происходят вычисления), находились на первых (power + 1) позициях в векторе nodes
		//Тогда при вызове функции Newton() строится интерполяционный член степени power, основанный на самых близких к точке point_1.x вершинах
		//Таким образом, в любой момент работы цикла построенный интерполяционный многочлен можно использовать для исследования функции на промежутки монотонности с высокой точностью
		while ((point_1.x - nodes[swapIndex][1]) < (nodes[k + 1][1] - point_1.x))
		{
			point_2.y = Newton(nodes, coeffVector, point_2.x, power);
			boundaries(count, point_1, point_2, monotVector, monotInterval, isIncreasing, boundaryValue, Fvalue);
			point_1.x = point_2.x;
			point_2.x += step;
			point_1.y = point_2.y;
		}
		nodes[k + 1].swap(nodes[swapIndex]);
		coeffVector = coefficients(nodes, power);
		point_1.y = Newton(nodes, coeffVector, point_1.x, power);
		++k;
		swapIndex = (k - power) % (power + 1);
	}

	while (point_1.x < endpoint[1])
	{
		point_2.y = Newton(nodes, coeffVector, point_2.x, power);
		boundaries(count, point_1, point_2, monotVector, monotInterval, isIncreasing, boundaryValue, Fvalue);
		point_1.x = point_2.x;
		point_2.x += step;
		point_1.y = point_2.y;
	}
	monotInterval.second = endpoint[1];
	cout << "[a" << count << ",b" << count << "]=[" << monotInterval.first << "," << monotInterval.second << "],		f'(a) = " << boundaryValue << ",	f'(b) = " << endpoint[3] << endl;
	if ((boundaryValue <= Fvalue && Fvalue <= point_2.y) or (boundaryValue >= Fvalue && Fvalue >= point_2.y))
		monotVector.push_back(monotInterval);
	++count;

	cout << "Количество промежутков монотонности равно " << count << endl << endl;
	return monotVector;
}

void interpolationSearch(vecVector nodes, Pair monotInterval, double Fvalue, int power)
{
	vector<double> coeff;
	vecVector suitaleNodes;
	for (int i = 0; i < nodes.size(); ++i)
		if (nodes[i][1] >= monotInterval.first && nodes[i][1] <= monotInterval.second)
			suitaleNodes.push_back(nodes[i]);

	int minimum = (power < suitaleNodes.size() - 1) ? power : suitaleNodes.size() - 1;
	suitaleNodes = sort(swap(suitaleNodes), Fvalue);
	cout << "print(suitaleNodes)::" << endl;
	print(suitaleNodes);
	coeff = coefficients(suitaleNodes, minimum);
	double answer = Lagrange(suitaleNodes, Fvalue, minimum);
	cout << "X = f^-1(Fvalue) = " << answer << ",	|f(X)-Fvalue| = " << abs(Fvalue - func(answer)) << endl;
}

void bisectionSearch(vecVector nodes, Pair monotInterval, double Fvalue, int power, double precision)
{
	vecVector suitaleNodes;
	for (int i = 0; i < nodes.size(); ++i)
		if (nodes[i][1] >= monotInterval.first && nodes[i][1] <= monotInterval.second)
			suitaleNodes.push_back(nodes[i]);

	if (suitaleNodes.size() > power + 1)
		bisection(monotInterval, precision, suitaleNodes, power, Fvalue);
	else
		bisection(monotInterval, precision, suitaleNodes, suitaleNodes.size(), Fvalue);
}

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Задача обратного интерполирования, вариант 2, функция f(x) = ln(1 + x)" << endl;
	cout << "Введите число табличных значений" << endl;
	int points = 0;
	cin >> points;
	double a = 0;
	double b = 0;
	double Fvalue = 0;
	cout << "Введите левую границу отрезка а > -1" << endl;
	cin >> a;
	b = a;
	while (b <= a)
	{
		cout << "Введите правую границу отрезка b > " << a << endl;
		cin >> b;
	}

	int power = points;
	vecVector basicNodes = nodes(points - 1, a, b);
	vecVector nodes = basicNodes;
	print(basicNodes);

	int t = 1;
	while (t == 1)
	{
		cout << "Введите значение функции Fvalue" << endl;
		cin >> Fvalue;
		while (power > points - 1)
		{
			cout << "Введите степень интерполирования многочлена power <= " << points - 1 << endl;
			cin >> power;
		}
		int N = 0;
		cout << "Ведите значение N - число начальных промежутков для поиска промежутков монотонности" << endl;
		cin >> N;

		cout << endl << "3.1, первый способ:" << endl << endl;
		vecPair monotVector = monotonicityIntervals(nodes, power, N, Fvalue);
		for (int i = 0; i < monotVector.size(); ++i)
			interpolationSearch(nodes, monotVector[i], Fvalue, power);


		cout << endl << "3.1, второй способ:" << endl;
		cout << "Введите точность precision" << endl << endl;
		double precision;
		cin >> precision;

		for (int i = 0; i < monotVector.size(); ++i)
			bisectionSearch(nodes, monotVector[i], Fvalue, power, precision);
		cout << endl << "Найдено решений: " << monotVector.size() << endl;
		monotVector.clear();
		nodes = basicNodes;
		power = points;

		cout << endl << "Чтобы ввести новые значения Fvalue, power, N или precision, введите 1" << endl;
		cout << "Чтобы закончить работу программы, введите 0" << endl << endl;
		cin >> t;
	}
	return 0;
}