#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

double func_f(double x, double y) { return sin(x - 2.2 * y) - x * y + 1; }
double func_g(double x, double y) { return 4 * x * x / 7 - y * y - 0.75; }
double func_f_dx(double x, double y) { return cos(x - 2.2 * y) - y; }
double func_f_dy(double x, double y) { return -2.2 * cos(x - 2.2 * y) - x; }
double func_g_dx(double x, double y) { return 8 * x / 7; }
double func_g_dy(double x, double y) { return -2 * y; }

//double func_f(double x, double y) { return sin(x) - y - 1.32; }
//double func_g(double x, double y) { return cos(y) - x + 0.85; }
//double func_f_dx(double x, double y) { return cos(x); }
//double func_f_dy(double x, double y) { return -1; }
//double func_g_dx(double x, double y) { return -1; }
//double func_g_dy(double x, double y) { return -sin(y); }
double determinant(double a, double b, double c, double d) { return a * d - b * c; }
double A_determ(double x, double y) { return determinant(func_f(x, y), func_f_dy(x, y), func_g(x, y), func_g_dy(x, y)); }
double B_determ(double x, double y) { return determinant(func_f_dx(x, y), func_f(x, y), func_g_dx(x, y), func_g(x, y)); }
double J_determ(double x, double y) { return determinant(func_f_dx(x, y), func_f_dy(x, y), func_g_dx(x, y), func_g_dy(x, y)); }
void Newton(double& a_x, double& b_x, double& a_y, double& b_y, double precision);
std::vector<double*> search(double* array, double a_x, double b_x, double a_y, double b_y, int N);
void correction(std::vector<double*>& roots, double precision);

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "Численное решение системы нелинейных уравнений" << std::endl;
	double a_x{ 0 }, a_y{ 0 }, b_x{ 0 }, b_y{ 0 };
	int N = 0;
	double precision = 0;
	std::cout << std::setprecision(18) << "Введите значение интервал для переменной x" << std::endl;
	std::cin >> a_x >> b_x;
	std::cout << "Введите значение интервал для переменной y" << std::endl;
	std::cin >> a_y >> b_y;
	std::cout << "Ведите значение N" << std::endl;
	std::cin >> N;
	std::cout << "Ведите значение precision" << std::endl;
	std::cin >> precision;
	std::cout << "Исходные параметры: " << a_x << "<= x <= " << b_x << ", " << a_y << "<= y <= " << b_y << std::endl;
	std::cout << "N = " << N << "precision = " << precision << std::endl;

	double* array = new double[4]{ 0 };
	std::vector<double*> sectors = search(array, a_x, b_x, a_y, b_y, N);
	std::vector<double*> roots;

	for (int i = 0; i < sectors.size(); ++i) {
		roots.push_back(new double[4]{ sectors[i][0], sectors[i][1], sectors[i][2], sectors[i][3] });
		Newton(roots[i][0], roots[i][1], roots[i][2], roots[i][3], precision);
		std::cout << std::endl;
	}

	correction(roots, precision);
	double x{ 0 }, y{ 0 };
	for (int i = 0; i < roots.size(); ++i) {
		x = (roots[i][0] + roots[i][1]) / 2;
		y = (roots[i][2] + roots[i][3]) / 2;
		std::cout << roots[i][0] << "<= xm <=" << roots[i][1] << ",   x = " << x <<
			",    " << roots[i][2] << " <= ym <=" << roots[i][3] << ",   y = " << y << std::endl << std::endl;
		std::cout << "|f(x,y) - 0| = " << abs(func_f(x, y)) << ",    |g(x,y) - 0| = " << abs(func_g(x, y)) << std::endl;
	}


	for (int i = 0; i < sectors.size(); ++i) delete[] sectors[i];
	for (int i = 0; i < roots.size(); ++i) delete[] roots[i];
	return EXIT_SUCCESS;
}


