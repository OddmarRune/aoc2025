#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;





int main(int argc, char **argv) {  
  ifstream file(get_filename(argc, argv));
  string str; 
  long sum=0;
  while (std::getline(file, str))
  {
    if (str.size()==0) continue;
    int a = -1;
    int pa = 0;
    int b = -1;
    int pb = 1;
    for (int i = 0; i < (str.size()-1); i++) {
	    int x = stoi(str.substr(i,1));
	    if (x>a) {
		    a = x;
		    pa = i;
	    }
    }
    
    for (int i = pa+1; i<str.size(); i++) {
	    int x = stoi(str.substr(i,1));
	    if (x>b) {
		    b = x;
		    pb = i;
	    }
    }
    cout << a << b << " " << pa << "," << pb << endl;
    sum += a*10+b;
  }
  cout << sum << endl;
  return 0;
}
