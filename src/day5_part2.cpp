#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;



int main(int argc, char **argv) {  
	ifstream file(get_filename(argc, argv));
	string str; 
	vector<pair<long,long>> rules;
	while (std::getline(file, str))
	{
		if (str.size()==0) {
			break;
		}
		int p = str.find("-");
		long from = stol(str.substr(0,p));
		long to = stol(str.substr(p+1));
		if (from>to) {
			cout << "wrong order" << from << " - " << to << endl;
		}
		for (const auto &rule: rules) {
			if (from >= rule.first && from <= rule.second) {
				from = rule.second+1;
			}
			if (to >= rule.first && to <= rule.second) {
				to = rule.first-1;
			}
		}
		if (from>to) {
			cout << "dropped a rule (" << str << ") " << from << " - " << to << endl;
			continue;
		}		
		
		for (int i = rules.size()-1; i>=0; i--) {
			long from_ = rules[i].first;
			long to_ = rules[i].second;
			if (from <= from_ && from_ <= to ) {
				from_ = to+1;
			}
			if (from <= to_ && to_ <= to) {
				to_ = from_-1;
			}
			if (from_>to_) {
				rules.erase(rules.begin()+i);
			}
			else if (from_ != rules[i].first || to_ != rules[i].second) {
				rules[i] = {from_, to_};
			}
		}
		rules.push_back({from, to});
	}
	long num = 0;
	for (const auto &rule : rules) {
		cout << " [ " << rule.first << " - " << rule.second << " ] " << rule.second - rule.first + 1 << endl;
		num += (rule.second-rule.first+1);
	}
	cout << num << endl;
	return 0;
}
