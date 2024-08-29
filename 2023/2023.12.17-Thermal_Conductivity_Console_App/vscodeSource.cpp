#include "winbgim.h"
#include <iostream>
#include <fstream>
#include <cmath>

double DISTANCE = 500;
double ALPHA_X = 0;
double BETA_U = 0;
double GAMMA_T = 0;

void putSquare(int x, int y, int color);
void rotate(double& x, double& y, double& z);
void rotate_x(double &y, double &z);
void rotate_y(double &x, double &z);
void rotate_z(double &x, double &y);
void projection1(double &projection_x, double &projection_y, double x, double x0_max, double y, double y0_max, double z);
int minimum(int x1, int x2, int x3, int x4);
void rotated_point(int *array, double x, double x0_max, double y, double y0_max, double z);
void rotated_lines(int *result, double **array, double x0_max, double y0_max, double h, double tau);
char *stringToCharArray(std::string);

void visualisation()
{
  int isComparisonTest;
  int N1 = 0;
  int N2 = 0;
  double h = 0;
  double tau = 0;
  double **u = nullptr;
  char *method_name = nullptr;
  std::ifstream input("text.txt");
  if (input)
  {
    input >> isComparisonTest;
    method_name = isComparisonTest == 1 ? new char[31] : new char[15];
    isComparisonTest = isComparisonTest == 1 ? 100 : 1;
    input >> method_name;
    input >> N1 >> N2;
    input >> h >> tau;
    u = new double* [N1 + 1]{nullptr};
    for (int i = 0; i <= N1; ++i)
    {
      u[i] = new double[N2 + 1];
    }

    for (int i = 0; i <= N1; ++i)
    {
      for (int j = 0; j <= N2; ++j)
      {
        input >> u[i][j];
        u[i][j] *= isComparisonTest;
      }
    }
  }
  input.close();

  char corrected_name[15];
  for (int i = 0; i < 15; ++i)
    corrected_name[i] = method_name[i];
  int window_width = -minimum(-(50 + 5 * N1), 500, 0, 0);
  int window_height = minimum((100 + 500 * u[N1][N2]), 500, 10000, 10000);

  int window_1 = initwindow(window_width, window_height, method_name, 0, 0, false, false);
  setfillstyle(1, 15);
  setcolor(0);
  setbkcolor(15);
  bar3d(0, 0, getmaxx(), getmaxy(), 0, 0);

  line(5, window_height - 20, 5, window_height - 20 - 500 * u[N1][N2]);
  outtextxy(10, window_height - 20 - 500 * u[N1][N2], (char *)"U[.][N2]");
  line(5, window_height - 20, 5 + 5 * N1, window_height - 20);
  outtextxy(5 + 5 * N1, window_height - 20, (char *)"X");
  for (int i = 0; i <= N1; ++i)
    putSquare(5 + 5 * i, window_height - 20 - 500 * u[i][N2], 0);
  system("pause");
  closegraph(window_1);

  std::cout << "DISTANCE = ? (suggested value: 100 - 1000)" << std::endl;
  std::cin >> DISTANCE;
  std::cout << "ALPHA_X = ? (suggested value: -1.0 - 1.0)" << std::endl;
  std::cin >> ALPHA_X;
  std::cout << "BETA_U = ? (suggested value: -1.0 - 1.0)" << std::endl;
  std::cin >> BETA_U;
  std::cout << "GAMMA_T = ? (suggested value: -1.0 - 1.0)" << std::endl;
  std::cin >> GAMMA_T;
  double x0{0}, y0{0}, z0{0};                // X[i], u[i][j], t[j]
  double projection_x0{0}, projection_y0{0}; // A projection of a 3D point(x0,y0,z0) onto the screen
  double k = 3 * round(N2 / N1);
  double x0_max = (3 * N1) / 2;
  double y0_max = (500 * u[N1][N2]) / 2;
  double z0_min = (-k * N2) / 2;

  double **array = new double *[4]{new double[3]{0, 500*u[0][0], 0}, new double[3]{3.0 * N1, 500*u[N1][0], 0},
  new double[3]{0, 500*u[0][N2], -k * N2}, new double[3]{3.0 * N1, 500*u[N1][N2], -k * N2} };

  int window_2 = initwindow(1200, 800);
  setcolor(0);
  setbkcolor(15);
  bar3d(0, 0, getmaxx(), getmaxy(), 0, 0);
  int *boundaries = new int[2]{0};
  rotated_lines(boundaries, array, x0_max, y0_max, h, tau);
  int horizontal_indent = boundaries[0];
  int vertical_indent = boundaries[1];
  for (int i = 0; i <= N1; ++i)
  {
    for (int j = 0; j <= N2; ++j)
    {
      x0 = 3 * i;
      y0 = 500 * u[i][j];
      z0 = -k * j;
      rotate(x0, y0, z0);
      projection1(projection_x0, projection_y0, x0, x0_max, y0, y0_max, -z0);
      putpixel((int)projection_x0 + horizontal_indent, -(int)projection_y0 + vertical_indent, 0);
    }
  }
  getch();
  closegraph();
  for (int i = 0; i < 4; ++i)
    delete[] array[i];
  delete[] array;
  for (int i = 0; i <= N1; ++i)
    delete[] u[i];
  delete[] u;
}

