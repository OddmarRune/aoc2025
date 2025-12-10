#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;

int main(int argc, char **argv) {  
	ScopeTimer t(argv[0]);
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
		rules.push_back({from, to});
	}
	long num = 0;
	cout << endl;
	while (std::getline(file, str)) {
		if (str.size()==0) continue;
		long ingredient = stol(str);
		bool found = false;
		for (const auto &rule : rules) {
			if (ingredient >= rule.first && ingredient <= rule.second) {
				cout << "  - Ingredient ID " << ingredient << " is fresh because it falls into range " 
				     << rule.first << "-" << rule.second << endl;
				found = true;
				num++;
				break;
			}
		}
		if (!found) {
			cout << "  - Ingredient " << ingredient << " is spoiled" << endl;
		}
	}
	cout << endl;
	cout << num << " of the available ingredient IDs are fresh." <<  endl;
	cout << endl;
	return 0;
}
