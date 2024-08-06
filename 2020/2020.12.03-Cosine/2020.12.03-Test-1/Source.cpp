#include<iostream>
#include<cmath>
#include<iomanip>


double myFunction(double x, int n){										//функция, вычисляющая приближенное значение косинуса угла
	double s = 1;														//с помощью разложения в ряд Тейлора
	double d = -x * x / 2;
	for (int i = 2; abs(d) >= pow(10, -n); i += 2)
	{
		s += d;															//сложение разных членов ряда Тейлора
		d = -d * x * x / (i + 1) / (i + 2);								//вычисление следующего члена ряда, используя предыдущий
	}
	return s;
}


int main(){
	setlocale(LC_ALL, "Russian");

	double x = 0;
	int n = 0;
	std::cout << "Введите x - размер угла в градусах" << std::endl;
	std::cin >> x;

	x = x * acos(-1) / 180;												//значение угла в радианах, которое понадобится при вычислении косинуса

	std::cout << "Введите n - порядок точности" << std::endl;
	std::cin >> n;
	std::setprecision(n);

	std::cout << "cos(x) = " << cos(x) << std::endl;					//сравнение значения косинуса угла, полученного с помощью библиотеки 
	std::cout << "cos(x) ~ " << myFunction(x, n) << std::endl;			//cmath и функции myFunction

	return 0;
}