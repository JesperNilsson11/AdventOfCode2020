#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

struct Questions {
	unordered_map<char, int> map;
	int nr = 0;
};

istream& operator>>(istream& i, Questions& q) {
	string key;
	string line;
	char c;

	q = {};

	while (getline(i, line), line.size()) {
		stringstream ss(line);
		q.nr++;
		while (ss >> c) {
			q.map[c]++;
		}
	}

	return i;
}

int calcanswers() {
	ifstream input("input.txt");

	int result = 0;

	if (input.is_open()) {
		string s;
		Questions q;

		int counter = 0;
		while (input >> q) {
			for (auto& p : q.map) {
				if (p.second == q.nr)
					result++;
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << calcanswers() << endl;
}