#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

struct Node {
	Node(int i) {
		val = i;
		next = nullptr;
	}

	int val;
	Node* next;
};

unsigned long long func() {
	long long result = 0;

	vector<Node> circle = { 7, 1, 2, 6, 4, 3, 5, 8, 9 };

	//int current = 0;
	for (int i = 10; i <= 1000000; i++)
		circle.emplace_back(i);

	Node* head = &circle[0];
	Node* current = head; 
	for (int i = 1; i < circle.size(); i++) {
		current->next = &circle[i];
		current = current->next;
	}
	current->next = head;

	current = head;
	

	for (int i = 0; i < 10000000; i++) {
		if (i % 100000 == 0)
			cout << i << " ";

		//vector<int> temp;
		Node* temp = current->next;
		Node* unhook = current->next;
		
		unhook = unhook->next;
		unhook = unhook->next;
		Node* null = unhook;
		unhook = unhook->next;
		null->next = nullptr;

		current->next = unhook;

		//int dest = circle[current] - 1;
		int dest = current->val;
		bool found = false;
		do {
			dest -= 1;
			if (dest < 1)
				dest = 1000000;

			found = false;
			Node* iter = temp;

			while (iter != nullptr) {
				if (iter->val == dest) {
					found = true;
					break;
				}
				iter = iter->next;
			}
		} while (found);

		Node* destindex = nullptr;
		if (dest > 9)
			destindex = &circle[dest - 1];
		else {
			for (int i = 0; i < 9; i++) {
				if (circle[i].val == dest) {
					destindex = &circle[i];
					break;
				}
			}
		}

		//int destindex = -1;
		//bool notfound = true;
		//while (notfound) {
		//	if (dest == 0)
		//		dest = 1000000;
		//	//for (int j = 0; j < circle.size();j++) {
		//	//	if (dest == circle[j]) {
		//	//		notfound = false;
		//	//		destindex = j;
		//	//		break;
		//	//	}
		//	//}
		//	Node* iter = current;
		//	do {
		//		if (dest == iter->val) {
		//			destindex = iter;
		//			notfound = false;
		//			break;
		//		}
		//
		//		iter = iter->next;
		//	} while (iter != current);
		//
		//	if (notfound)
		//		dest--;
		//}

		//circle.insert(circle.begin() + destindex + 1, temp.begin(), temp.end());
		Node* t = destindex->next;
		destindex->next = temp;

		temp = temp->next;
		temp = temp->next;
		temp->next = t;
		//if (destindex < current)
		//	current += 3;

		//current++;
		//current %= circle.size();

		current = current->next;

		
		////for (int v : circle) {
		////	n *= 10;
		////	n += v;
		////}
		//
	}

	//for (int i = 0; i < circle.size(); i++) {
	//	if (circle[i] == 1) {
	//		result = circle[i + 1] * circle[i + 2];
	//
	//		break;
	//	}
	//}

	cout << endl << endl;
	Node* iter = head;
	while (iter->val != 1)
		iter = iter->next;

	long long val1, val2;
	iter = iter->next;
	val1 = iter->val;
	iter = iter->next;
	val2 = iter->val;
	result = val1 * val2;

	cout << val1 << " *  " << val2 <<" = ";

	return result;
}


int main() {
	cout << func() << endl;
}