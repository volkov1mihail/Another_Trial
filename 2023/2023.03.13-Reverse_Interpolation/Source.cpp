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

double func(double x)																	//�������, ������������ ������������� ������� ����� �������� ��������� ��������� ����������������
{
	//return log(1 + x);
	return sin(x) - x * x / 2;
}

void print_coeff(vector<double> vector)										//����� ������������� ���������� �� �����
{
	for (auto x : vector)
		cout << x << endl;
	return;
}

vecVector nodes(int points, double a, double b)						//���������� ������� �������, ���������� ��������������� �� ���������� [a;b]
{
	vecVector Nodes;																				//�������� ������
	vector<double> node;																		//������, �������������� ����� ���� ����� �� ����������
	for (int i = 0; i <= points; ++i)
	{
		node.push_back(i);																		//����� �����
		node.push_back(a + (b - a) * i / points);							//��������� ����� �� ���������� [a;b]
		node.push_back(0);																		//���������� ������ ��� �������� ���������� ����������� �� ����� i �� ����� x(��. ������� sort())
		node.push_back(func(node[1]));												//�������� ������� func() � ������ �����
		Nodes.push_back(node);
		node.clear();
	}
	return Nodes;
}

void print(vecVector nodes)									//����� ������� ����� �� �����
{//��������� i[0] - ����� ����� , i[1] - �� ��������� �� ���������� [a;b], i[3] - �������� ������� func() � ���� �����
	int k = 0;
	cout << "xk			 |f(xk)" << endl;
	for (auto i : nodes)
	{
		cout << k << "	x" << i[0] << " =	" << i[1] << "			|f(x" << i[0] << ") = " << i[3] << endl;
		++k;
	}
}

void print_reverse(vecVector nodes, int power)		//����� "�������������" �������, � ������� ���������� ������� ��������� ����� � �������� ������� func()
{																									//����� i[0] - ����� ����� , i[1] - �������� ������� func(), i[3] - �� ��������� �� ���������� [a;b]
	int count = 0;
	cout << "f(xk)				||f(xk)-F|				|f^-1(f(xk))" << endl;
	for (auto i : nodes)
	{
		if (count == power + 1)												//���� ������� ������� ���������� power ������ ���������� ����� - 1, �� ����� ����� �� ����������� ��� ������������
			break;
		cout << "f(x" << i[0] << ") = " << i[1] << "			||f(x" << i[0] << ")-F| = " << i[2] << "			|f^-1(f(x" << i[0] << ")) = " << i[3] << endl;
		++count;
	}
}

vecVector swap(vecVector nodes)	//"���������������" ������� ����� ������������ ������� ��������� ����� i[1] � �������� ������� � ��� i[3]
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

vecVector sort(vecVector nodes, double Fvalue)									//���������� ������� ����� � ����������� �� ���������� �� ����� Fvalue
{
	double a = 0;
	int length = nodes.size() - 1;
	for (int i = 0; i < length; ++i)
		nodes[i][2] = abs(nodes[i][1] - Fvalue);										//���������� ���������� �� i-��� ����� �� ����� Fvalue

	for (int i = 0; i < length; ++i)
		for (int j = 0; j < length - i; ++j)
			if (nodes[j][2] > nodes[j + 1][2])												//���������� ������� nodes � ������� ���������� ���������� �� ����� Fvalue
				nodes[j].swap(nodes[j + 1]);

	return nodes;
}

