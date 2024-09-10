#include <iostream>

void TrimRight(char*& s)
{
	//������, ���� �������� ������ ������
	if (s == nullptr) return;

	//������, ������ �������. �� ���������, �� �������� �� ��������������� ������ �������� ��� ������ ������
	int frontIndex = 0;
	//������, ������ ������. ���� �������� ������ ��������� �� ������, ������ ������ ����� ��������� 
	//�� ��������� �������, ������� ����� ������ ��������.
	int backIndex = 0;
	while (s[frontIndex] != '\0') {
		if (s[frontIndex] != ' ')			//���� ����� ����� �������� ��� �������� ������� ������(�� ������ � �� ����� ������), ��
			backIndex = frontIndex;			//������ ������ ������������� � ��������, ����� ������ ����� ����� ����� ��������
		++frontIndex;
	}
	if (s[backIndex] == ' ')				//���� ��� �������� ���� ������ ���������, ��� ��� ��������� ������� �� ��������,
		s[backIndex] = '\0';					//�� ������ ������� ���������� ������ ������(������ ���������� ������)

	if (backIndex != frontIndex - 1)//���� �������� ������, ����������� �� ����� ������, ����� �� 1 ������ �������, ��
		s[backIndex + 1] = '\0';			//��������� ������� ������(����� '\0') �� �������� �������� � ��������� ������ �� �����
}


int SqueezeSpaces(char* s)
{
	char* startp, * endp;

	if (s == NULL)
		return EOF;
	for (startp = s; *startp == ' '; startp++)
		;
	if (startp - s > 0) {
		endp = startp;
		startp = s;
		while (*startp++ = *endp++)
			;
	}
	endp = s + strlen(s);
	while (*--endp == ' ')
		*endp = '\0';
	return 1;
}

void smallArray(char* array) {
	char* newArray = new char[3]{ '1','2','3' };
	array = newArray;
}


int main()
{
	int stackArray[5] = { 0, 1, 2, 3, 4 };
	int* heapArray = new int[5];
	heapArray[0] = 0; heapArray[1] = 1; heapArray[2] = 2; heapArray[3] = 3; heapArray[4] = 4;

	std::cout << "sizeof(stackArray) = " << sizeof(stackArray) << std::endl;
	std::cout << "&stackArray = " << &stackArray << std::endl;
	std::cout << "stackArray = " << stackArray << std::endl;
	std::cout << "&stackArray[0] = " << &stackArray[0] << std::endl;
	std::cout << "&stackArray[0] = " << &stackArray[1] << std::endl;
	std::cout << "&stackArray[0] = " << &stackArray[2] << std::endl;
	std::cout << "&stackArray[0] = " << &stackArray[3] << std::endl;
	std::cout << "&stackArray[4] = " << &stackArray[4] << std::endl;

	std::cout << "sizeof(*heapArray) = " << sizeof(*heapArray) << std::endl;
	std::cout << "&heapArray = " << &heapArray << std::endl;
	std::cout << "heapArray = " << heapArray << std::endl;
	std::cout << "&heapArray[0] = " << &heapArray[0] << std::endl;
	std::cout << "&heapArray[0] = " << &heapArray[1] << std::endl;
	std::cout << "&heapArray[0] = " << &heapArray[2] << std::endl;
	std::cout << "&heapArray[0] = " << &heapArray[3] << std::endl;
	std::cout << "&heapArray[4] = " << &heapArray[4] << std::endl;

	return 0;

	//std::string string = "First row \nSecond row \nThird row            ";
	std::string string = " d        ";
	char* s = new char[string.length()];
	std::cout << "string.length() = " << string.length() << std::endl;
	int i = 0;
	for (i = 0; string[i] != '\0'; ++i)
		s[i] = string[i];
	s[i] = string[i];

	for (i = 0; s[i] != '\0'; ++i)
		std::cout << s[i];
	std::cout << "i = " << i << std::endl;

	SqueezeSpaces(s);
	for (i = 0; s[i] != '\0'; ++i)
		std::cout << s[i];
	std::cout << "i = " << i << std::endl;
	return 0;
}