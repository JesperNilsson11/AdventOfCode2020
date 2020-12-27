#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;



unsigned long long func() {

	unsigned long long result = 1;
	unsigned long long key1 = 15733400, key2 = 6408062;

	unsigned long long loop = 1, subject_number = 7;

	while (subject_number != key1) {
		loop++;

		subject_number *= 7;
		subject_number %= 20201227;
	}
	
	for (int i = 0; i < loop; i++) {
		result *= key2;

		result %= 20201227;
	}

	return result;
}


int main() {
	cout << func() << endl;
}