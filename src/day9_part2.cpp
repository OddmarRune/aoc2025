#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include "helpers.h"

using namespace std;


long area(const pair<long,long> &a, const pair<long,long> &b) {
	return (abs(b.second-a.second)+1)*(abs(b.first-a.first)+1);
}

void draw(vector<vector<char>> &world, const pair<long,long> &a, const pair<long,long> &b) {
	world[a.first][a.second] = '#';
	world[b.first][b.second] = '#';
	if (a.first == b.first) {
		for (long l = min(a.second,b.second)+1; l<max(a.second,b.second); l++) {
			if (world[a.first][l] == '.') world[a.first][l] = '-';
		}
	}
	else if (a.second == b.second) {
		for (long l = min(a.first,b.first)+1; l<max(a.first,b.first); l++) {
			if (world[l][a.second] == '.') world[l][a.second] = '|';
			else cout << "possible crossing" << endl;
			
		}
	}
	else {
		cerr << "This should not happen" << endl;
	}
}


void show(const vector<vector<char>> &world) {
	for (int i=0; i<world.size(); i++) {
		for (int l=0; l<world[i].size(); l++) {
			cout << world[i][l];				
		}
		cout << endl;
	}
}

void flod_fill(vector<vector<char>> &world) {
	for (int j=0; j<2; j++) {
	for (int i=0; i<world.size(); i++) {
		bool inside = false;
		bool unknown = false;
		for (int l=0; l<world[i].size(); l++) {
			if (!unknown && !inside && world[i][l] == '.') {
				world[i][l] = ' ';
				continue;
			}
			if (!unknown && !inside && world[i][l] == '|') {
				inside = true;
				continue;
			}
			if (!unknown && inside && world[i][l] == '.') {
				world[i][l] = 'x';
				continue;
			}
			if (!unknown && inside && world[i][l] == '|') {
				inside = false;
				continue;
			}
			if (world[i][l] == '#') {
				unknown = true;
				continue;
			}
			if (world[i][l] == 'x') {
				unknown = false;
				inside = true;
			}
			if (world[i][l] == ' ') {
				unknown = false;
				inside = false;
			}
		}
	}	
	for (int l=0; l<world[0].size(); l++) {
		bool inside = false;
		bool unknown = false;
		for (int i=0; i<world.size(); i++) {
			if (!unknown && !inside && world[i][l] == '.') {
				world[i][l] = ' ';
				continue;
			}
			if (!unknown && !inside && world[i][l] == '-') {
				inside = true;
				continue;
			}
			if (!unknown && inside && world[i][l] == '.') {
				world[i][l] = 'x';
				continue;
			}
			if (!unknown && inside && world[i][l] == '-') {
				inside = false;
				continue;
			}
			if (world[i][l] == '#') {
				unknown = true;
				continue;
			}
			if (world[i][l] == 'x') {
				unknown = false;
				inside = true;
			}
			if (world[i][l] == ' ') {
				unknown = false;
				inside = false;
			}
		}
	}
	}
}

long check(const vector<vector<char>> &world) {
	long sum = 0;
	for (int i=0; i<world.size(); i++) {
		for (int l=0; l<world[i].size(); l++) {
			if (world[i][l] == '.') sum++;
		}
	}
	return sum;
}


bool check_area(const vector<vector<char>> &world, const pair<long,long> &a, const pair<long,long> &b) {
	long sum = 0;
	long start1 = min(a.first,b.first);
	long start2 = min(a.second,b.second);
	long stop1 = max(a.first,b.first);
	long stop2 = max(a.second,b.second);
	for (int i=start1; i<=stop1; i++) if (world[i][start2] == ' ') return false;
	for (int l=start2+1; l<=stop2; l++) if (world[start1][l] == ' ') return false;
	for (int i=start1; i<stop1; i++) if (world[i][stop2] == ' ') return false;
	for (int l=start2+1; l<stop2; l++) if (world[stop1][l] == ' ') return false;
	return true;
}



int main(int argc, char **argv) {  
	ifstream file(get_filename(argc, argv));
	string str; 
	vector<pair<long,long>> list;
	while (std::getline(file, str))
	{				
		int p = str.find(',');
		//if (p>=0) list.push_back({stol(str.substr(0,p)),stol(str.substr(p+1))});
		if (p>=0) list.push_back({stol(str.substr(p+1)),stol(str.substr(0,p))});
	}
	long min1 = -1, min2 = -1, max1 = -1, max2 = -1;
	for (int i=0; i<list.size(); i++) {
		if (list[i].first<min1 || min1<0) min1 = list[i].first;
		if (list[i].second<min2 || min2<0) min2 = list[i].second;
		if (list[i].first>max1) max1 = list[i].first;
		if (list[i].second>max2) max2 = list[i].second;
	}
	vector<vector<char>> world(max1+1, vector<char>(max2+1));
	for (int i=0;i<max1+1;i++) {
		for(int l=0;l<max2+1;l++) {
			world[i][l]='.';
		}
	}
	for (int l=0; l<list.size(); l++) {
		draw(world, list[l], list[(l+1)%list.size()]);
	}
	flod_fill(world);
	if (max2 < 100) show(world);
	long max_area = 0;
	pair<int,int> max_pair{-1,-1};
	for (int i = 0; i<list.size(); i++) {
		for (int l = i+1; l<list.size(); l++) {
			long A = area(list[i], list[l]);
			if (A <= max_area) continue;
			if (check_area(world, list[i], list[l])) {
				max_area = A;
				max_pair = {i,l};
			}
		}
	}
	cout << " Area = " << max_area << endl;
	cout << list[max_pair.first].second << ',' << list[max_pair.first].first << " - " 
	     << list[max_pair.second].second << ',' << list[max_pair.second].first << endl;
	return 0;
}
