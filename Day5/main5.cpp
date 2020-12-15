#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

struct Passport {
	int byr = 0;
	int iyr = 0;
	int eyr = 0;
	string hgt;
	string hcl;
	string ecl;
	string pid;
	string cid;
};

istream& operator>>(istream& i, Passport& p) {
	string key;
	string line;
	char a, b, c;

	p = {};

	while (getline(i, line), line.size()) {
		stringstream ss(line);

		while (ss >> a) {
			key = {};
			ss >> b;
			ss >> c;

			key += a;
			key += b;
			key += c;
			char dot;
			ss >> dot;

			if (key == "byr") {
				ss >> p.byr;
			}
			else if (key == "iyr") {
				ss >> p.iyr;
			}
			else if (key == "eyr") {
				ss >> p.eyr;
			}
			else if (key == "hgt") {
				ss >> p.hgt;
			}
			else if (key == "hcl") {
				ss >> p.hcl;
			}
			else if (key == "pid") {
				ss >> p.pid;
			}
			else if (key == "ecl") {
				ss >> p.ecl;
			}
			else if (key == "cid") {
				ss >> p.cid;
			}
			else {
				cout << "Warning!!!\n";
			}
		}
	}

	return i;
}

int findseat() {
	ifstream input("input.txt");
	unordered_map<int, bool> seats;

	int result = 0;

	if (input.is_open()) {
		string s;

		while (input >> s) {
			int lower = 0;
			int higher = 127;
			int lowc = 0;
			int highc = 7;

			for (auto c : s) {
				if (c == 'F') {
					higher -= (higher - lower + 1) / 2;
				}
				else if (c == 'B') {
					lower += (higher - lower + 1) / 2;
				}
				else if (c == 'L') {
					highc -= (highc - lowc + 1) / 2;
				}
				else if (c == 'R') {
					lowc += (highc - lowc + 1) / 2;
				}
			}

			int id = higher * 8 + highc;

			seats[id] = true;

			if (id > result)
				result = id;
		}

		for (int i = 0; i <= 848; i++) {
			auto got = seats.find(i);

			if (got == seats.end()) {
				cout << "id: " << i << endl;
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << findseat() << endl;
}