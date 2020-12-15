#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

int decrypt() {
	ifstream input("input.txt");

	int result = 0;

	if (input.is_open()) {
		string s;
		int num;
		vector<int> numbers;
		vector<int> allnumbers;
		while (input >> num) {
			numbers.push_back(num);
			allnumbers.push_back(num);

			if (numbers.size() > 26)
				numbers.erase(numbers.begin());

			if (numbers.size() == 26) {
				bool found = false;

				for (int i = 0; i < 25; i++) {
					for (int j = 0; j < 25; j++) {
						if (i == j)
							continue;

						if (numbers[i] + numbers[j] == numbers[25]) {
							found = true;
							break;
						}
					}
				}

				if (!found) {
					//return numbers[25];
					break;
				}
			}
		}

		for (int i = 0; i < allnumbers.size(); i++) {
			int sum = 0;
			for (int j = i; j < allnumbers.size(); j++) {
				sum += allnumbers[j];

				if (sum == num) {
					int max = 0;
					int min = 100000000000;
					for (int x = i; x <= j; x++) {
						if (allnumbers[x] < min)
							min = allnumbers[x];
						if (allnumbers[x] > max)
							max = allnumbers[x];
					}
					
					return min + max;
				}
				else if (sum > num)
					break;
			}
		}
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << decrypt() << endl;
}