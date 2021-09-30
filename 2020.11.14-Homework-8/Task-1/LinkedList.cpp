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
	return ((index >= 0) && (index < count));
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
		return true;
	}
	else if (index == count - 1)
	{
		tail->data = element;
		return true;
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
	extract(index);
	//if (index == 0)
	//{
	//	Node* node = head;
	//	head = head->next;
	//	delete node;
	//	return;
	//}
	//if (indexValid(index))
	//{
	//	Node* temp = head;
	//	for (int i = 0; i < index - 1; ++i)
	//	{
	//		temp = temp->next;
	//	}
	//	Node* node = temp;
	//	temp = temp->next;
	//	delete node;
	//}
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
	for (int i = 0; i < count; ++i)  // 0 1 2 3, i=3, a[i]=2
	{
		if (temp->data == element)
		{
			c = i;
			break;
		}
		temp = temp->next;
	}
	if ((c < 0) && (count > 1))
	{
		c = (tail->data == element ? count - 1 : c);
	}
	return c;
}

bool LinkedList::contains(int element)
{
	//Node* temp = head;
	//int c = 0;
	//for (int i = 0; i < count - 1; ++i)
	//{
	//	if (head->data == element)
	//	{
	//		c = 1;
	//		break;
	//	}
	//	temp = temp->next;
	//}
	//return c;
	return (indexOf(element) < 0 ? false : true);
}

//bool LinkedList::swap(int index1, int index2)
//{
//	if ((!indexValid(index1)) or (!indexValid(index2)))
//	{
//		return false;
//	}
//	else if (index1 == index2)
//	{
//		return true;
//	}
//	else
//	{
//		Node* temp1 = head;
//		Node* temp2 = head;
//		for (int i = 0; i < index1 - 1; ++i)
//		{
//			temp1 = temp1->next;
//		}
//		for (int i = 0; i < index2 - 1; ++i)
//		{
//			temp2 = temp2->next;
//		}
//		//Node* temp3 = temp1;
//		//Node* temp4 = temp1->next;
//		//temp1 = temp2;
//		//temp1->next = temp2->next;
//		//temp2 = temp3;
//		//temp2->next = temp4;
//		Node* temp11 = temp1->next;
//		Node* temp111 = temp1->next->next;
//		Node* temp22 = temp2->next;
//		Node* temp222 = temp2->next->next;
//		temp1->next = temp22;
//		temp1->next->next = temp222;
//		temp2->next = temp11;
//		temp2->next->next = temp111;
//		return true;
//	}
//}

int LinkedList::extract(int index)
{

	if (!indexValid(index))
	{
		return -999999;
	}
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
		int c = temp->next->data;
		Node* node = temp->next;
		temp->next = temp->next->next;
		delete node;
		--count;
		return c;
	}
}

int LinkedList::extractTail()
{
	int c = 0;
	if (count == 0)
	{
		return 0;
	}
	else if (count == 1)
	{
		c = tail->data;
		head = tail = nullptr;
		count--;
		return c;
	}
	else
	{
		Node* temp = head->next;
		c = tail->data;
		for (int i = 1; i < count - 2; ++i)
		{
			temp = temp->next;
		}
		temp->next = nullptr;
		--count;
		return c;
	}
}

int LinkedList::extractHead()
{
	int c = 0;
	if (count == 0)
	{
		return 0;
	}
	else if (count == 1)
	{
		c = head->data;
		head = tail = nullptr;
		count--;
		return c;
	}
	else
	{
		c = head->data;
		Node* node = head;
		head = head->next;
		delete node;
		--count;
		return c;
	}
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
	if (index1 == 0)
	{
		if (index2 == 1)
		{
			Node* node1 = head;
			Node* node2 = head->next->next;
			head = head->next;
			head->next = node1;
			head->next->next = node2;
			delete node1;
			delete node2;
			return true;
		}
		else if (index2 == count - 1)
		{
			Node* node1 = head->next;
			Node* node2 = tail;
			tail = head;
			tail->next = nullptr;
			head = node2;
			head->next = node1;
			delete node1;
			delete node2;
			return true;
		}
		else
		{
			Node* temp = head;
			for (int i = 0; i < index2 - 1; ++i)
			{
				temp = temp->next;
			}
			Node* node2 = head->next;
			Node* node3 = temp->next;
			Node* node1 = temp->next->next;
			temp->next = head;
			temp->next->next = node1;
			head = node3;
			head->next = node2;
			delete node1;
			delete node2;
			delete node3;
			return true;
		}
	}
	else
	{
		if (index2 == count - 1)
		{
			Node* temp1 = head;
			for (int i = 0; i < index1; ++i)
			{
				temp1 = temp1->next;
			}
			Node* node1 = tail;
			Node* node2 = temp1->next->next;
			tail = temp1->next;
			tail->next = nullptr;
			temp1->next = node1;
			temp1->next->next = node2;
			delete node1;
			delete node2;
			return true;
		}
		else
		{
			Node* temp1 = head;
			for (int i = 0; i < index1 - 1; ++i)
			{
				temp1 = temp1->next;
			}
			Node* temp2 = head;
			for (int i = 0; i < index2 - 1; ++i)
			{
				temp2 = temp2->next;
			}
			Node* node1 = temp1->next;
			Node* node2 = temp1->next->next;
			temp1->next = temp2->next;
			temp1->next->next = temp2->next->next;
			temp2->next = node1;
			temp2->next->next = node2;
			delete node1;
			delete node2;
			return true;
		}
	}
}





bool LinkedList::last(Node* last)
{
	last = tail;
}


bool LinkedList::prelast(Node* prelast)
{
	Node* node1 = head;
	if (count == 0 or count == 1)
	{
		prelast = nullptr;
	}
	else if (count == 2)
	{
		prelast = head;
	}
	else
	{
		prelast = head;
		node1->next->next;
		while (node1 != tail)
		{
			prelast->next;
			node1->next;
		}
		prelast->next;
	}
}


bool LinkedList::get_ptr(int n, Node* node)
{
	if (n < 0 or n > count or (n == 0 and count != 0))
	{
		return false;
	}
	else if (n == 0 and count == 0)
	{
		node = nullptr;
	}
	else
	{
		node = head;
		for (int i = 1; i < n; i++)
		{
			node->next;
		}
	}
}