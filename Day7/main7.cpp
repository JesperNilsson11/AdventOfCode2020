#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

bool findgold(unordered_map<string, vector<pair<string,int>>>& bags, string bag) {
	for (auto& b : bags[bag]) {
		if (b.first == "shinygold")
			return true;

		if (findgold(bags, b.first))
			return true;
	}

	return false;
}

int calcgold(unordered_map<string, vector<pair<string, int>>>& bags, string bag) {
	int result = 0;

	if (bags[bag].size() == 0)
		return 1;

	for (auto& b : bags[bag]) {
		result += b.second * calcgold(bags, b.first);
	}

	if (bag != "shinygold")
		result++;

	return result;
}

int calcbags() {
	ifstream input("input.txt");

	int result = 0;
	unordered_map<string, vector<pair<string, int>>> bags;

	if (input.is_open()) {
		string s;

		int counter = 0;
		while (getline(input, s)) {
			string b1, b2, trash;
			stringstream ss(s);

			ss >> b1;
			ss >> b2;

			ss >> trash;
			ss >> trash;
			ss >> trash;

			if (trash == "no") {
				bags[b1 + b2] = {};
				continue;
			}

			vector<pair<string,int>> vec;
			while (isdigit(trash[0])) {
				stringstream sss(trash);
				int num;
				sss >> num;
				string n1, n2;
				ss >> n1;
				ss >> n2;

				vec.push_back({ n1 + n2, num });

				ss >> trash;
				ss >> trash;
			}

			bags[b1 + b2] = vec;
		}

		for (auto& p : bags) {
			if (findgold(bags, p.first))
				result++;
		}

		result = calcgold(bags, "shinygold");
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << calcbags() << endl;
}