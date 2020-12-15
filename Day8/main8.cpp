#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

int calcbags() {
	ifstream input("input.txt");

	int result = 0;
	vector<pair<string, bool>> program;

	if (input.is_open()) {
		string s;

		while (getline(input, s)) {
			program.push_back({ s, false });
		}

		bool found = false;
		int counter = 0;
		int accumalator = 0;
		while (!found) {
			int nrofjmpnop = 0;
			int pc = 0;
			accumalator = 0;

			for (auto& p : program)
				p.second = false;

			while (program[pc].second == false) {
				program[pc].second = true;
				stringstream ss(program[pc].first);
				string instruction;
				int value;

				ss >> instruction;
				ss >> value;

				if (instruction != "acc") {
					if (nrofjmpnop == counter) {
						if (instruction == "jmp")
							instruction = "nop";
						else
							instruction = "jmp";
					}

					nrofjmpnop++;
				}

				if (instruction == "acc") {
					accumalator += value;
				}
				else if (instruction == "jmp") {
					pc += value - 1;
				}
				else if (instruction == "nop") {

				}

				pc++;

				if (pc == program.size()) {
					found = true;
					break;
				}
			}

			counter++;
		}

		result = accumalator;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << calcbags() << endl;
}