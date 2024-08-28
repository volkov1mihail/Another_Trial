#include <iostream>
#include <iomanip>
#include <vector>
#include <clocale>
using namespace std;
//Программа, решающая задачу обратного интерполирования для заданной функции func(), промежутка [a;b]
//Для решения задачи используются два способа
//Первый способ - построение интерполяционного многочлена заданной степени power обратной функции func^(-1) там, где она существует
//Второй способ - использование биекции промежутков монотонности функции func() с достижением заданной точности precision
//Точность, с которой было найдено решение, выводится на экран для сравнения двух подходов

typedef vector<vector<double>> vecVector;
typedef pair<double, double> Pair;
typedef vector<Pair> vecPair;

struct Point {
	double x;
	double y;
	Point(double data_x = 0, double data_y = 0) : x{ data_x }, y{ data_y }{};
};

double func(double x)																			//Функция, приближенное представление которой нужно получить благодаря обратному интерполированию
{
	return log(1 + x);
	//return sin(x) - x * x / 2;
}

//Инициализация вектора вершин, вывод его на экран, "разворот" и сортировка относительно данного значения
vecVector nodes(int, double, double);
void print(vecVector const&);
vecVector swap(vecVector const&);
vecVector sort(vecVector, double);

//Интерполяционный многочлен в форме Лагранжа и в форме Ньютона
//Форма Ньютона используется в случае, когда нужно вычислять значение интерполяционного многочлена в
//большом количестве точек, расположенных вблизи одних и тех же вершин
//В таком случае есть возможность заранее заполнить вектор кожффициентов интерполяционного многочлена и далее их не пересчитывать
double Lagrange(vecVector const&, double, int);
vector<double> coefficients(vecVector const&, int);
double Newton(vecVector const&, vector<double> const&, double, int);

//Реализация первого способа решения задачи об обратном интерполировании
void boundaries(vecPair&, Pair&, Point const&, Point const&, int&, bool&, double&, double);
vecPair monotonicityIntervals(vecVector&, int, int, double);
void interpolationSearch(vecVector const&, Pair const&, int, double);

//Реализация второго способа решения задачи об обратном интерполировании
double leftmost(vecVector const&, int);
void bisection(vecVector const&, Pair const&, int, double, double);
void bisectionSearch(vecVector const&, Pair const&, int, double, double);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << setprecision(13) << "Задача обратного интерполирования, вариант 2, функция f(x) = ln(1 + x)" << endl;
	cout << "Введите число табличных значений" << endl;
	int points = 0;
	cin >> points;
	int power = points;

	double a = 0;
	double b = 0;
	cout << "Введите левую границу отрезка а > -1" << endl;
	cin >> a;
	b = a;
	while (b <= a)
	{
		cout << "Введите правую границу отрезка b > " << a << endl;
		cin >> b;
	}
	
	double Fvalue = 0;
	vecVector basicNodes = nodes(points - 1, a, b);
	vecVector nodes = basicNodes;
	print(basicNodes);

	int timer = 1;																													//Индикатор, определяющий, когда нужно закончить работу программы
	while (timer == 1)
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

		vecPair monotVector = monotonicityIntervals(nodes, power, N, Fvalue);	//Определение промежутков монотонности функции func()
		cout << endl << "3.1, первый способ:" << endl << endl;
		for (int i = 0; i < monotVector.size(); ++i)
			interpolationSearch(nodes, monotVector[i], power, Fvalue);					//Поиск решений путем обратного интерполирования


		cout << endl << "3.1, второй способ:" << endl;
		cout << "Введите точность precision" << endl << endl;
		double precision;
		cin >> precision;

		for (int i = 0; i < monotVector.size(); ++i)
			bisectionSearch(nodes, monotVector[i], power, Fvalue, precision);		//Поиск решений с помощью бисекции
		cout << endl << "Найдено решений: " << monotVector.size() << endl;
		monotVector.clear();																									//Возврат к начальным значениям переменных для повтороного выполнения программы
		nodes = basicNodes;
		power = points;

		cout << endl << "Чтобы ввести новые значения Fvalue, power, N или precision, введите 1" << endl;
		cout << "Чтобы закончить работу программы, введите 0" << endl << endl;
		cin >> timer;
	}
	return 0;
}

