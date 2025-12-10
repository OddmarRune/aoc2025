#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;


bool is_numeric(char c)
{
	return c>='0' && c<='9';
}


long eval(long a, long b, char c)
{
	if (c =='+') return a+b;
	if (c =='*') return a*b;
	return 0;
}


int main(int argc, char **argv) {  
	ScopeTimer t(argv[0]);
	ifstream file(get_filename(argc, argv));
	string str; 
	vector<vector<long>> all_numbers;
	vector<char> operators;
	while (std::getline(file, str))
	{
		vector<long> numbers;
		string tmp = "";
		for (int i = 0; i<str.size(); i++) {
			if (str[i] == ' ') {
				if (tmp != "") {
					numbers.push_back(stoi(tmp));
					tmp = "";
				}
			       	continue;
			}
			if (is_numeric(str[i])) {
				tmp += str[i];
			}
			else {
				operators.push_back(str[i]);
				continue;
			}
		}
		if (tmp != "") {
			numbers.push_back(stoi(tmp));
			tmp = "";
		}
		if (numbers.size()>0) 
			all_numbers.push_back(numbers);
	}
	cout << all_numbers.size() << " " << operators.size() << endl;
	cout << all_numbers[0].size() << " " << all_numbers[1].size() << " " << all_numbers[2].size() << endl;
	long sum = 0;
	for (int i=0; i<operators.size(); i++) {
		cout << all_numbers[0][i] << " ";
		long a = all_numbers[0][i];
		for (int j=1; j<all_numbers.size(); j++) {
			cout << operators[i] << " " << all_numbers[j][i] << " ";
			a = eval(a, all_numbers[j][i], operators[i]);
		}
		cout << "= " << a << endl;
		sum += a;
	}
	cout << sum << endl;
	return 0;
}
