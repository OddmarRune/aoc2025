#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;

vector<long> factors(long number) {
  vector<long> fact;
  for (long f=1; f < number; f++) {
    if (number%f==0) {
      fact.push_back(f);
    }
  }
  return fact;
}

long count(long start, long stop) {
  long sum=0;
  for (long i=start; i<=stop; i++) {
    string number = to_string(i);
    long n = size(number);
    vector<long> f = factors(n);
    for (int j=0; j<f.size(); j++) {
      bool eq = true;
      for (int k=0; k<(size(number)/f[j]-1); k++)
        eq &= (number.substr(k*f[j],f[j]) == number.substr((k+1)*f[j],f[j]));
      if (eq) {
        sum += i;
        break;
      }
    }
  }
  return sum;
}

int main(int argc, char **argv) {  
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
