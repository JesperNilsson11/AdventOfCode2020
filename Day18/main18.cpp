#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

struct math {
	unsigned long long num;
	bool add;
};

pair<int,int> getindex(const string& s, int index) {
	int min, max;

	int brackets = 0;
	min = 0;
	for (int i = index; i >= 0; i--) {
		if (s[i] >= '0' && s[i] <= '9' && brackets == 0) {
			min = i;
			break;
		}
		else if (s[i] == ')') {
			brackets++;
		}
		else if (s[i] == '(') {
			brackets--;

			if (brackets == 0) {
				min = i;
				break;
			}
		}
	}

	brackets = 0;
	max = s.size() - 1;
	for (int i = index; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9' && brackets == 0) {
			max = i;
			break;
		}
		else if (s[i] == ')') {
			brackets--;

			if (brackets == 0) {
				max = i;
				break;
			}

		}
		else if (s[i] == '(') {
			brackets++;
		}
	}

	return { min, max };
}

void manipulate(string& s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '+') {
			auto p = getindex(s, i);

			string s1 = s.substr(0, p.first);
			string s2 = s.substr(p.first, p.second - p.first + 1);
			string s3 = s.substr(p.second + 1, s.size() - (p.second + 1));

			s = s1 + "(" + s2 + ")" + s3;

			i++;
		}
	}
}

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 0;
	string sresult = "";

	if (input.is_open()) {
		string s;

		int lines = 0;
		long long max = 0;
		while (getline(input, s)) {
			//s = "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2";
			manipulate(s);
			vector<math> stack;

			stack.push_back({ 0, true });

			stringstream ss(s);
			char c;

			bool lastwasadd = true;
			//int readexpression = 0;

			while (ss >> c) {
				if (c == '(') {
					stack.push_back({ 0, lastwasadd });

					lastwasadd = true;

					//if (readexpression == 1)
					//	readexpression++;
				}
				else if (c == ')') {
					auto m = stack.back();

					stack.pop_back();

					if (m.add) {
						stack.back().num += m.num;
					}
					else {
						stack.back().num *= m.num;
					}

					//if (readexpression == 2) {
					//	//m = stack.back();
					//	//
					//	//stack.pop_back();
					//	//
					//	//stack.back().num *= m.num;
					//
					//	readexpression--;
					//}
				}
				else if (c == '+') {
					lastwasadd = true;
				}
				else if (c == '*') {
					//if (readexpression == 1) {
					//	auto m = stack.back();
					//	
					//	stack.pop_back();
					//	
					//	stack.back().num *= m.num;
					//}
					//else if (readexpression > 1)
					//
					lastwasadd = false;
					//readexpression = 1;
					//stack.push_back({ 0, false });
				}
				else {
					int num = c - '0';

					if (lastwasadd)
						stack.back().num += num;
					else
						stack.back().num *= num;
				}
			}

			//while (stack.size() > 1) {
			//	auto m = stack.back();
			//
			//	stack.pop_back();
			//
			//	if (m.add) {
			//		stack.back().num += m.num;
			//	}
			//	else {
			//		stack.back().num *= m.num;
			//	}
			//}

			if (stack.size() != 1)
				cout << "error";
			result += stack[0].num;

			int size = sresult.size();
			string add = to_string(stack[0].num);
			if (size < add.size())
				size = add.size();
			size++;

			string newresult(size, '0');
			bool carry = false;
			for (int i = 0; i < size; i++) {
				int num = 0;

				if (i < sresult.size()) {
					num += sresult[sresult.size() - 1 - i] - '0';
				}
				if (i < add.size()) {
					num += add[add.size() - 1 - i] - '0';
				}

				if (carry)
					num += 1;

				carry = num >= 10;
				num %= 10;

				newresult[newresult.size() - 1 - i] = num + '0';
			}

			if (newresult[0] == '0') {
				newresult = newresult.substr(1, newresult.size() - 1);
			}

			sresult = newresult;

			lines++;
			if (max < stack[0].num) {
				max = stack[0].num;
			}
		}
		cout << lines << " " << max << endl;
		cout << sresult << endl;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << func() << endl;
}