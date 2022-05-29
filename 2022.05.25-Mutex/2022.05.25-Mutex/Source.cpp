#include<random>
#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<omp.h> 
#include<chrono>
#include<queue>
#include<condition_variable>
using namespace std;

condition_variable cv;
int object;
mutex m;
queue < int> q;
bool flag = false;
bool work1 = true, work2 = true;
vector<int> v1, v2;
mt19937 mt;
uniform_int_distribution<int> r(0, 100);

void factory();
void consumer();
void check_all();
void factory_m();
void consumer_m();
void check_all_m();
void factory_cv();
void consumer_cv();
void check_all_cv();
void factory_cvm();
void consumer_cvm();
void check_all_cvm();
void factory_3();
void consumer_3();
void check_all_3();


bool f()
{
	return !q.empty();
}


void factory()
{
	while (work1)
	{
		if (flag == true) { this_thread::sleep_for(chrono::microseconds(r(mt))); }
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
		}
	}
}


void consumer()
{
	while (work2)
	{
		if (flag == false) this_thread::sleep_for(chrono::microseconds(r(mt)));
		else
		{
			v2.push_back(object);
			flag = false;
		}
	}
}


void check_all()
{
	thread f1(factory);
	thread f2(factory);
	thread c1(consumer);
	thread c2(consumer);
	thread c3(consumer);
	this_thread::sleep_for(1s);
	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();
	cout << "v1=";
	for (int i = 0; i < v1.size(); i++) {
		cout << v1[i] << " ";
	}
	cout << endl;
	cout << "v2=";
	for (int i = 0; i < v2.size(); i++) {
		cout << v2[i] << " ";
	}
	cout << endl;
	v1 == v2 ? cout << "v1 = v2" << endl : cout << "v1 != v2" << endl;
}


void factory_m()
{
	while (work1)
	{
		m.lock();
		if (flag == true)
		{
			m.unlock();
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		}
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
			m.unlock();
		}
	}
}


void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (flag == false)
		{
			m.unlock();
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		}
		else
		{
			v2.push_back(object);
			flag = false;
			m.unlock();
		}
	}
}


void check_all_m()
{
	thread f1(factory_m);
	thread f2(factory_m);
	thread c1(consumer_m);
	thread c2(consumer_m);
	thread c3(consumer_m);
	this_thread::sleep_for(1s);
	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();
	cout << "v1=";
	for (int i = 0; i < v1.size(); i++) {
		cout << v1[i] << " ";
	}
	cout << endl;
	cout << "v2=";
	for (int i = 0; i < v2.size(); i++) {
		cout << v2[i] << " ";
	}
	cout << endl;
	v1 == v2 ? cout << "v1 = v2" << endl : cout << "v1 != v2" << endl;
}


int main()
{
	srand(time(0));
	//check_all();
	//check_all_m();
	//check_all_cv();
	check_all_cvm();
	//check_all_3();
	return 0;
}


void factory_cv()
{
	while (work1)
	{
		if (!q.empty())
			this_thread::sleep_for(chrono::microseconds(r(mt)));

		else q.push(r(mt));
	}
}


void consumer_cv()
{
	while (work2)
	{
		if (q.empty())
			this_thread::sleep_for(chrono::microseconds(r(mt)));

		else
		{
			cout << q.front() << " ";
			q.pop();
		}
	}
}


void check_all_cv()
{
	thread f1(factory_cv);
	thread f2(factory_cv);
	thread c1(consumer_cv);
	thread c2(consumer_cv);
	thread c3(consumer_cv);
	this_thread::sleep_for(1s);
	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();
	cout << "q= ";
	while (!q.empty())
	{
		int val = q.front();
		q.pop();
		cout << val << " ";
	}
	cout << endl;
}


void factory_cvm()
{
	while (work1)
	{
		m.lock();
		if (!q.empty())
		{
			m.unlock();
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		}
		else
		{
			int c = r(mt);
			q.push(c);
			v1.push_back(c);
			m.unlock();
		}
	}
}


void consumer_cvm()
{
	while (work2)
	{
		m.lock();
		if (q.empty())
		{
			m.unlock();
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		}
		else
		{
			v2.push_back(q.front());
			q.pop();
			m.unlock();
		}
	}
}


void check_all_cvm()
{
	thread f1(factory_cvm);
	thread f2(factory_cvm);
	thread c1(consumer_cvm);
	thread c2(consumer_cvm);
	thread c3(consumer_cvm);
	this_thread::sleep_for(1s);
	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();
	cout << "v1=";
	for (int i = 0; i < v1.size(); i++) {
		cout << v1[i] << " ";
	}
	cout << endl;
	cout << "v2=";
	for (int i = 0; i < v2.size(); i++) {
		cout << v2[i] << " ";
	}
	cout << endl;
	v1 == v2 ? cout << "v1 = v2" << endl : cout << "v1 != v2" << endl;
}


void factory_3()
{
	while (work1)
	{
		unique_lock <mutex> l(m);
		if (!q.empty())
		{
			cv.notify_one();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			q.push(r(mt));
			v1.push_back(q.front());
			cv.notify_one();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
	}
	cv.notify_all();
}


void consumer_3()
{
	while (work2)
	{
		unique_lock <mutex> l(m);
		cv.wait(l, f);
		if (q.empty()) return;
		else
		{
			v2.push_back(q.front());
			q.pop();
			cv.notify_all();
			return;
		}
		v2.push_back(q.front());
		q.pop();
	}
}


void check_all_3()
{
	thread f1(factory_3);
	thread f2(factory_3);
	thread c1(consumer_3);
	thread c2(consumer_3);
	thread c3(consumer_3);
	this_thread::sleep_for(1s);
	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();
	cout << endl;
	v1 == v2 ? cout << "v1 = v2" << endl : cout << "v1 != v2" << endl;
	cout << "v2= ";
	for (int i = 0; i < v2.size(); i++) {
		cout << v2[i] << " ";
	}
}