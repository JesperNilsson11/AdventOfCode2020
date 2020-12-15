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

	if (index == numbers.size()-1)
		return 1;
	
	auto f = map.find(index);
	if (f != map.end())
		return f->second;

	for (int i = index + 1; i < numbers.size(); i++) {
		if (numbers[i]-numbers[index] <= 3) {
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
		vector<int> numbers;
		while (input >> num) {
			if (num > max)
				max = num;

			numbers.push_back(num);
		}

		numbers.push_back(0);
		numbers.push_back(max + 3);
		sort(numbers.begin(), numbers.end());

		int one = 0;
		int three = 0;
		for (int i = 0; i < numbers.size() - 1; i++) {
			int dif = numbers[i + 1] - numbers[i];

			if (dif == 1)
				one++;
			else if (dif == 3)
				three++;
			else if (dif > 3)
				cout << "warning";
		}

		result = one * three;

		auto r = rec(numbers, 0);

		cout << r << endl;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << adapters() << endl;
}