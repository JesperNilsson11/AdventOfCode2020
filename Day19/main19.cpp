#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

pair<bool, int> match(unordered_map<string, vector<vector<string>>>& rules, string rule, string word, int index);

bool rules0(unordered_map<string, vector<vector<string>>>& rules, string word, int eight, int eleven) {
	int index = 0;

	for (int i = 0; i < eight; i++) {
		auto p = match(rules, "42", word, index);

		if (p.first == false)
			return false;

		index = p.second;
	}

	for (int i = 0; i < eleven; i++) {
		auto p = match(rules, "42", word, index);

		if (p.first == false)
			return false;

		index = p.second;
	}
	for (int i = 0; i < eleven; i++) {
		auto p = match(rules, "31", word, index);

		if (p.first == false)
			return false;

		index = p.second;
	}

	return index == word.size();
}

pair<bool, int> match(unordered_map<string, vector<vector<string>>>& rules, string rule, string word, int index) {
	if (rules[rule].size() == 1 && rules[rule][0].size() == 1 && (rules[rule][0][0] == "a" || rules[rule][0][0] == "b")) {
		if (rules[rule][0][0][0] == word[index])
			return { true, index + 1 };
		else
			return { false, index };
	}

	bool ruleok = false;
	int newindex = index;
	//bool loop = false;
	//int counter = 0;
	//bool previousloop;
	//if (rule == "11" || rule == "8")
	//	loop = false;

	do {
		for (auto& v : rules[rule]) {
			newindex = index;
			//previousloop = false;
			if (rule == "0") {
				for (int eight = 1; eight < 10; eight++) {
					for (int eleven = 1; eleven < 10; eleven++) {
						if (rules0(rules, word, eight, eleven))
							return { true, word.size() };
					}
				}

				return { false, 0 };
			}
			else {
				for (int i = 0; i < v.size(); i++) {
					auto& r = v[i];

					auto p = match(rules, r, word, newindex);

					ruleok = p.first;

					//if (previousloop && !ruleok) {
					//	i -= 2;
					//	previousloop = false;
					//	continue;
					//}
					if (!ruleok)
						break;


					//previousloop = r == "11" || r == "8";
					newindex = p.second;
				}

				if (ruleok) {
					index = newindex;
					//if (loop)
					//	counter++;
					break;
				}
			}
		}

		//if (!ruleok) {
		//	loop = false;
		//
		//	if (counter > 0) {
		//		ruleok = true;
		//		newindex = index;
		//	}
		//}
	} while (false);

	//if (rule == "0" && newindex != word.size())
	//	return { false, index };

	if (ruleok)
		return { true, newindex };

	return { false, index };
}

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 0;
	string sresult = "";

	if (input.is_open()) {
		string s;

		unordered_map<string, vector<vector<string>>> rules;
		int lines = 0;
		while (getline(input, s)) {
			lines++;
			if (s.size() == 0)
				continue;

			if (s[0] == 'a' || s[0] == 'b') {
				if (match(rules, "0", s, 0).first) {
					result++;
					//cout << s << endl;
				}
			}
			else {
				stringstream ss(s);
				string key;

				ss >> key;
				key = key.substr(0, key.size() - 1);
				vector<vector<string>> temp1;

				string val;
				temp1.push_back({});
				while (ss >> val) {
					if (val == "|") {
						temp1.push_back({});
						continue;
					}

					if (val[0] == '\"')
						val = val[1];

					temp1.back().push_back(val);
				}

				rules[key] = temp1;
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