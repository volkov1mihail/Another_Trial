#include<random>
#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;
//Программа имитирует взаимодействие завода(factory) и потребителя(consumer)
//Если на складе(в очереди q) отсутствует товар(очередь пуста), завод передает одну единицу товара на склад
//Если на складе есть товар, потребитель забирает товар со склада
//Одновременно в работу запускается 2 потока, выполняющих должности завода, и 3 потока, выполняющих должности потребителя
//Исследуется поведение программы в случае использования библиотеки mutex, condition_variable и только с библиотекой tread

//Генерация случайных чисел, играющих роль товара
mt19937 mt;
uniform_int_distribution<int> r(0, 100);

bool flag = false;													//Индикатор того, заполнен ли склад
bool work1 = true; bool work2 = true;				//Индикаторы того, идет ли работу по заполнению(work1) и опустошению склада(work2)

mutex m;
queue<int> q;																//Склад
condition_variable cv;

//Функции, не использующие mutex и conditional_variable
void factory();
void consumer();
void check_all();

//Функции, использующие mutex
void factory_m();
void consumer_m();
void check_all_m();

//Функции, использующие mutex и conditional_variable
bool is_full() { return !q.empty(); }
void factory_cv();
void consumer_cv();
void check_all_cv();

int main()
{
	srand(time(0));

	//check_all();
	//work1 = true;
	//work2 = true;
	//flag = false;
	//system("pause");

	check_all_m();
	work1 = true;
	work2 = true;
	flag = false;
	system("pause");

	check_all_cv();

	return 0;
}


void factory()											//Функция, добавляющая в очередь элемент в случае, если она пуста
{
	while (work1)
	{
		if (!q.empty())
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		else
			q.push(r(mt));
	}
}

void consumer()											//Функция, удаляющая из очереди элемент в случае, если она не пуста
{
	while (work2)
	{
		if (q.empty())
			this_thread::sleep_for(chrono::microseconds(r(mt)));
		else
			q.pop();
	}
}

void check_all()										//Функция, запускающая несколько потоков, одновременно имеющих доступ к очереди q
{
	//Потоки, пополняющие очередь
	thread f1(factory);
	thread f2(factory);
	//Потоки, опусташающие очередь
	thread c1(consumer);
	thread c2(consumer);
	thread c3(consumer);
	this_thread::sleep_for(1s);				//Время наблюдения за работой потоков

	work1 = false;										//Остановка потоков
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();

	cout << "q = ";										//Проверка, остались ли какие-то элементы в очереди(очередь должна быть пуста)
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

void factory_m()										//Функция, добавляющая в очередь элемент в случае, если она пуста(с использованием mutex)
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
			q.push(r(mt));
			m.unlock();
		}
	}
}

void consumer_m()										//Функция, удаляющая из очереди элемент в случае, если она не пуста(с использованием mutex)
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
			q.pop();
			m.unlock();
		}
	}
}

void check_all_m()									//Функция, запускающая несколько потоков, одновременно имеющих доступ к очереди q(с использованием mutex)
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

	cout << "q = ";
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

void factory_cv()										//Пополнение очереди, испольуя mutex и conditional_variable
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
			cv.notify_one();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
	}
	cv.notify_all();
}

void consumer_cv()									//Опустошение очереди, испольуя mutex и conditional_variable
{
	while (work2)
	{
		unique_lock <mutex> l(m);
		cv.wait(l, is_full);
		if (q.empty()) return;
		else
		{
			q.pop();
			cv.notify_all();
			return;
		}
		q.pop();
	}
}

void check_all_cv()								//Запуск потоков, использующих mutex и conditional_variable
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

	cout << "q = ";
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}