void putSquare(int x, int y, int color)
{
  for (int i = x - 1; i <= x + 1; ++i)
  {
    for (int j = y - 1; j <= y + 1; ++j)
    {
      putpixel(i, j, color);
    }
  }
}

void rotate(double &x, double &y, double &z)
{
  rotate_x(y, z);
  rotate_y(x, z);
  rotate_z(x, y);
}

void rotate_x(double &y, double &z)
{
  double y1 = y;
  y = y * cos(ALPHA_X) - z * sin(ALPHA_X);
  z = y1 * sin(ALPHA_X) + z * cos(ALPHA_X);
}

void rotate_y(double &x, double &z)
{
  double x1 = x;
  x = x * cos(BETA_U) + z * sin(BETA_U);
  z = -x1 * sin(BETA_U) + z * cos(BETA_U);
}

void rotate_z(double &x, double &y)
{
  double x1 = x;
  x = x * cos(GAMMA_T) - y * sin(GAMMA_T);
  y = x1 * sin(GAMMA_T) + y * cos(GAMMA_T);
}

void projection1(double &projection_x, double &projection_y, double x, double x0_max, double y, double y0_max, double z)
{
  projection_x = x0_max + DISTANCE * (x - x0_max) / (z + DISTANCE);
  projection_y = y0_max + DISTANCE * (y - y0_max) / (z + DISTANCE);
}

void rotated_point(int *array, double x, double x0_max, double y, double y0_max, double z)
{
  rotate(x, y, z);
  double projected_x = 0;
  double projected_y = 0;
  projection1(projected_x, projected_y, x, x0_max, y, y0_max, -z);
  array[0] = (int)projected_x;
  array[1] = -(int)projected_y;
}

int minimum(int x1, int x2, int x3, int x4)
{
  int result = x1;
  int array[4] = {x1, x2, x3, x4};
  for (int i = 1; i < 4; ++i)
  {
    if (array[i] < result)
      result = array[i];
  }
  return result;
}

void rotated_lines(int *result, double **array, double x0_max, double y0_max, double h, double tau)
{
  int **bigArray = new int *[4];
  for (int i = 0; i < 4; ++i)
  {
    bigArray[i] = new int[2]{0};
    rotated_point(bigArray[i], array[i][0], x0_max, array[i][1], y0_max, array[i][2]);
  }
  result[0] = 100 - minimum(bigArray[0][0], bigArray[1][0], bigArray[2][0], bigArray[3][0]);
  result[1] = 100 - minimum(bigArray[0][1], bigArray[1][1], bigArray[2][1], bigArray[3][1]);

  double x{array[1][0]}, y{0}, z{0};
  rotate(x, y, z);
  projection1(x, y, x, x0_max, y, y0_max, z);
  line(result[0], result[1], result[0] + (int)(x * 1.5), result[1] + (int)(y * 1.5));
  outtextxy(result[0] + (int)(x*1.2), result[1] + (int)(y * 1.2) - 20, (char *)"X");
  outtextxy(result[0] + (int)x, result[1] + (int)y, stringToCharArray(std::to_string(array[1][0] * h / 3)));

  x = 0;
  y = array[3][1];
  z = 0;
  rotate(x, y, z);
  projection1(x, y, x, x0_max, y, y0_max, z);
  line(result[0], result[1], result[0] + (int)(x * 1.2), result[1] - (int)(y * 1.2));
  outtextxy(result[0] + (int)(x * 1.2), result[1] - (int)(y * 1.2), (char *)"U");
  outtextxy(result[0] + (int)x, result[1] - (int)y, stringToCharArray(std::to_string(array[3][1] / 500)));

  line(result[0], result[1], result[0] + bigArray[2][0], result[1] + bigArray[2][1]);
  outtextxy(result[0] + bigArray[2][0] - 20, result[1] + bigArray[2][1] - 15, (char *)"t");
  outtextxy(result[0] + bigArray[2][0] - 20, result[1] + bigArray[2][1] + 15, stringToCharArray(std::to_string(0.01)));

  for (int i = 0; i < 4; ++i)
  {
    delete[] bigArray[i];
  }
  delete[] bigArray;
}

char *stringToCharArray(std::string line)
{
  char *result = new char[line.size()];
  for (int i = 0; i < line.size(); ++i)
    result[i] = line[i];
  return result;
}
