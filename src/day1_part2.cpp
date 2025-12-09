#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "helpers.h"

using namespace std;

#define N 100

int main(int argc, char **argv) {  
  ifstream file(get_filename(argc, argv));
  string str; 
  int pos = 50;
  int num = 0;
  while (std::getline(file, str))
  {
    char D = str[0];
    int n = stoi(str.substr(1));
    if (D=='L') pos = (N-pos)%N;
    num += (pos + n) / N;
    pos = (pos + n) % N;      
    if (D=='L') pos = (N-pos)%N;
  }
  cout << num << endl;
  return 0;
}
