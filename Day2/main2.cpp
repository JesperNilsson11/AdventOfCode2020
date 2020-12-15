#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Password {
	int low;
	int high;
	char c;
	string password;
};

istream& operator>>(istream& i, Password& p) {
	int num;
	char c;
	i >> p.low;
	i >> c;
	i >> p.high;
	i >> p.c;
	i >> c;
	i >> p.password;

	return i;
}

int getpasswords() {
	ifstream input("input.txt");
	vector<Password> passwords;

	int result = 0;

	if (input.is_open()) {
		Password p;

		while (input >> p) {
			passwords.emplace_back(p);
		}

		for (auto& p : passwords) {
			int nr = 0;
			for (auto& c : p.password) {
				if (c == p.c) {
					nr++;
				}
			}

			if (nr >= p.low && nr <= p.high) {
				result++;
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}

int getpasswords2() {
	ifstream input("input.txt");
	vector<Password> passwords;

	int result = 0;

	if (input.is_open()) {
		Password p;

		while (input >> p) {
			passwords.emplace_back(p);
		}

		for (auto& p : passwords) {
			if ((p.password[p.low-1] == p.c || p.password[p.high - 1] == p.c) && p.password[p.high - 1] != p.password[p.low - 1]) {
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
	cout << getpasswords2() << endl;
}