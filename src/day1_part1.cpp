#include <iostream>
#include <fstream>
#include <string>
#include "helpers.h"

using namespace std;

#define N 100

int main(int argc, char **argv) {  
  ScopeTimer t(argv[0]);
  ifstream file(get_filename(argc, argv));
  string str; 
  int pos = 50;
  int num[N];
  for (int i = 0; i<N; i++)
	  num[i] = 0;
  while (std::getline(file, str))
  {
    char D = str[0];
    int n = stoi(str.substr(1));
    if (D=='R')  pos = (pos + n) % N;
    else         pos = (pos + N - (n%N)) % N;
    num[pos] += 1;
  }
  cout << num[0] << endl;
  return 0;
}
