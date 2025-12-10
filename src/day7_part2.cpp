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
	vector<long> beam;
	while (std::getline(file, str))
	{		
		vector<long> beam_tmp;
		for (int i=0; i<str.size(); i++) {
			if (i >= beam_tmp.size()) beam_tmp.push_back(0);
			if (i >= beam.size()) beam.push_back(0);
		}
		for (int i=0; i<str.size(); i++) {
//			cout << str[i];
			if (str[i] == '.') {
				beam_tmp[i] += beam[i];
			}
			if (str[i] == 'S') {
				beam_tmp[i] = 1;
			}
			if (str[i] == '^' and beam[i]>0) {
				if (i > 0) {
					beam_tmp[i-1] += beam[i];
				}
				if (i < beam.size()-1) {
					beam_tmp[i+1] += beam[i];
				}
//				beam_tmp[i] = 0;
			}
		}
		for (int i=0; i<beam_tmp.size(); i++) {
			beam[i] = beam_tmp[i];
			if (beam[i]>0 && str[i] != 'S') cout << '|';
			else cout << str[i];
		}
		cout << endl;
	}
	long sum = 0;
	for (int i = 0; i<beam.size(); i++) {
		sum += beam[i];
	}
	cout << sum << endl;
	return 0;
}