vecVector nodes(int points, double a, double b)						//Заполнение вектора точками, равномерно распределенными на промежутке [a;b]
{
	vecVector Nodes;																				//Итоговый веткор
	vector<double> node;																		//Вектор, представляющий собой одну точку на промежутке
	for (int i = 0; i <= points; ++i)
	{
		node.push_back(i);																		//Номер точки
		node.push_back(a + (b - a) * i / points);							//Положение точки на промежутке [a;b]
		node.push_back(0);																		//Выделяется память для будущего заполнения разностью между значением функции в точке и величиной Fvalue(см. функцию sort())
		node.push_back(func(node[1]));												//Значение функции func() в данной точке
		Nodes.push_back(node);
		node.clear();
	}
	return Nodes;
}

void print(vecVector const& nodes)												//Вывод вектора точек на экран
{//Выводится i[0] - номер точки , i[1] - ее положение на промежутке [a;b], i[3] - значение функции func() в этой точке
	int k = 0;
	cout << "xk			 |f(xk)" << endl;
	for (auto i : nodes)
	{
		cout << k << "	x" << i[0] << " =	" << i[1] << "			|f(x" << i[0] << ") = " << i[3] << endl;
		++k;
	}
}

vecVector swap(vecVector const& nodes)	//"Разворачивание" вектора путем перестановки местами положения точки i[1] и значения функции в ней i[3]
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

