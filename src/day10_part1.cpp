#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;

enum State {
	NONE,
	TARGET,
	BUTTON,
	JOLTAGE
};


void parse(const string &line, vector<bool> &target, vector<vector<int>> &buttons, vector<int> &joltage) {
	int p=-1;
	State state = NONE;
	string tmp = "";
	int b=-1;
	while((++p)<line.size()) {
		cout << line[p];
		if (line[p] == '[') {
			state = TARGET;
			continue;
		}
		if (line[p] == ']') {
			state = NONE;
			continue;
		}
		if (line[p] == ' ') {
			state = NONE;
			continue;
		}
		if (line[p] == '(') {
			buttons.push_back(vector<int>());
			b++;
			state = BUTTON;
			continue;
		}
		if (line[p] == ')') {
			buttons[b].push_back(stoi(tmp));
			tmp = "";
			state = NONE;
			continue;
		}
		if (line[p] == '{') {
			state = JOLTAGE;
			continue;
		}
		if (line[p] == '}') {
			joltage.push_back(stoi(tmp));
			tmp = "";
			state = NONE;
			continue;
		}
		if (state == TARGET) {
			if (line[p] == '.') target.push_back(false);
			else if (line[p] == '#') target.push_back(true);
			continue;
		}
		if (state == BUTTON) {
			if (line[p] == ',') {
				buttons[b].push_back(stoi(tmp));
				tmp = "";				
			}
			else {
				tmp += line[p];
			}
			continue;
		}
		if (state == JOLTAGE) {
			if (line[p] == ',') {
				joltage.push_back(stoi(tmp));
				tmp = "";				
			}
			else {
				tmp += line[p];
			}
			continue;
		}
	}
	cout << endl;
}


void apply(vector<bool> &lights, const vector<int> &button) {
	for (int i=0; i<button.size(); i++) lights[button[i]] = !lights[button[i]];
}


void show(const vector<bool> &lights) {
	for (int i=0; i<lights.size(); i++) {
		if (lights[i]) cout << "#";
		else cout << ".";
//		cout << (lights[i])?"#":".";
	}
//	cout << endl;
	cout << " ";
}

void show_button(const vector<int> &button) {
	for (int i=0; i<button.size(); i++) {
		 cout << button[i] << " ";
	}
//	cout << endl;
}


vector<vector<int>> get_all_combos(int buttons, int pushes) {
	vector<vector<int>> result;
	vector<int> current;
	for (int i = 0; i<pushes; i++) {
		current.push_back(i);
	}
	result.push_back(current);
	bool finished = false;
	while (!finished) {
		finished = true;
		for (int i = 0; i<pushes; i++) {
			if (current[pushes-i-1] < buttons-i-1)  {
				current[pushes-i-1]++;
				for (int j = 1; j<=i; j++)
					current[pushes-i-1+j] = current[pushes-i-1+(j-1)]+1;
				result.push_back(current);
				finished = false;
				break;
			}
		}
	}
	return result;
}


int main(int argc, char **argv) {  
	ScopeTimer t(argv[0]);
	ifstream file(get_filename(argc, argv));
	string str; 
	long num = 0;
	while (std::getline(file, str))
	{
		vector<vector<int>> buttons;
		vector<int> joltage;
		vector<bool> target;
		parse(str,target,buttons,joltage);
		bool found = false;
//		for (int i=0; i<buttons.size(); i++) {
//			vector<int> button = buttons[i];
			for (int j=0; j<=buttons.size(); j++) {
//				cout << "[" << buttons.size() << "," << j << "]" << endl;
				vector<vector<int>> schemes = get_all_combos(buttons.size(), j);
				for (int k=0; k<schemes.size(); k++) {
					vector<bool> lights;
					for (int l=0; l<target.size(); l++) lights.push_back(false);
					for (int l=0; l<schemes[k].size(); l++) {
						vector<int> button = buttons[schemes[k][l]];
						for (int m=0; m<button.size();m++)
							lights[button[m]] = !lights[button[m]];
					}
					bool equal = true;
					for (int l=0; l<target.size() && equal; l++) {
						if (target[l] != lights[l]) equal = false;
					}
					if (equal) {
						cout << "found: ";
						for (int l=0; l<schemes[k].size(); l++) {
							cout << schemes[k][l] << ",";
						}
						cout << endl;
						found = true;
						num += j;
						break;
					}
				}
				if (found) break;
			}
//			if (found) break;
//		}
	}
	cout << num << endl;
	return 0;
}
