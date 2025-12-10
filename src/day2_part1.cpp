#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;


long count(long start, long stop) {
  long sum=0;
  for (long i=start; i<=stop; i++) {
    string number = to_string(i);
    long n = size(number);
    if (n%2==0) {
      if (number.substr(0,n/2) == number.substr(n/2,-1)) {
        sum += i;
      }
    }
  }
  return sum;
}




int main(int argc, char **argv) {  
  ScopeTimer t(argv[0]);
  ifstream file(get_filename(argc, argv));
  string str; 
  long sum=0;
  while (std::getline(file, str))
  {
    int prev=0;
    int next=0;
    int mid=0;
    while (next>=0) {
      next = str.find(',',prev+1);      
      string subst = str.substr(prev,next-prev);
      mid = subst.find('-');
      long start = stol(subst.substr(0,mid));
      long stop = stol(subst.substr(mid+1,-1));
      long current = count(start,stop);
      sum += current;
      prev = next+1;
    }
  }
  cout << sum << endl;
  return 0;
}
