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
	ifstream input("input.txt");

	long long result = 0;

	if (input.is_open()) {
		string s;
		string mask = "";
		unordered_map<unsigned long long, unsigned long long> memory;

		//int dir = 1;

		while (getline(input, s)) {
			stringstream ss(s);

			string ins = "";
			for (int i = 0; i < 4; i++) {
				char c;
				ss >> c;

				ins += c;
			}

			if (ins == "mask") {
				ss >> ins;
				ss >> ins;

				mask = ins;
			}
			else if (ins == "mem[") {
				unsigned long long mem;
				unsigned long long val;
				ss >> mem;
				char c;

				ss >> c;
				ss >> c;

				ss >> val;

				//mask = "000000000000000000000000000000X1001X";
				//mem = 42;
				//val = 100;

				string smem = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X";
				long long x = 0;
				for (long long i = mask.size() - 1; i >= 0; i--) {
					if (mask[i] == '0') {
						long long m = (long long)1 << (35 - i);
						long long bit = mem & m;
						bit = bit >> (35 - i);

						smem[i] = to_string(bit)[0];
					}
					else if (mask[i] == '1') {
						smem[i] = '1';
					}
					else {
						smem[i] = 'X';
						x++;
					}
				}

				if (x == 0) {
					memory[getmem(smem)] = val;
				}
				else {
					for (long long i = 0; i < powl(2, x); i++) {
						string newsmem = smem;
						int posx = 0;

						for (auto& c : newsmem) {
							if (c == 'X') {
								long long bit = i & ((long long)1 << posx);

								if (bit) {
									c = '1';
								}
								else {
									c = '0';
								}

								posx++;
							}
						}

						memory[getmem(newsmem)] = val;
					}
				}

				//unsigned long long newval = 0;
				//for (long long i = mask.size() - 1; i >= 0; i--) {
				//	if (mask[i] == '1') {
				//		newval += (long long)1 << (35 - i);
				//	}
				//	else if (mask[i] == 'X') {
				//		newval = newval | (val & (long long)1 << (35 - i));
				//	}
				//}
				//
				//memory[mem] = newval;
			}
		}

		for (auto& p : memory)
			result += p.second;

		cout << result << endl;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << func() << endl;
}