double Lagrange(vecVector nodes, double x, int power)	//�������� ����������������� ���������� �������� ������� power � ����� x,
{																											//������������ �� ������ nodes[i][1] � ���������������� ���������� ������� nodes[i][3]
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

vector<double> coefficients(vecVector nodes, int power)	//���������� ������������� ����������������� ���������� ������� ������� power
{																												//nodes - ������ ����� �� �������� ������ � ��������������� �� �������� ������� func()			
	double a = 1;
	vector<double> coeffVector{ nodes[0][3] };						//������ ������������� ��� ��������������� ��������� � ��������� ��� ����������������� ����������
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

double Newton(vecVector nodes, vector<double> coeffArray, double x, int power)//�������� ����������������� ���������� ������� ������� power � ����� x,
{																																							//������������ �� ������ nodes[i][1] � ���������������� ���������� ������� nodes[i][3]
	double result = coeffArray[0];																							//� �������������� coeffArray[i] ����� i-���� ��������� ���������� 
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
	cout << "xm = " << c << ",  d = " << (b - a) / 2 << ",		|f(xm)-F| = " << abs(func(c) - F) << ". ���������� ��������: " << i << endl;
}

void boundaries(int& count, Point& point_1, Point& point_2, vecPair& monotVector, Pair& monotInterval, bool& isIncreasing, double& boundaryValue, double Fvalue)
{ //�������, ������������ ������� ����������� ������������ � �������� �� � ������ monotVector

	//���� ����������� ��������, �� �������� point_1.y ������ ���� ����� �������� point_2.y,
	//�� ��������� ����� ���������� ������������, �� ������� ���������������� ��������� ������
	//� ����� ������ �� ����� ��������� ����� ����� ���������� � ��� ���������
	//����� �����, ���� ����� Fvalue ����� ����� ���������� ����������������� ���������� � ������� ������
	//����������(boundaryValue - �������� �� ����� �������, point_2.y - �� ������), ���������� ������������ �������� � monotVector ��� ��������� ����������������
	if (point_1.y <= point_2.y && isIncreasing == 0)
	{
		cout << "[a" << count << ",b" << count << "]=[" << monotInterval.first << "," << monotInterval.second
			<< "],		f'(a) = " << boundaryValue << ",	f'(b) = " << point_2.y << endl;
		if ((boundaryValue <= Fvalue && Fvalue <= point_2.y) or (boundaryValue >= Fvalue && Fvalue >= point_2.y))
			monotVector.push_back(monotInterval);

		monotInterval.first = point_1.x;											//������ ������ ���������� ������������(�����������)
		monotInterval.second = point_2.x;											//��� �����(�� ��� ���, ���� �� ������ �������� ��������)
		boundaryValue = point_1.y;														//�������� �� ����� ������� ���������� �����������
		isIncreasing = 1;																			//��������� ����, ��� ���������� �����������
		++count;																							//����� ������� ����������� ������������
	}
	//������, ����������� �������, �� � ������ ���������� �����������
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
	//���� �� ��������� �� ���� �� ����������������� �������, ������� ���������� ������������ ��� �� ����������
	//����� ������� monotInterval ���������� �� ������� point_2.x ��� ����������� ������
	else   monotInterval.second = point_2.x;
}

vecPair monotonicityIntervals(vecVector& nodes, int power, int N, double Fvalue)
{	//������� ��������� ���������� [a;b] �� ���������������� ���������� ������������ � ���������� �� ������ ������ ������� � ��������� �� ���������� �������� Fvalue
	int length = nodes.size() - 1;
	double step = (nodes[length][1] - nodes[0][1]) / N;						//���, � ������� ���������� ����� ����������������
	vector<double> endpoint = nodes[length];											//�������� ���������� ����� ��������� �� �������� ������
	int count = 0;																								//����� ������� ����������� ������������

	vector<double> coeffVector = coefficients(nodes, power);//������ ������������� ����������������� ���������� ������� ������� power � ������� ����� ����� ���������� [a;b]
	vecPair monotVector;																					//������, �������� ��� ��������� ���������� ������������, ���������� � ���� �������� Fvalue

	Point point_1{ nodes[0][1], nodes[0][3] };										//���� (x,y) � ����� ������� ���������� [a;b] (x = a, y = func(a))
	Point point_2;																								//���� (x,y) �� ���������� ���� �� ������� a
	point_2.x = point_1.x + step;																	//(x = a + step, y ����������� � ������� ����������������� ���������� �������)
	point_2.y = Newton(nodes, coeffVector, point_1.x + step, power);

	Pair monotInterval{ point_1.x, point_2.x };										//������� ���������� ������������, � ������� ������ ��������� ����� points_1 � point_2
	bool isIncreasing = (point_1.y <= point_2.y ? 1 : 0);					//��������� ����, �������� ������ ���������� ������������ ����������� �����������(1) ��� ��������(0)
	double boundaryValue = point_1.y;															//������������ �������� �������/����������������� ���������� �� ����� ������� ���������� ������������

	int k = power;																								//��������, ������������ ������� � ������� nodes
	int swapIndex = 0;																						//������, ����������� �� ������� � ������� nodes, ������� ����� �������� ������� � (k + 1)-�� ��������
	//���� ���������� ����� point_1 � point_2 �� ��� ���, ���� ������ �� ��������� ������� � ������� nodes(����� k == length)
	while (k < length){
		//�� ����� ������ �������� ����� ����������� ���� ���� ������ ������� ������ � ������� nodes
		//��� ��������, ����� �������, �������� ������� � ����� point_1.x(� ������� ���������� ����������), ���������� �� ������ (power + 1) �������� � ������� nodes
		//����� ��� ������ ������� Newton() �������� ���������������� ���� ������� power, ���������� �� ����� ������� � ����� point_1.x ��������
		//����� �������, � ����� ������ ������ ����� ����������� ���������������� ��������� ����� ������������ ��� ������������ ������� �� ���������� ������������ � ������� ���������
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

	cout << "���������� ����������� ������������ ����� " << count << endl << endl;
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
	cout << setprecision(13) << "������ ��������� ����������������, ������� 2, ������� f(x) = ln(1 + x)" << endl;
	cout << "������� ����� ��������� ��������" << endl;
	int points = 0;
	cin >> points;
	double a = 0;
	double b = 0;
	double Fvalue = 0;
	cout << "������� ����� ������� ������� � > -1" << endl;
	cin >> a;
	b = a;
	while (b <= a)
	{
		cout << "������� ������ ������� ������� b > " << a << endl;
		cin >> b;
	}

	int power = points;
	vecVector basicNodes = nodes(points - 1, a, b);
	vecVector nodes = basicNodes;
	print(basicNodes);

	int t = 1;
	while (t == 1)
	{
		cout << "������� �������� ������� Fvalue" << endl;
		cin >> Fvalue;
		while (power > points - 1)
		{
			cout << "������� ������� ���������������� ���������� power <= " << points - 1 << endl;
			cin >> power;
		}
		int N = 0;
		cout << "������ �������� N - ����� ��������� ����������� ��� ������ ����������� ������������" << endl;
		cin >> N;

		cout << endl << "3.1, ������ ������:" << endl << endl;
		vecPair monotVector = monotonicityIntervals(nodes, power, N, Fvalue);
		for (int i = 0; i < monotVector.size(); ++i)
			interpolationSearch(nodes, monotVector[i], Fvalue, power);


		cout << endl << "3.1, ������ ������:" << endl;
		cout << "������� �������� precision" << endl << endl;
		double precision;
		cin >> precision;

		for (int i = 0; i < monotVector.size(); ++i)
			bisectionSearch(nodes, monotVector[i], Fvalue, power, precision);
		cout << endl << "������� �������: " << monotVector.size() << endl;
		monotVector.clear();
		nodes = basicNodes;
		power = points;

		cout << endl << "����� ������ ����� �������� Fvalue, power, N ��� precision, ������� 1" << endl;
		cout << "����� ��������� ������ ���������, ������� 0" << endl << endl;
		cin >> t;
	}
	return 0;
}