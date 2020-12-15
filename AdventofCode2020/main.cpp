#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int extractnumbers() {
	ifstream input("input.txt");
	vector<int> numbers;

	int result = 0;

	if (input.is_open()) {
		int number;

		while (input >> number) {
			numbers.emplace_back(number);
		}

		bool found = false;

		for (int i = 0; i < numbers.size() && !found; ++i) {
			for (int j = i + 1; j < numbers.size() && !found; ++j) {
				for (int k = j + 1; k < numbers.size() && !found; ++k) {
					if (numbers[i] + numbers[j] + numbers[k] == 2020) {
						result = numbers[i] * numbers[j] * numbers[k];
						found = true;
					}
				}
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}

int main() {
	cout << extractnumbers() << endl;
}