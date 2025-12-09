#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;




int main(int argc, char **argv) {  
	ifstream file(get_filename(argc, argv));
	string str; 
	int split_number = 0;
	vector<bool> beams;
	while (std::getline(file, str))
	{		
		for (int i=0; i<str.size(); i++) {
			if (i >= beams.size()) beams.push_back(false);
			if (str[i] == '.') continue;
			if (str[i] == 'S') beams[i] = true;
			if (str[i] == '^' and beams[i]) {
				split_number ++;
				if (i>0) beams[i-1] = true;
				beams[i] = false;
				if (i < beams.size()-1) beams[i+1] = true;
			}
		}
	}
	cout << split_number << endl;
	return 0;
}
