#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
#include<iomanip>
#include <cstdlib>
#include <omp.h>
#include <string>
using namespace std;
using namespace std::chrono;


const int N = 100000000;
const int n = N + 1;
vector <double> v(n);


long double pi_(int, int);
long double Multi_pi(int);
int block_size(int);
long double pi_slow();
int MultiThreadFind(int, string, string);
int Find_thread(string, string, int, int);
int Find(string, string, int, int);
int Find_slow(string, string);



int main()
{
	srand(time(0));
	string what = "2518";
	string s = "1298251817249918287931857251801928848235092358923980983460293850923241765953279125182963197642197481276525923956839039152159174921678293297342971428417292783927952397124572195427698329735967129748521794653895934946179452542926389379681279432917529863297341972582997296463192439762982979159963972532973491672827387274910247198759289182361047019230192398127497812659182125091720398102937918292836587391824659180410928301927918239817287650182791825012948029384092371";
	double pi = pi_slow();
	pi = Multi_pi(2);
	int n = Find_slow(what, s);
	n = MultiThreadFind(8, what, s);
	return 0;
}



long double pi_slow()
{
	long double pi = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < N; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	}
	pi = pi * 4 / N;
	cout << "pi_slow::" << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	cout << "pi_slow:: " << omp_get_wtime() - t << endl;
	return pi;
}


long double pi_(int threads, int first_index)
{
	long double pi = 0;
	int bl_size = block_size(threads);
	for (int i = first_index; i < min(first_index + bl_size, N); i++)
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * N)) * ((2.0 * i - 1) / (2.0 * N))));
	return pi;
}


long double Multi_pi(int threads)
{
	long double pi = 0;
	int bl_size = block_size(threads);
	int first_index = 0;
	int i = 0;
	vector<future <long double>> fut(threads);
	double t = omp_get_wtime();
	while (first_index < N)
	{
		fut[i] = async(pi_, threads, first_index);
		first_index += bl_size;
		i++;
	}
	for (int j = 0; j < i; ++j)
	{
		pi += fut[j].get();
	}
	pi = pi * 4 / N;
	cout << "Multi_pi:: " << omp_get_wtime() - t << endl;
	cout << "Multi_pi::" << endl;
	cout << setprecision(15) << "pi = " << pi << endl;
	return pi;
}


int block_size(int threads)
{
	return N / threads + (N % threads ? 1 : 0);
}


int MultiThreadFind(int thread, string what, string s)
{
	int n = 0;
	int i = 1;
	int length = s.size() / thread + (s.size() % thread ? 1 : 0);
	int first_index = length;
	vector<future <int>> fut(thread);
	double t = omp_get_wtime();

	fut[0] = async(Find_thread, what, s, thread, 1 - what.size());
	while (first_index < s.size())
	{
		fut[i] = async(Find_thread, what, s, thread, first_index - what.size() + 1);
		first_index += length;
		i++;
	}
	for (int j = 0; j < i; ++j)
	{
		n += fut[j].get();
	}
	cout << "MultiThreadFind:: " << omp_get_wtime() - t << endl;
	cout << "n = " << n << endl;
	return n;
}


int Find_thread(string what, string s, int thread, int first_index)
{
	int n = 0;
	int length = s.size() / thread + (s.size() % thread ? 1 : 0);
	return n = Find(what, s, first_index, first_index + length + what.size() - 1);
}


int Find(string what, string s, int a, int b)
{
	int n = 0;
	int i = a < 0 ? 0 : a;
	int j = 0;
	int l = 0;
	while (i < b + 1 - what.size())
	{
		while (j < what.size() && j + i < s.size())
		{
			l = what[j] == s[i + j] ? l + 1 : l;
			++j;
		}
		n = l == what.size() ? n + 1 : n;
		j = 0;
		l = 0;
		++i;
	}
	return n;
}


int Find_slow(string what, string s)
{
	int n = 0;
	int i = 0;
	int j = 0;
	int l = 0;
	double t = omp_get_wtime();
	while (i < s.size())
	{
		while (j < what.size() && j + i < s.size())
		{
			l = what[j] == s[i + j] ? l + 1 : l;
			++j;
		}
		n = l == what.size() ? n + 1 : n;
		j = 0;
		l = 0;
		++i;
	}
	cout << "Find_slow:: " << omp_get_wtime() - t << endl;
	cout << "n = " << n << endl;
	return n;
}