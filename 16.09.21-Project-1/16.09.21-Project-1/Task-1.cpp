#include <iostream>
using namespace std;


struct Node
{
	int data;
	Node* next;
	Node(int d = 0, Node* n = nullptr) : data(d), next(n) {}
};


struct List
{
	Node* head;
	List() { head = nullptr; }
};


int length(List L)
{
	Node* p = L.head;
	int i = 0;
	while (p != nullptr)
	{
		i++;
		p = p->next;
	}
	return i;
}


void add_first(int d, Node* head)
{
	Node* t;
	t = new Node;
	t->data = d;
	t->next = head;
	head = t;
}

int main()
{
	List L;
	add_first(7, L.head);
	add_first(8, L.head);
	add_first(9, L.head);
	add_first(1, L.head);
	add_first(2, L.head);
	cout << length(L) << endl;
}