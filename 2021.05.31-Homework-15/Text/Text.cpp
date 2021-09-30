#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main()
{
	string str;
	ifstream fin("in.txt"); 
	getline(fin, str);
	fin.close();
	cout << str << endl;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'o' || str[i] == 'i' || str[i] == 'u')
		{
			str[i] = '*';
		}
	}
	ofstream fout("out.txt");
	fout << str << endl;
	fout.close();
	return 0;
}