#pragma once
#include <string>
#include <cstring>

using namespace std;

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
