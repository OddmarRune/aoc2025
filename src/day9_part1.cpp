#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include "helpers.h"

using namespace std;


long area(const pair<long,long> &a, const pair<long,long> &b) {
	return (abs(b.second-a.second)+1)*(abs(b.first-a.first)+1);
}


int main(int argc, char **argv) {  
	ScopeTimer t(argv[0]);
	ifstream file(get_filename(argc, argv));
	string str; 
	vector<pair<long,long>> list;
	while (std::getline(file, str))
	{				
		int p = str.find(',');
		if (p>=0) list.push_back({stol(str.substr(0,p)),stol(str.substr(p+1))});
	}
	long max_area = 0;
	pair<int,int> max_pair{-1,-1};
	for (int i = 0; i<list.size(); i++) {
		for (int l = i+1; l<list.size(); l++) {
			long A = area(list[i],list[l]);
			if (A > max_area) {
				max_area = A;
				max_pair = {i,l};
			}
		}
	}
	cout << " Area = " << max_area << endl;
	cout << list[max_pair.first].first << ',' << list[max_pair.first].second << " - " 
	     << list[max_pair.second].first << ',' << list[max_pair.second].second << endl;
	return 0;
}
