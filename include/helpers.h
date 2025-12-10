#pragma once
#include <string>
#include <cstring>
#include <chrono>
#include <iostream>

using namespace std;

class ScopeTimer {
public:
    explicit ScopeTimer(string name = "")
        : name_(move(name)),
          start_(chrono::high_resolution_clock::now()) {}

    ~ScopeTimer() {
        auto end = chrono::high_resolution_clock::now();
        auto us = chrono::duration_cast<chrono::microseconds>(end - start_).count();

        cout << (name_.empty() ? "" : name_ + ": ")
                  << us / 1000.0 << " ms\n";
  	cout << endl;
    }

private:
    string name_;
    chrono::high_resolution_clock::time_point start_;
};


string get_filename(int argc, char **argv) {
  string filename = "input/";	
  int day = 0;
  int part = 0;
  int state = 0;
  bool started = false;
  for (int i = 0; i<strlen(argv[0]) ; i++) {
    if (argv[0][i]>='0' && argv[0][i]<='9') {
      started = true;
      if (state == 0)
	      day = day*10 + (argv[0][i]-'0');
      if (state == 1)
	      part = part*10 + (argv[0][i]-'0');
    }
    else if (started) {
      state = state+1;
      started = false;
    }
    if (state>=2) break;
  }
  if (argc>1 && strcmp(argv[1],"test") == 0) {
    filename = filename + "test"+(day<10?"0":"")+to_string(day)+".txt";
  }
  else {
    filename = filename + "input"+(day<10?"0":"")+to_string(day)+".txt";
  }

  string line = "day: " + to_string(day) + ", part: " + to_string(part) + ", input: " + filename ;
  cout << line << endl;
  for (int i = 0; i<size(line); i++) cout << "=";
  cout << endl;

  return filename;
}
