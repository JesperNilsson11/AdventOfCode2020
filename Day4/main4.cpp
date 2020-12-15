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
	char a,b,c;
	
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

int getpassports() {
	ifstream input("input.txt");
	vector<Passport> passports;
	vector<Passport> pc;

	int result = 0;

	if (input.is_open()) {
		Passport p;
		int counter = 0;
		while (input >> p) {
			counter++;
			passports.emplace_back(p);
		}

		for (auto& p : passports) {
			if (p.byr >= 1920 && p.byr <= 2002 && p.iyr >= 2010 && p.iyr <= 2020 && p.eyr >= 2020 && p.eyr <= 2030 && p.hgt.size() && p.hcl.size() && p.ecl.size() && p.pid.size()) {
				bool correct = true;

				if (p.hgt[p.hgt.size() - 1] == 'm' && p.hgt[p.hgt.size() - 2] == 'c') {
					stringstream ss(p.hgt);
					int height;
					ss >> height;

					if (height < 150 || height > 193)
						correct = false;
				}
				else if (p.hgt[p.hgt.size() - 1] == 'n' && p.hgt[p.hgt.size() - 2] == 'i') {
					stringstream ss(p.hgt);
					int height;
					ss >> height;

					if (height < 59 || height > 76)
						correct = false;
				}
				else {
					correct = false;
				}

				if (p.hcl[0] != '#' || p.hcl.size() != 7) {
					correct = false;
				}
				else {
					for (int i = 1; i < p.hcl.size(); i++) {
						char c = p.hcl[i];
						if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')) {
							//correct
						}
						else {
							correct = false;
						}
					}
				}

				if (p.ecl == "amb" || p.ecl == "blu" || p.ecl == "brn" || p.ecl == "gry" || p.ecl == "grn" || p.ecl == "hzl" || p.ecl == "oth") {
					//corretc
				}
				else {
					correct = false;
				}

				if (p.pid.size() != 9) {
					correct = false;
				}
				else {
					for (auto c : p.pid)
						if (c >= '0' && c <= '9') {
							//correct
						}
						else {
							correct = false;
						}
				}

				if (correct) {
					result++;
					pc.push_back(p);
				}
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	int counter = 0;
	for (auto& p : pc) {
		cout << counter << " " << p.hgt << endl;
		counter++;
	}

	return result;
}


int main() {
	cout << getpassports() << endl;
}