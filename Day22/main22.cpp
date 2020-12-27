#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

struct hash_func {

unsigned long operator()(const pair<vector<int>, vector<int>>& key) const
{
	unsigned long hash = 0;
	for (int i = 0; i < key.first.size(); i++)
	{
		hash += (71 * hash + key.first[i]) % 5;
	}
	return hash;
}
};

struct key_func {

bool operator()(const pair<vector<int>, vector<int>>& key1, const pair<vector<int>, vector<int>>& key2) const
{
	if (key1.first.size() != key2.first.size() || key1.second.size() != key2.second.size())
		return false;

	for (int i = 0; i < key1.first.size(); i++) {
		if (key1.first[i] != key2.first[i])
			return false;
	}
	for (int i = 0; i < key1.second.size(); i++) {
		if (key1.second[i] != key2.second[i])
			return false;
	}

	return true;
}
};

unordered_map<pair<vector<int>, vector<int>>, bool, hash_func, key_func> memoize;

pair<bool, vector<int>> play_game(vector<int> d1, vector<int> d2, int depth) {

	unordered_map<pair<vector<int>, vector<int>>, bool, hash_func, key_func> SEEN;
	int rounds = 0;
	while (d1.size() && d2.size()) {
		rounds++;
		pair<vector<int>, vector<int>> my_key = { d1, d2 };
		auto found = SEEN.find(my_key);
		if (found != SEEN.end())
			return { true, d1 };

		SEEN[my_key] = true;
		int c1 = d1[0], c2 = d2[0];
		d1.erase(d1.begin());
		d2.erase(d2.begin());
		
		bool p1_wins = false;

		if (d1.size() >= c1 && d2.size() >= c2) {
			if (depth == 3)
				cout << rounds << " ";

			vector<int> NEW_D1;
			for (int i = 0; i < c1; i++)
				NEW_D1.emplace_back(d1[i]);
			vector<int> NEW_D2;
			for (int i = 0; i < c2; i++)
				NEW_D2.emplace_back(d2[i]);

			auto p = play_game(NEW_D1, NEW_D2, depth+1);
			p1_wins = p.first;
		}
		else {
			p1_wins = c1 > c2;
		}

		if (p1_wins) {
			d1.emplace_back(c1);
			d1.emplace_back(c2);
		}
		else {
			d2.emplace_back(c2);
			d2.emplace_back(c1);
		}
	}
	
	if (d1.size())
		return { true, d1 };
	else
		return { false, d2 };
}

bool rec(vector<int> deck1, vector<int> deck2, int depth) {
	unordered_map<pair<vector<int>, vector<int>>, bool, hash_func, key_func> map;

	auto f = memoize.find({ deck1, deck2 });
	//if (f != memoize.end())
	//	return f->second;
	int rounds = 0;
	while (deck1.size() && deck2.size()) {
		rounds++;
		int num1 = deck1[0];
		int num2 = deck2[0];

		auto found = map.find({ deck1, deck2 });
		if (found != map.end()) {
			return true;
		}
		map[{deck1, deck2}] = true;

		deck1.erase(deck1.begin());
		deck2.erase(deck2.begin());


		if (num1 > deck1.size() || num2 > deck2.size()) {
			if (num1 > num2) {
				deck1.push_back(num1);
				deck1.push_back(num2);
			}
			else if (num1 == num2) {
				cout << "error\n";
			}
			else {
				deck2.push_back(num2);
				deck2.push_back(num1);
			}
		}
		else {
			vector<int> newdeck1;
			for (int i = 0; i < num1; i++)
				newdeck1.push_back(deck1[i]);
			vector<int> newdeck2;
			for (int i = 0; i < num2; i++)
				newdeck2.push_back(deck2[i]);
			if (depth == 1)
				cout << "1:" << rounds << " ";
			if (depth == 2)
				cout << "2:" << rounds << " ";
			if (depth == 3)
				cout << "1 ";
			if (depth == 4)
				cout << "2 ";

			if (rec(newdeck1, newdeck2, depth+1)) {
				deck1.push_back(num1);
				deck1.push_back(num2);

				memoize[{newdeck1, newdeck2}] = true;
			}
			else {
				deck2.push_back(num2);
				deck2.push_back(num1);
				memoize[{newdeck1, newdeck2}] = false;
			}
		}
	}

	return deck1.size() > 0;
}

long long calc(const vector<int>& cards) {
	long long result = 0;

	for (int i = 0; i < cards.size(); i++) {
		result += cards[i] * (cards.size() - i);
	}

	return result;
}

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 0;


	string s;

	vector<int> deck1 = { 10, 21, 37,2,47,13,6,29,9,3,4,48,46,25,44,41,23,20,24,12,45,43,5,27,50 };
	vector<int> deck2 = { 39,42,31,36,7,1,49,19,40,35,8,11,18,30,14,17,15,34,26,33,32,38,28,16,22 };

	return calc(play_game(deck1, deck2, 0).second);

	unordered_map<pair<vector<int>, vector<int>>, bool, hash_func, key_func> map;
	int round = 0;
	while (deck1.size() && deck2.size()) {
		cout << "round " << ++round << endl;
		int num1 = deck1[0];
		int num2 = deck2[0];

		auto found = map.find({ deck1, deck2 });
		if (found != map.end()) {
			break;
		}
		map[{deck1, deck2}] = true;

		deck1.erase(deck1.begin());
		deck2.erase(deck2.begin());


		if (num1 > deck1.size() || num2 > deck2.size()) {
			if (num1 > num2) {
				deck1.push_back(num1);
				deck1.push_back(num2);
			}
			else if (num1 == num2) {
				cout << "error\n";
			}
			else {
				deck2.push_back(num2);
				deck2.push_back(num1);
			}
		}
		else {
			if (round == 79) {
				//deck1.push_back(num1);
				//deck1.push_back(num2);
				//continue;
				round++;
			}

			vector<int> newdeck1;
			for (int i = 0; i < num1; i++)
				newdeck1.push_back(deck1[i]);
			vector<int> newdeck2;
			for (int i = 0; i < num2; i++)
				newdeck2.push_back(deck2[i]);

			if (rec(newdeck1, newdeck2, 0)) {
				deck1.push_back(num1);
				deck1.push_back(num2);
			}
			else {
				deck2.push_back(num2);
				deck2.push_back(num1);
			}
		}
	}

	if (deck1.size()) {
		result = calc(deck1);
	}
	else {
		result = calc(deck2);
	}



	return result;
}


int main() {
	cout << func() << endl;
}