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
	vector<string> numbers;
	vector<int> block_positions;
	vector<char> operators;
	while (std::getline(file, str))
	{		
		for (int i = 0; i<str.size(); i++) {
			if (str[i] == ' ') continue;
			if (is_numeric(str[i])) {
				numbers.push_back(str);
				break;
			}
			operators.push_back(str[i]);
			block_positions.push_back(i);
		}

	}
	long sum=0;
	for (int i=0; i<block_positions.size(); i++) {
		vector<string> block;
		for (int j=0; j<numbers.size(); j++) {
			if (j<block_positions.size()-1) {
				block.push_back(numbers[j].substr(block_positions[i], block_positions[i+1]-block_positions[i])); 
			}
			else 
			{
				block.push_back(numbers[j].substr(block_positions[i]));
			}

		}
		vector<long> block_numbers;
		for (int j=0; j<block[0].size(); j++) {
			string tmp="";
			for (int l=0; l<block.size(); l++) {
				if (block[l][j] != ' ')
					tmp += block[l][j];
			}
			if (tmp.size()>0)
				block_numbers.push_back(stol(tmp));
		}
		long a = block_numbers[0];	
		cout << a << " ";
		for (int j=1; j<block_numbers.size(); j++) {
			cout << operators[i] << " " << block_numbers[j] << " ";
			a = eval(a, block_numbers[j], operators[i]);
		}
		cout << "= " <<  a << endl;
		sum += a;
	}
	cout << "sume = " << sum << endl;
	return 0;
}
