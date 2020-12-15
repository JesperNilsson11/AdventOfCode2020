#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;


int reversmod(int n, int mod) {
	while (n < 0)
		n += mod;

	return n;
}


int func() {
	ifstream input("input.txt");

	long long result = 0;

	//int num = 1008713;
	vector<int> ids = { 13,0,0,41,0,0,0,0,0,0,0,0,0,467,0,0,0,0,0,0,0,0,0,0,0,19,0,0,0,0,17,0,0,0,0,0,0,0,0,0,0,0,29,0,353,0,0,0,0,0,37,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,23 };

	//if (input.is_open()) {
		string s;

		while (getline(input, s)) {
			
		}

		

		vector<pair<int, int>> busses;
		for (int i = 0; i < ids.size(); i++) {
			if (ids[i] == 0)
				continue;

			busses.push_back({ ids[i], reversmod(-i, ids[i]) });
		}

		sort(busses.begin(), busses.end(), [](pair<int, int>& a, pair<int, int>& b) -> bool {
			return a.first > b.first;
			});

		long long min = 0;
		long long produkt = 1;
		for (int i = 0; i < busses.size(); i++) {
			while (min % busses[i].first != busses[i].second)
				min += produkt;
		
			produkt *= busses[i].first;
		}
		

		cout << min << endl;
	//}
	//else {
	//	cout << "failed loading file\n";
	//}

	return result;
}


int main() {
	cout << func() << endl;
}