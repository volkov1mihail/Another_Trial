#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <clocale>

using namespace std;

ostream& print(ostream& out, const string& format,
	const vector<string>& args)
{
	regex re("[^%]+|%%|%\\d+");
	for (sregex_token_iterator i{ format.begin(), format.end(), re, 0 }, end; i != end; ++i)
	{
		string token{ *i };
		if (token == "%%") // escaped %
		{
			out << '%';
		}
		else if (token[0] == '%') // positional parameter
		{
			unsigned long index = stoul(token.substr(1));
			out << args.at(index - 1);
		}
		else // print as is
		{
			out << token;
		}
	}
	return out;
}


vector<string> split(const string& s, char sep)
{
	vector<string> args;
	istringstream ss{ s };
	for (string arg; getline(ss, arg, sep); )
		args.push_back(arg);
	return args;
}


int main()
{
	//setlocale(LC_ALL, "Russian");
	//char array[] = "Антон|15|Архангельске";
	//print(cout, "Привет, меня зовут %1, мне %2 лет. Я живу в %3", split(array, '|')) << endl;
	double d = 0;
	cin >> d;
	cout << "d=" << d << endl;
}

//с = 308; d= 12345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678911234567891123456789112345678
//c = 324; d=0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000009