#include <iostream>

void TrimRight(char*& s)
{
	//Случай, если передана пустая строка
	if (s == nullptr) return;

	//Индекс, идущий впереди. Он проверяет, не является ли рассматриваемый символ пробелом или концом строки
	int frontIndex = 0;
	//Индекс, идущий позади. Если передний индекс указывает на пробел, задний индекс будет указывать 
	//на последний элемент, стоящий перед серией пробелов.
	int backIndex = 0;
	while (s[frontIndex] != '\0') {
		if (s[frontIndex] != ' ')			//Если после серии пробелов был встречен обычный символ(не пробел и не конец строки), то
			backIndex = frontIndex;			//задний индекс выравнивается с передним, чтобы начать поиск новой серии пробелов
		++frontIndex;
	}
	if (s[backIndex] == ' ')				//Если при проверки всей строки оказалось, что она полностью состоит из пробелов,
		s[backIndex] = '\0';					//ее первый элемент заменяется концом строки(строка становится пустой)

	if (backIndex != frontIndex - 1)//Если передний индекс, указывающий на конец строки, всего на 1 больше заднего, то
		s[backIndex + 1] = '\0';			//последний элемент строки(кроме '\0') не является пробелом и обрезание строки не нужно
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