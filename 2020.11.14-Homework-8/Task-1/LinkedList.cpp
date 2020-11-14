#include "LinkedList.h"

LinkedList::LinkedList(const LinkedList& list)
{
	tail = head = nullptr;
	count = 0;
	Node* temp = list.head;
	while (temp != nullptr)
	{
		addToTail(temp->data);
		temp = temp->next;
	}
}

LinkedList::~LinkedList()
{
	Node* temp = head;
	while (temp != nullptr)
	{
		Node* node = temp;
		temp = temp->next;
		delete node;
	}
}

bool LinkedList::indexValid(int index)
{
	return (index > 0 && index < count);
}

int LinkedList::length()
{
	return count;
}

bool LinkedList::addToHead(int element)
{
	if (head == nullptr)
	{
		head = tail = new Node(element);
	}
	else
	{
		head = new Node(element, head);
	}
	++count;
	return true;
}

bool LinkedList::addToTail(int element)
{
	if (tail == nullptr)
	{
		head = tail = new Node(element);
	}
	else
	{
		tail->next = new Node(element);
		tail = tail->next;
	}
	++count;
	return true;
}

bool LinkedList::add(int index, int element)
{
	if (index == 0)
	{
		return addToHead(element);
	}
	if (index == count)
	{
		return addToTail(element);
	}
	if (!indexValid(index))
	{
		return false;
	}
	Node* temp = head;
	for (int i = 0; i < index - 1; ++i)
	{
		temp = temp->next;
	}
	temp->next = new Node(element, temp->next);
	++count;
	return true;
}

int LinkedList::get(int index)
{
	if (!indexValid(index))
	{
		return -1;
	}
	if (index == 0)
	{
		return head->data;
	}
	if (index == count - 1)
	{
		return tail->data;
	}
	Node* temp = head;
	for (int i = 0; i < index; ++i)
	{
		temp = temp->next;
	}
	return temp->data;

}

bool LinkedList::set(int index, int element)
{
	if (!indexValid(index))
	{
		return false;
	}
	if (index == 0)
	{
		head->data = element;
	}
	else if (index == count - 1)
	{
		tail->data = element;
	}
	else
	{
		Node* temp = head;
		for (int i = 0; i < index; ++i)
		{
			temp = temp->next;
		}
		temp->data = element;
	}
	return true;
}

int& LinkedList::operator[](int index)
{
	if (head == nullptr)
	{
		addToHead(0);
		return head->data;
	}
	if (index <= 0)
	{
		return head->data;
	}
	if (index >= count)
	{
		addToTail(0);
		return tail->data;
	}
	if (index == count - 1)
	{
		return tail->data;
	}
	Node* temp = head;
	for (int i = 0; i < index; ++i)
	{
		temp = temp->next;
	}
	return temp->data;
}

std::ostream& operator<<(std::ostream& stream, const LinkedList list)
{
	stream << "[" << list.count << "]{";
	if (list.head == nullptr)
	{
		stream << "EMPTY";
	}
	else
	{
		Node* temp = list.head;
		while (temp != nullptr)
		{
			stream << temp->data;
			if (temp->next != nullptr)
			{
				stream << ", ";
			}
			temp = temp->next;
		}
	}
	stream << "}";

	return stream;
}

void LinkedList::operator+=(int element)
{
	addToTail(element);
}

void LinkedList::operator-=(int index)
{
	if (index == 0)
	{
		Node* node = head;
		head = head->next;
		delete node;
	}
	if (indexValid(index))
	{
		Node* temp = head;
		for (int i = 0; i < index - 1; ++i)
		{
			temp = temp->next;
		}
		Node* node = temp;
		temp = temp->next;
		delete node;
	}
}

LinkedList& LinkedList::operator= (const LinkedList& list)
{
	if (&list != this)
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			Node* node = temp;
			temp = temp->next;
			delete node;
		}
		count = 0;
		temp = list.head;
		while (temp != nullptr)
		{
			addToTail(temp->data);
			temp = temp->next;
		}
	}
	return *this;
}

int LinkedList::indexOf(int element)
{
	Node* temp = head;
	int c = -1;
	for (int i = 0; i < count - 1; ++i)
	{
		if (head->data == element)
		{
			c = i;
			break;
		}
		temp = temp->next;
	}
	return c;
}

bool LinkedList::contains(int element)
{
	Node* temp = head;
	int c = 0;
	for (int i = 0; i < count - 1; ++i)
	{
		if (head->data == element)
		{
			c = 1;
			break;
		}
		temp = temp->next;
	}
	return c;
}

bool LinkedList::swap(int index1, int index2)
{
	if ((!indexValid(index1)) or (!indexValid(index2)))
	{
		return false;
	}
	else if (index1 == index2)
	{
		return true;
	}
	else
	{
		Node* temp1 = head;
		Node* temp2 = head;
		for (int i = 0; i < index1 - 1; ++i)
		{
			temp1 = temp1->next;
		}
		for (int i = 0; i < index2 - 1; ++i)
		{
			temp2 = temp2->next;
		}
		Node* temp3 = temp1;
		temp1 = temp2;
		temp2 = temp1;
		return true;
	}
}

int LinkedList::extract(int index)
{
	if (index == 0)
	{
		extractHead();
	}
	else if (index == count - 1)
	{
		extractTail();
	}
	else
	{
		Node* temp = head;
		for (int i = 0; i < index - 1; ++i)
		{
			temp = temp->next;
		}
		return temp->data;
		Node* node = temp;
		temp = temp->next;
		delete node;
		--count;
	}
}

int LinkedList::extractTail()
{
	if (count == 0)
	{
		return 0;
	}
	else if (count == 1)
	{
		head = tail = nullptr;
		return 0;
		count--;
	}
	else
	{
		Node* temp = head->next;
		for (int i = 1; i < count - 2; ++i)
		{
			temp = temp->next;
		}
		temp->next = nullptr;
		return tail->data;
		--count;
	}
}

int LinkedList::extractHead()
{
	if (count == 0)
	{
		return 0;
	}
	else if (count == 1)
	{
		head = tail = nullptr;
		return 0;
		count--;
	}
	else
	{
		Node* node = head;
		head = head->next;
		delete node;
		return head->data;
		--count;
	}
}