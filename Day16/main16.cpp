#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

int func() {
	ifstream input("input.txt");

	long long result = 1;

	if (input.is_open()) {
		string s;

		vector<vector<int>> tickets;
		vector<int> myticket;
		vector<pair<pair<int, int>, pair<int, int>>> ranges;
		int stage = 0;
		while (getline(input, s)) {
			stringstream ss(s);

			if (s == "") {
				continue;
			}
			if (s == "your ticket:") {
				stage = 1;
				continue;
			}
			if (s == "nearby tickets:") {
				stage = 2;
				continue;
			}

			if (stage == 0) {
				int n1,n2,n3,n4;
				char c;

				while (ss >> c) {
					if (c == ':')
						break;
				}

				ss >> n1;
				ss >> c;
				ss >> n2;

				ss >> c;
				ss >> c;

				ss >> n3;
				ss >> c;
				ss >> n4;

				ranges.push_back({ {n1,n2}, {n3,n4} });
			}
			else if (stage == 1) {
				char c;
				int num;

				while (ss >> num) {
					myticket.push_back(num);
					ss >> c;
				}
			}
			else {
				char c;
				int num;
				vector<int> ticket;
				while (ss >> num) {
					ticket.push_back(num);
					ss >> c;
				}

				tickets.push_back(ticket);
			}
		}

		for (auto it = tickets.begin(); it != tickets.end(); ) {
			bool invalid = false;
			for (auto n : *it) {
				bool valid = false;
				for (auto& r : ranges) {
					if ((r.first.first <= n && n <= r.first.second) || (r.second.first <= n && n <= r.second.second)) {
						valid = true;
					}
					else {
						//result += n;
						//break;
					}
				}

				if (!valid) {
					invalid = true;
					break;
				}
			}

			if (invalid) {
				it = tickets.erase(it);
			}
			else {
				it++;
			}
		}


		vector<unordered_map<int, int>> map(ranges.size());
		for (auto it = tickets.begin(); it != tickets.end(); it++) {
			for (int index = 0; index < it->size(); index++) {
				auto n = (*it)[index];
				for (int i = 0; i < ranges.size(); i++) {
					auto& r = ranges[i];
					if ((r.first.first <= n && n <= r.first.second) || (r.second.first <= n && n <= r.second.second)) {
						map[i][index]++;
					}
					else {
						//result += n;
						//break;
					}
				}
			}
		}

		for (auto& m : map) {
			vector<int> keys;
			for (auto& p : m) {
				if (p.second != 190)
					keys.push_back(p.first);
			}

			for (auto k : keys) {
				m.erase(k);
			}
		}

		unordered_map<int, int> dict;
		do {
			int key;
			int i;
			for (i = 0; i < map.size(); i++) {
				if (map[i].size() == 1) {
					key = map[i].begin()->first;
					break;
				}
			}

			dict[i] = key;

			for (auto& m : map) {
				m.erase(key);
			}
		} while (dict.size() < 20);

		for (auto& p : dict) {
			if (p.first < 6) {
				result *= myticket[p.second];
			}
		}

		cout << result << endl;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << func() << endl;
}