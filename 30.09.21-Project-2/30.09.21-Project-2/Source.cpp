#include<iostream>
using namespace std;

struct DNode
{
	int data;
	DNode* next;
	DNode* prev;
	DNode(int d = 0, DNode* n = nullptr, DNode* p = nullptr) :
		data(d), next(n), prev(p) {}
};


struct DList
{
	DNode* head, * tail;
	DList() { head = nullptr; tail = nullptr; }

	void add_first(int d)
	{
		DNode* t;
		t = new DNode(d, head, nullptr);
		if (head == nullptr)
			tail = t;
		else
			head->prev = t;
		head = t;
	}
	void del_first()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			return;
		}
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}
		DNode* t;
		t = head;
		head = head->next;
		head->prev = nullptr;
		delete t;
	}
	void print()
	{
		DNode* p = head;
		while (p != nullptr)
		{
			cout << p->data << "\t";
			p = p->next;
		}
		cout << endl;
	}
	void print_reverse()
	{
		DNode* p = tail;
		while (p != nullptr)
		{
			cout << p->data << "\t";
			p = p->prev;
		}
		cout << endl;
	}
	void Print()
	{
		print();
		print_reverse();
		cout << endl;
	}
	int length()
	{
		DNode* node = head;
		int c = 1;
		if (head == nullptr)
		{
			return 0;
		}
		if (head->next == nullptr)
		{
			return 1;
		}
		while (node->next != nullptr)
		{
			c++;
			node = node->next;
		}
		return c;
	}
	void insertp(int n, int a)
	{
		if (n == 0)
		{
			add_first(a);
		}
		else if (n == length() - 1)
		{
			DNode* t;
			t = new DNode(a, nullptr, tail);
			tail->next = t;
			tail = t;
		}
		else if (n > 0 and n < length() - 1)
		{
			DNode* t;
			DNode* node = head;
			for (int i = 1; i < n; ++i)
			{
				node = node->next;
			}
			t = new DNode(a, node->next, node);
			node->next->prev = t;
			node->next = t;
		}
	}
	void reverse()
	{
		DNode* node1 = tail;
		DNode* node2 = tail;
		while (node1->prev != nullptr)
		{
			node2 = node1->next;
			node1->next = node1->prev;
			node1->prev = node2;
			node1 = node1->next;
		}
		head->prev = head->next;
		head->next = nullptr;
		head = tail;
		tail = node1;
	}
	DNode* copy(DNode* x, DNode*& z)
	{
		if (x == nullptr)
			return nullptr;
		DNode* y;
		z = y;
		y = new DNode(x->data, copy(x->next, z), z);
		return y;
	}
	void del()
	{
		while (length() != 0)
		{
			del_first();
		}
	}
	DList(const DList& l)
	{
		head = copy(DNode * l.head, DNode * &l.head->next);
	}
	DList& operator=(const DList& l)
	{
		del();
		head = copy(DNode * l.head, DNode * &l.head->next);
	}
	~DList()
	{
		del();
	}
};



int main()
{
	DNode* t = nullptr;
	DList l;
	l.add_first(3);
	l.add_first(2);
	l.add_first(1);
	cout << "l:" << endl;
	l.Print();
	DList l1;
	l1.copy(l.head, t);
	cout << "l1:" << endl;
	l1.Print();
	return EXIT_SUCCESS;
}