#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

struct recipe {
	vector<string> ingridients;
	vector<string> allergens;
};

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 0;
	string sresult = "";

	if (input.is_open()) {
		string s;

		unordered_map<string, unordered_map<string,int>> allergens;
		unordered_map<string, bool> ingredients;
		vector<string> ingwithall;
		vector<recipe> recipes;
		while (getline(input, s)) {
			stringstream ss(s);
			bool ingrediant = true;

			string temp;
			recipe r;
			while (ss >> temp) {
				if (temp == "(contains") {
					ingrediant = false;
				}
				else if (ingrediant) {
					r.ingridients.push_back(temp);
					ingredients[temp] = true;
				}
				else {
					string a = temp.substr(0, temp.size() - 1);
					r.allergens.push_back(a);

					allergens[a] = {};
				}
			}

			recipes.push_back(r);
		}

		for (auto& r : recipes) {
			for (auto& i : r.ingridients) {
				for (auto& a : r.allergens) {
					allergens[a][i]++;
				}
			}
		}

		vector<pair<string, string>> dict;
		while (ingwithall.size() < 8) {
			string all;
			string ing;
			for (auto& a : allergens) {
				all = a.first;
				bool unique = true;
				int max = 0;

				for (auto& i : ingwithall) {
					a.second.erase(i);
				}

				for (auto& i : a.second) {
					if (i.second > max) {
						max = i.second;
						unique = true;
						ing = i.first;
					}
					else if (i.second == max) {
						unique = false;
					}
				}

				if (unique) {
					break;
				}
			}

			dict.push_back({ all, ing });

			ingwithall.push_back(ing);
			allergens.erase(all);
		}

		for (auto& r : recipes) {
			for (auto& i : r.ingridients) {
				bool found = false;
				for (auto& ii : ingwithall) {
					if (ii == i) {
						found = true;
						break;
					}
				}

				if (!found)
					result++;
			}
		}

		sort(dict.begin(), dict.end(), [](const pair<string, string>& a, const pair<string, string>& b) -> bool
			{
				return a.first < b.first;
			});

		for (auto& p : dict) {
			cout << p.second << ",";
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