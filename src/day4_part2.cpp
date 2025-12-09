#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;


int neighbours(vector<vector<char>> map, int r, int c) {
	int R = map.size();
	if (R==0) return 0;
	int C = map[0].size();
	if (C==0) return 0;
	int count = 0;
	if (r>0) {
		count += (map[r-1][c] == '@'?1:0);
		if (c>0) count += (map[r-1][c-1] == '@'?1:0);
		if (c<C-1) count += (map[r-1][c+1] == '@'?1:0);
	}
	{
		if (c>0) count += (map[r][c-1] == '@'?1:0);
		if (c<C-1) count += (map[r][c+1] == '@'?1:0);
	}
	if (r<R-1) {
		count += (map[r+1][c] == '@'?1:0);
		if (c>0) count += (map[r+1][c-1] == '@'?1:0);
		if (c<C-1) count += (map[r+1][c+1] == '@'?1:0);
	}
	return count;
}


int reduce(vector<vector<char>> &map) {
  int R = map.size();
  if (R==0) return 0;
  int C = map[0].size();
  if (C==0) return 0;

  vector<pair<int,int>> remove_list;

  for (int r=0; r<R; r++) {
	  for (int c=0; c<C; c++) {
		if (map[r][c] == '@' && neighbours(map, r, c) < 4) {
			remove_list.push_back({r,c});
		}
	  }
  }  
  for (auto rc : remove_list) {
    map[rc.first][rc.second] = '.';
  }
  return remove_list.size();
}


int main(int argc, char **argv) {  
  ifstream file(get_filename(argc, argv));
  string str; 
  vector<vector<char>> map;
  vector<string> outmap;
  int row = -1;
  while (std::getline(file, str))
  {
    if (str.size()==0) continue;
    map.push_back(vector<char>());
    row++;
    for (int i = 0; i<str.size(); i++) {
      map[row].push_back(str[i]);
    }
  }
  int count = 0;
  int rolls = -1;
  while (rolls != 0) {
	rolls = reduce(map);
	count += rolls;
  }

  int R = map.size();
  if (R==0) return 0;
  int C = map[0].size();
  if (C==0) return 0;
  for (int r=0; r<R; r++) {
	  outmap.push_back("");
	  for (int c=0; c<C; c++) {
		outmap[r] += map[r][c];
	  }
	  cout << outmap[r] << endl;
  }
  cout << count << endl;
  return 0;
}
