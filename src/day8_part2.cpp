#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include "helpers.h"

using namespace std;


struct vec3 {
	double x, y, z;	
	vec3(int x_, int y_, int z_) {
		x = static_cast<double>(x_);
		y = static_cast<double>(y_);
		z = static_cast<double>(z_);
	}
};



double dist(const vec3 &a, const vec3 &b) {
	return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2)+pow(b.z-a.z,2));
}


bool is_connected(const vector<int> &c, int a) {
	for (auto b: c){
		if (a==b) return true;
	}
	return false;
}


int main(int argc, char **argv) {  
	ifstream file(get_filename(argc, argv));
	string str; 
	vector<vec3> V;
	while (std::getline(file, str))
	{				
		int a = str.find(',');
		if (a>0) {
			int b = str.find(',',a+1);
			V.push_back({stoi(str.substr(0,a)), stoi(str.substr(a+1,b-a-1)), stoi(str.substr(b+1))});

		}
	}
	priority_queue<pair<double, pair<int, int>>> pq;
	for (int i=0; i<V.size(); i++) {
		for (int j=i+1; j<V.size(); j++) {
			pq.push({1/dist(V[i],V[j]),{i,j}});
			
		}
	}
	vector<vector<int>> connections;
	for (int i=0; i<V.size(); i++) {
		connections.push_back({i});
	}
	for (int i=0; !pq.empty(); i++) {
		auto connect  = pq.top();
		pq.pop();
		bool check = connections.size() == 2;
		int a = connect.second.first;
		int a_conn = -1;
		for (int j=0; j<connections.size(); j++) {
			if (is_connected(connections[j], a)) {
				a_conn = j;
				break;
			}
		}
		int b = connect.second.second;
		int b_conn = -1;
		for (int j=0; j<connections.size(); j++) {
			if (is_connected(connections[j], b)) {
				b_conn = j;
				break;
			}
		}
		if (a_conn >= 0 && a_conn == b_conn) continue;
		if (a_conn >= 0 && b_conn == -1) {
			cout << "Should never happen 1" << endl;
			connections[a_conn].push_back(b);
			continue;
		}
		if (a_conn == -1 && b_conn >= 0) {
			cout << "Should never happen 2" << endl;
			connections[b_conn].push_back(a);
			continue;
		}
		if (a_conn >= 0 && b_conn >= 0 && a_conn != b_conn) {
			for (int j=0; j<connections[b_conn].size(); j++) {
				connections[a_conn].push_back(connections[b_conn][j]);
			}
			connections.erase(connections.begin()+b_conn);
			if (check) {
				cout << a << ":" << V[a].x << "," << V[a].y << "," << V[a].z << endl;
				cout << b << ":" << V[b].x << "," << V[b].y << "," << V[b].z << endl;
				cout << "result = " << static_cast<long>(V[a].x)*static_cast<long>(V[b].x) << endl;
				break;
			}
			continue;
		}
		cout << "This should never happen" << endl;
//		connections.push_back({a,b});
	}
/*
	int a = 1, b = 1, c = 1;
	for (int i=0; i<connections.size(); i++) {
		int x = connections[i].size();
		if (x>a) {
			c = b;
			b = a;
			a = x;
			continue;
		}
		if (x>b) {
			c = b;
			b = x;
			continue;
		}
		if (x>c) {
			c = x;
		}
	}
	cout << a << "," << b << "," << c << endl;

	cout << a * b * c << endl;
*/
	return 0;
}