vecVector sort(vecVector nodes, double Fvalue)								//Сортировка вектора точек в зависимости от разности между значением функции в точке и величиной  Fvalue
{
	int length = nodes.size() - 1;
	for (int i = 0; i < length; ++i)
		nodes[i][2] = abs(nodes[i][1] - Fvalue);									//Вычисление разности для i-той точки

	for (int i = 0; i < length; ++i)
		for (int j = 0; j < length - i; ++j)
			if (nodes[j][2] > nodes[j + 1][2])											//Сортировка вектора nodes в порядке увеличения разности
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

vector<double> coefficients(vecVector const& nodes, int power)//Вычисление коэффициентов интерполяционного многочлена Ньютона степени power
{																															//nodes - вектор точек на числовой прямой и соответствующих им значений функции func()			
	double a = 1;
	vector<double> coeffVector{ nodes[0][3] };									//Вектор коэффициентов при соответствующих слагаемых в выражении для интерполяционного многочлена
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

double Newton(vecVector const& nodes, vector<double> const& coeffArray, double x, int power)
{	//Значение интерполяционного многочлена Ньютона степени power в точке x, построенного на точках nodes[i][1] 
	//с соответствующими значениями функции nodes[i][3] и коэффициентами coeffArray[i] перед i-тыми степенями многочлена
	double result = coeffArray[0];
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


void boundaries(vecPair& monotVector, Pair& monotInterval, Point const& point_1, Point const& point_2, int& count, bool& isIncreasing, double& boundaryValue, double Fvalue)
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

	vector<double> coeffVector = coefficients(nodes, power);			//Вектор коэффициентов интерполяционного многочлена Ньютона степени power в крайней левой точке промежутка [a;b]
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

	//Цикл перемещает точки point_1 и point_2 до тех пор, пока не "дойдет до" последней вершины в векторе nodes(тогда k == length)
	//Под "дойдет до" подразумевается момент, когда точка point_1.x окажется к последней вершине ближе, чем к вершине с индексом (length - 1 - power) % (power + 1)
	while (k < length) {
		//Во время работы внешнего цикла приведенный ниже цикл меняет порядок вершин в векторе nodes
		//Это делается, чтобы вершины, наиболее близкие к точке point_1.x(в которой происходят вычисления), находились на первых (power + 1) позициях в векторе nodes
		//Тогда при вызове функции Newton() строится интерполяционный член степени power, основанный на самых близких к точке point_1.x вершинах
		//Таким образом, в любой момент работы цикла построенный интерполяционный многочлен можно использовать для исследования функции на промежутки монотонности с высокой точностью
		while ((point_1.x - nodes[swapIndex][1]) < (nodes[k + 1][1] - point_1.x))
		{
			point_2.y = Newton(nodes, coeffVector, point_2.x, power);
			//Функция boundaries сравнивает значение функции в точка point_1 и point_2 и делает вывод о том, находятся ли точки в
			//промежутке возрастания, убывания или на границе промежутков монотонности
			boundaries(monotVector, monotInterval, point_1, point_2, count, isIncreasing, boundaryValue, Fvalue);
			//Продвижение вдоль числовой прямой
			point_1.x = point_2.x;
			point_2.x += step;
			point_1.y = point_2.y;
		}
		nodes[k + 1].swap(nodes[swapIndex]);												//Перестановка вершин в векторе, обеспечивающая правильное создание интерполяционного моногочлена
		coeffVector = coefficients(nodes, power);										//Пересчет коэффициентов интерполяционного многочлена с учетом перестановки
		++k;
		swapIndex = (k - power) % (power + 1);											//Перестановка иднекса для следующей перестановки
	}

	//Цикл производит поиск промежутков монотонности до тех пор, пока точка point_1.x не дойдет до концапромежутка [a;b]
	while (point_1.x < endpoint[1])
	{
		point_2.y = Newton(nodes, coeffVector, point_2.x, power);
		boundaries(monotVector, monotInterval, point_1, point_2, count, isIncreasing, boundaryValue, Fvalue);
		point_1.x = point_2.x;
		point_2.x += step;
		point_1.y = point_2.y;
	}
	monotInterval.second = endpoint[1];														//Фиксирование последнего промежутка монотонности
	//Вывод последнего промежутка монотонности на экран и проверка, попадает ли в него значение Fvalue
	cout << "[a" << count << ",b" << count << "]=[" << monotInterval.first << "," << monotInterval.second << "],		f'(a) = " << boundaryValue << ",	f'(b) = " << endpoint[3] << endl;
	if ((boundaryValue <= Fvalue && Fvalue <= point_2.y) or (boundaryValue >= Fvalue && Fvalue >= point_2.y))
		monotVector.push_back(monotInterval);
	++count;
	//Т.к. count учитывает все найденные промежукти монотонности, а не только те, в которые входит значение Fvalue, его величина чаще всего будет больше monotVector.size()

	cout << "Количество промежутков монотонности равно " << count << endl << endl;
	return monotVector;
}

void interpolationSearch(vecVector const& nodes, Pair const& monotInterval, int power, double Fvalue)
{	//Функция, решающая задачу обратного интерполирования путем построения построения интерполяционного многочлена обратной функции func^(-1)
	//Для обеспечения существования обратной функции, рассматривается промежуток монотонности monotInterval
	vecVector suitableNodes;																			//Вектор из вершин, содержащихся в данном промежутке монотонности
	for (int i = 0; i < nodes.size(); ++i)												//Заполнение этого вектора подходящими вершинами
		if (nodes[i][1] >= monotInterval.first && nodes[i][1] <= monotInterval.second)
			suitableNodes.push_back(nodes[i]);

	//В случае, если в промежутке монотонности находится недостаточно вершин для построения интерполяционного многочлена степени power,
	//на основании подходящих вершин строится интерполяционный многочлен максимальной возможной степени 
	int minimum = (power <= suitableNodes.size() - 1) ? power : suitableNodes.size() - 1;
	suitableNodes = swap(suitableNodes);													//"Разворот" вектора для обратного интерполирования
	cout << "print(suitableNodes)::" << endl;											//Вывод вектора на экран
	print(suitableNodes);

	double answer = Lagrange(suitableNodes, Fvalue, minimum);			//Результат решения задачи обратного инетрполирования
	cout << "X = f^-1(Fvalue) = " << answer << ",	|f(X)-Fvalue| = " << abs(Fvalue - func(answer)) << endl;	//Определение точности решения
}


double leftmost(vecVector const& nodes, int power)
{	//Функция, возвращающая координату вершины вектора nodes, находящуюся левее всех других(из первых power + 1)
	double result = nodes[0][1];
	for (int i = 0; i <= power; ++i)
		result = min(result, nodes[i][1]);
	return result;
}

void bisection(vecVector const& nodes, Pair const& monotInterval, int power, double Fvalue, double precision)
{	//Функция решает задачу обратного интерполирования с заданной степенью интерполяционного многочлена power путем разбиения 
	//данного промежутка монотонности на промежутки смены знака функции, длина которых постепенно уменьшается
	vector<double> coeffVector;														//Вектор коэффициентов интерполяционного многочлена Ньютона степени power в некоторой точке
	double left = monotInterval.first;										//Левый конец рассматриваемого промежутка
	double right = monotInterval.second;									//Правый конец рассматриваемого промежутка
	double middle = 0;																		//Середина рассматриваемого промежутка
	int count = 0;																				//Количество проделанных итераций
	double leftSign = 0;																	//Знак функции на левом конце промежутка
	double middleSign = 0;																//Знак функции на правом конце промежутка

	if (nodes.size() == power + 1)
	{	//В данном случае все вершины nodes участвуют в построении интерполяционного многочлена для любой точки промежутка
		coeffVector = coefficients(nodes, power);						//Соответствующие коэффициенты интерполяционного многочлена
		while (right - left > 2 * precision)								//Ограничение на ширину рассматриваемого промежутка
		{	//Цикл определяет, в какой половине рассматриваемого промежутка происходит смена знака функции func() - Fvalue
			//Для этого вычисляется произведение значений этой функции в точках left и middle
			//Если leftSign * middleSign <= 0, смена знака происходит на левой половине промежутка, которая выбирается за новый промежуток для продолжения цикла
			//В противном случае выбирается правая половина промежутка
			middle = (left + right) / 2;
			leftSign = Newton(nodes, coeffVector, left, power) - Fvalue;
			middleSign = Newton(nodes, coeffVector, middle, power) - Fvalue;

			(leftSign * middleSign <= 0) ? right = middle : left = middle;
			++count;																					//Учитывание проделанной итерации
		}
	}
	else
	{	//В данном случае часть вершин будет использоваться для построения интерполяционного многочлена около левой точки промежутка, а часть - около средней
		//Эти вершины определяются путем сортировки вектора nodes относительно левой и средней точек промежутка
		//Функция lefmost вызывается для сравнения самых левых используемых вершин в двух наборах
		//Если самые левые вершины совпадают, то точки left и middle достаточно близки, чтобы для них можно было использовать одинаковый набор вершин
		vecVector leftNodes = sort(nodes, left);
		vecVector middleNodes = sort(nodes, middle);
		while (leftmost(leftNodes, power) != leftmost(middleNodes, power))
		{	//Процедура, аналогичная первому случаю, но с учетом изменения наборов вершин при каждой итерации
			middle = (left + right) / 2;
			leftSign = Newton(leftNodes, coefficients(leftNodes, power), left, power) - Fvalue;
			middleSign = Newton(middleNodes, coefficients(middleNodes, power), middle, power) - Fvalue;

			(leftSign * middleSign <= 0) ? right = middle : left = middle;
			leftNodes = sort(nodes, left);
			middleNodes = sort(nodes, middle);
			++count;																					//Учитывание проделанной итерации
		}

		coeffVector = coefficients(leftNodes, power);
		while (right - left > 2 * precision)
		{	//Поиск промежутков смены знака функции func() - Fvalue до тех пор, пока не будет достигнута необходимая точность
			middle = (left + right) / 2;
			leftSign = Newton(leftNodes, coeffVector, left, power) - Fvalue;
			middleSign = Newton(middleNodes, coeffVector, middle, power) - Fvalue;

			(leftSign * middleSign <= 0) ? right = middle : left = middle;
			++count;																					//Учитывание проделанной итерации
		}
	}
	middle = (left + right) / 2;													//За окончательный ответ выбирается середина последнего промежутка
	cout << "xm = " << middle << ",  Delta = " << (right - left) / 2 << ",		|f(xm)-F| = " << abs(func(middle) - Fvalue) << ". Количество итераций: " << count << endl;
}

void bisectionSearch(vecVector const& nodes, Pair const& monotInterval, int power, double Fvalue, double precision)
{	//Функция, решающая задачу обратного интерполирования с помощью бисекции.
	//Для данного промежутка монотонности monotInterval определяются вершины вектора nodes, попадающие в него
	vecVector suitableNodes;																			//Вектор из вершин, содержащихся в данном промежутке монотонности
	for (int i = 0; i < nodes.size(); ++i)												//Заполнение этого вектора подходящими вершинами
		if (nodes[i][1] >= monotInterval.first && nodes[i][1] <= monotInterval.second)
			suitableNodes.push_back(nodes[i]);

	//В случае, если в промежутке монотонности находится недостаточно вершин для построения интерполяционного многочлена степени power,
	//на основании подходящих вершин строится интерполяционный многочлен максимальной возможной степени
	int minimum = (power <= suitableNodes.size() - 1) ? power : suitableNodes.size() - 1;
	cout << "print(suitableNodes)::" << endl;											//Вывод вектора на экран
	print(suitableNodes);

	bisection(suitableNodes, monotInterval, minimum, Fvalue, precision);	//Результат решения задачи обратного инетрполирования
}