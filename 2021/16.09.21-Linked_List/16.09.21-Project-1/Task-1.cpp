#include <iostream>

struct Node {                         //структура узла
	int data;
	Node* next;
	Node(int d = 0, Node* n = nullptr) : data(d), next(n) {}
};

struct List {                         //список, состо€щий из последовательно св€занных узлов
	Node* head;
	List() { head = nullptr; }
};

int length(List L);                   //функци€ дл€ подсчета длины списка
void addFirst(int d, List& L);        //функци€, добавл€юща€ новый узел в начало списка(переназнача€ голову списка)

int main(){
	List L;
	addFirst(7, L);
	addFirst(8, L);
	addFirst(9, L);
	addFirst(1, L);
	addFirst(2, L);

	std::cout << L.head->data << std::endl;
	std::cout << length(L) << std::endl;
	
	return EXIT_SUCCESS;
}

int length(List L) {
	Node* p = L.head;
	int i = 0;
	while (p != nullptr) {
		i++;
		p = p->next;
	}
	return i;
}

void addFirst(int d, List& L) {
	Node* t = new Node;
	t->data = d;
	t->next = L.head;
	L.head = t;
}