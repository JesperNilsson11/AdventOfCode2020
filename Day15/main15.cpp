#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

unordered_map<int, long long> map;

long long getmem(string smem) {
	long long mem = 0;
	for (long long i = smem.size() - 1; i >= 0; i--) {
		mem = mem | ((long long)smem[i] - '0' << (35 - i));
	}

	return mem;
}


int func() {

	long long result = 0;


	string s;
	unordered_map<int, int> numbers;

	numbers[16] = 1;
	numbers[1] = 2;
	numbers[0] = 3;
	numbers[18] = 4;
	numbers[12] = 5;
	numbers[14] = 6;
	//numbers[19] = 7;

	int turn = 7;
	int nextnumber = 19;

	while (turn < 30000000) {
		auto found = numbers.find(nextnumber);

		if (found == numbers.end()) {
			numbers[nextnumber] = turn;

			nextnumber = 0;
		}
		else {
			int num = turn - numbers[nextnumber];
			numbers[nextnumber] = turn;

			nextnumber = num;
		}

		turn++;
	}

	result = nextnumber;

	return result;
}


int main() {
	cout << func() << endl;
}