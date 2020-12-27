#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

class MyHashFunction {
public:

	// Use sum of lengths of first and last names 
	// as hash function. 
	size_t operator()(const pair<int, int>& p) const
	{
		return p.first * (long long)10000 + p.second * (long long)100;
	}
};

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 0;

	if (input.is_open()) {
		string s;

		unordered_map<pair<int, int>, int, MyHashFunction> tiles;

		int max = 300;
		for (int x = -max; x <= max; x++) {
			for (int y = -max; y <= max; y++) {
				tiles[{x, y}] = 0;
			}
		}

		while (getline(input, s)) {
			int x = 0, y = 0;
			//s = "nwwswee";
			stringstream ss(s);

			char c;
			char dir = ' ';
			while (ss >> c) {
				if (c == 'e') {

					if (dir == 'n') {
						y += 1;
						x += 1;
					}
					else if (dir == 's') {
						y -= 1;
						x += 1;
					}
					else {
						x += 2;
					}

					dir = ' ';
				}
				else if (c == 'w') {
					if (dir == 'n') {
						y += 1;
						x -= 1;
					}
					else if (dir == 's') {
						y -= 1;
						x -= 1;
					}
					else {
						x -= 2;
					}

					dir = ' ';
				}
				else {
					dir = c;
				}
			}

			tiles[{x, y}]++;
		}

		//int l = 0;
		//for (auto& p : tiles) {
		//	if (p.second % 2) {
		//		l++;
		//	}
		//}
		//cout << ": " << l << endl;
		for (int i = 0; i < 100; i++) {
			unordered_map<pair<int, int>, int, MyHashFunction> newtiles = tiles;

			for (int y = -max; y <= max; y++) {

				for (int x = -max; x <= max; x++) {
					int black = 0;
					int white = 0;

					auto found = tiles.find({ (x - 2), y });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					found = tiles.find({ (x - 1), y + 1 });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					found = tiles.find({ (x - 1), y - 1 });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					found = tiles.find({ (x + 2), y });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					found = tiles.find({ (x + 1), y + 1 });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					found = tiles.find({ (x + 1), y - 1 });
					if (found != tiles.end()) {
						if (found->second % 2 == 0) {
							white++;
						}
						else {
							black++;
						}
					}

					if (newtiles[{x, y}] % 2 && (black == 0 || black > 2)) {
						newtiles[{x, y}]++;
					}
					else if (newtiles[{x, y}] % 2 == 0 && black == 2) {
						newtiles[{x, y}]++;
					}
				}
			}
			tiles = newtiles;

			//int local = 0;
			//for (auto& p : tiles) {
			//	if (p.second % 2) {
			//		local++;
			//	}
			//}
			//cout << i << ": " << local << endl;
		}

		for (auto& p : tiles) {
			if (p.second % 2) {
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
	cout << func() << endl;
}