void Newton(double& a_x, double& b_x, double& a_y, double& b_y, double precision)
{
	std::cout << "Начальное приближение: [" << a_x << " <= x <= " << b_x << ",    " << a_y << " <= y <= " << b_y << std::endl;
	double x0 = (a_x + b_x) / 2;
	double y0 = (a_y + b_y) / 2;
	int i = 1;
	double x1 = x0 - A_determ(x0, y0) / J_determ(x0, y0);
	double y1 = y0 - B_determ(x0, y0) / J_determ(x0, y0);

	while (abs(x1 - x0) > 2 * precision or abs(y1 - y0) > 2 * precision)
	{
		std::cout << "x0 = " << x0 << ",   y0 = " << y0 << std::endl;
		x0 = x1;
		x1 = x0 - A_determ(x0, y0) / J_determ(x0, y0);
		y0 = y1;
		y1 = y0 - B_determ(x0, y0) / J_determ(x0, y0);
		++i;
		if (i > 1000000)
		{
			std::cout << "Количество итераций превысило 1000000, сходимость маловероятна." << std::endl;
			return;
		}
	}
	a_x = x0;
	b_x = x1;
	a_y = y0;
	b_y = y1;
	double x = (x1 + x0) / 2;
	double y = (y1 + y0) / 2;
	std::cout << "xm = " << x << ",  delta_x = " << abs(x0 - x1) / 2 << std::endl;
	std::cout << "ym = " << y << ",  delta_y = " << abs(y0 - y1) / 2 << std::endl;
	std::cout << "|f(xm,ym) - 0| = " << abs(func_f(x, y)) << "		|g(xm,ym) - 0| = " << abs(func_g(x, y)) << std::endl;
}

std::vector<double*> search(double* array, double a_x, double b_x, double a_y, double b_y, int N)
{
	double h_x = (b_x - a_x) / N;
	double h_y = (b_y - a_y) / N;
	double previous_x = a_x;
	double current_x = a_x + h_x;
	double previous_y = a_y;
	double current_y = a_y + h_y;
	double value_f = func_f(previous_x, previous_y);
	double value_g = func_g(previous_x, previous_y);
	double value_f_x, value_g_x, value_f_y, value_g_y, value_f_xy, value_g_xy;
	int size;

	std::vector<double*> result;
	while (current_y <= b_y) {
		value_f_y = func_f(previous_x, current_y);
		value_g_y = func_g(previous_x, current_y);
		while (current_x <= b_x) {
			value_f_x = func_f(current_x, previous_y);
			value_g_x = func_g(current_x, previous_y);
			value_f_xy = func_f(current_x, current_y);
			value_g_xy = func_g(current_x, current_y);
			if ((value_f * value_f_x <= 0 or value_f * value_f_y <= 0 or value_f * value_f_xy <= 0) &&
				(value_g * value_g_x <= 0 or value_g * value_g_y <= 0 or value_g * value_g_xy <= 0))
			{
				size = result.size();
				std::cout << "[a_x_" << size << ",b_x_" << size << "] = [" << previous_x << "," << current_x << "]" << std::endl;
				std::cout << "[a_y_" << size << ",b_y_" << size << "] = [" << previous_y << "," << current_y << "]" << std::endl;
				result.push_back(new double[4]{ previous_x, current_x, previous_y, current_y });
			}
			previous_x = current_x;
			current_x += h_x;
			value_f = value_f_x;
			value_f_y = value_f_xy;
			value_g = value_g_x;
			value_g_y = value_g_xy;
		}
		previous_y = current_y;
		current_y += h_y;
		previous_x = a_x;
		current_x = a_x + h_x;
		value_f = func_f(previous_x, previous_y);
		value_f_x = func_f(current_x, previous_y);
		value_g = func_g(previous_x, previous_y);
		value_g_x = func_g(current_x, previous_y);
	}
	std::cout << "Количество областей перемены знаков равно " << result.size() << std::endl << std::endl;
	return result;
}

void correction(std::vector<double*>& roots, double precision)
{
	int count = roots.size();
	int currentFirst = 0;
	int previousFirst = 0;
	std::vector<int> overlap{ currentFirst };
	int k = 0;
	int c = 0;
	int counting = 1;
	while (currentFirst < roots.size() - 1) {
		for (int i = 1 + currentFirst; i < roots.size(); ++i) {
			if ((abs(roots[i][0] - roots[overlap[0]][0]) <= 2 * precision) && (abs(roots[i][3] - roots[overlap[0]][3]) <= 2 * precision))
				overlap.push_back(i);
		}
		if (overlap.size() == 1) {
			++currentFirst;
			overlap[0] = currentFirst;
			continue;
		}

		k = 1;
		while (count != roots.size() + overlap.size() - 1) {
			roots.erase(roots.begin() + (overlap[k] - k + 1));
			++k;
		}
		count -= overlap.size() - 1;

		c = 0;
		for (auto x : overlap) {
			if (x > c + overlap[1]) {
				currentFirst = x - c;
				break;
			}
			++c;
		}

		if (currentFirst == overlap[0]) currentFirst = overlap[overlap.size() - 1] + 1 - k;
		overlap.clear();
		overlap.push_back(currentFirst);
	}
}