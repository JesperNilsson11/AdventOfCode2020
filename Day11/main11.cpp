#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

unordered_map<int, long long> map;

long long rec(vector<int>& numbers, int index) {
	long long result = 0;

	if (index == numbers.size() - 1)
		return 1;

	auto f = map.find(index);
	if (f != map.end())
		return f->second;

	for (int i = index + 1; i < numbers.size(); i++) {
		if (numbers[i] - numbers[index] <= 3) {
			result += rec(numbers, i);
		}
	}

	map[index] = result;

	return result;
}

int adapters() {
	ifstream input("input.txt");

	int result = 0;

	if (input.is_open()) {
		string s;
		int num;
		int max = 0;
		vector<string> seats;
		while (getline(input,s)) {
			seats.push_back(s);
		}

		while (true) {
			vector<string> copy = seats;

			for (int y = 0; y < seats.size(); y++) {
				for (int x = 0; x < seats[y].size(); x++) {
					int count = 0;

					if (seats[y][x] == '.')
						continue;

					for (int yy = -1; yy < 2; yy++) {
						for (int xx = -1; xx < 2; xx++) {
							if (yy == 0 && xx == 0)
								continue;
							if (y + yy < 0 || y + yy >= seats.size() || x + xx < 0 || x + xx >= seats[y].size())
								continue;

							int yyy = y + yy;
							int xxx = x + xx;
							while (yyy >= 0 && yyy < seats.size() && xxx >= 0 && xxx < seats[y].size() && seats[yyy][xxx] == '.') {
								yyy += yy;
								xxx += xx;
							}
							

							if (yyy >= 0 && yyy < seats.size() && xxx >= 0 && xxx < seats[y].size() && seats[yyy][xxx] == '#')
								count++;
						}
					}

					if (seats[y][x] == 'L' && count == 0)
						copy[y][x] = '#';
					else if (seats[y][x] == '#' && count >= 5)
						copy[y][x] = 'L';
				}
			}

			if (copy == seats)
				break;

			seats = copy;
		}

		for (auto& s : seats) {
			for (auto c : s) {
				if (c == '#')
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
	cout << adapters() << endl;
}