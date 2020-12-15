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

int func() {
	ifstream input("input.txt");

	int result = 0;

	if (input.is_open()) {
		string s;
		int wayx = 10;
		int wayy = 1;
		int x = 0;
		int y = 0;

		//int dir = 1;

		while (getline(input, s)) {
			char c;
			int num;
			stringstream ss(s);

			ss >> c;
			ss >> num;

			if (c == 'F') {
				x += wayx * num;
				y += wayy * num;

				//switch (dir)
				//{
				//case 0:
				//	y += num;
				//	break;
				//case 1:
				//	x += num;
				//	break;
				//case 2:
				//	y -= num;
				//	break;
				//case 3:
				//	x -= num;
				//	break;
				//default:
				//	break;
				//}
			}
			else if (c == 'N') {
				//y += num;
				wayy += num;
			}
			else if (c == 'S') {
				//y -= num;
				wayy -= num;
			}
			else if (c == 'E') {
				wayx += num;
			}
			else if (c == 'W') {
				wayx -= num;
			}
			else if (c == 'L') {
				num /= 90;

				for (int i = 0; i < num; i++) {
					int temp = wayx;
					wayx = wayy * -1;
					wayy = temp;
				}
			}
			else if (c == 'R') {
				num /= 90;

				for (int i = 0; i < num; i++) {
					int temp = wayx;
					wayx = wayy;
					wayy = temp * -1;
				}
				//dir += num;
				//if (dir >= 4)
				//	dir -= 4;
			}
		}

		result = abs(x) + abs(y);
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << func() << endl;
}