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
  long sum=0;
  while (std::getline(file, str))
  {
    if (str.size()==0) continue;
    long current = 0;    
    int pos = -1;
    for (int digit = 0; digit<12; digit++) {
        int current_max = -1;
	int current_pos = -1;
	for (int p = pos+1; p<(str.size()-(11-digit)); p++) {
		int x = stoi(str.substr(p,1));
		if (x>current_max) {
			current_max = x;
			current_pos = p;
		}
	}
	pos = current_pos;
	current = current*10 + current_max;
//	cout << current << " (" << current_pos << ") ";
    }
//    cout << current << endl;
    sum += current;
  }
  cout << sum << endl;
  return 0;
}
