#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int getpath(int right, int down) {
	ifstream input("input.txt");
	vector<string> map;

	int result = 0;

	if (input.is_open()) {
		string l;

		while (input >> l) {
			map.emplace_back(l);
		}

		int rightcounter = 0;
		for (int i = 0; i < map.size(); i += down) {
			if (map[i][rightcounter % map[i].size()] == '#') {
				result++;
			}
			rightcounter += right;
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << getpath(1,1)* getpath(3, 1)* getpath(5, 1)* getpath(7, 1)* getpath(1, 2) << endl;
}