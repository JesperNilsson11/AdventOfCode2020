#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

class Tile {
public:
	Tile() = default;

	bool share_border(Tile& o) {
		bool tt = true, tti = true, tr = true, tri = true, tb = true, tbi = true, tl = true, tli = true;
		bool lt = true, lti = true, lr = true, lri = true, lb = true, lbi = true, ll = true, lli = true;
		bool rt = true, rti = true, rr = true, rri = true, rb = true, rbi = true, rl = true, rli = true;
		bool bt = true, bti = true, br = true, bri = true, bb = true, bbi = true, bl = true, bli = true;
		for (int i = 0; i < 10; i++) {
			if (tt) {
				tt = data[0][i] == o.data[0][i];
			}
			if (tti) {
				tti = data[0][i] == o.data[0][9 - i];
			}
			if (tb)
				tb = data[0][i] == o.data[9][i];
			if (tbi) {
				tbi = data[0][i] == o.data[9][9 - i];
			}
			if (tr) {
				tr = data[0][i] == o.data[i][9];
			}
			if (tri) {
				tri = data[0][i] == o.data[9 - i][9];
			}
			if (tl) {
				tl = data[0][i] == o.data[i][0];
			}
			if (tli) {
				tli = data[0][i] == o.data[9 - i][0];
			}

			if (lt) {
				lt = data[i][0] == o.data[0][i];
			}
			if (lti) {
				lti = data[i][0] == o.data[0][9 - i];
			}
			if (lb)
				lb = data[i][0] == o.data[9][i];
			if (lbi) {
				lbi = data[i][0] == o.data[9][9 - i];
			}
			if (lr) {
				lr = data[i][0] == o.data[i][9];
			}
			if (lri) {
				lri = data[i][0] == o.data[9 - i][9];
			}
			if (ll) {
				ll = data[i][0] == o.data[i][0];
			}
			if (lli) {
				lli = data[i][0] == o.data[9 - i][0];
			}

			if (rt) {
				rt = data[i][9] == o.data[0][i];
			}
			if (rti) {
				rti = data[i][9] == o.data[0][9 - i];
			}
			if (rb)
				rb = data[i][9] == o.data[9][i];
			if (rbi) {
				rbi = data[i][9] == o.data[9][9 - i];
			}
			if (rr) {
				rr = data[i][9] == o.data[i][9];
			}
			if (rri) {
				rri = data[i][9] == o.data[9 - i][9];
			}
			if (rl) {
				rl = data[i][9] == o.data[i][0];
			}
			if (rli) {
				rli = data[i][9] == o.data[9 - i][0];
			}

			if (bt) {
				bt = data[9][i] == o.data[0][i];
			}
			if (bti) {
				bti = data[9][i] == o.data[0][9 - i];
			}
			if (bb)
				bb = data[9][i] == o.data[9][i];
			if (bbi) {
				bbi = data[9][i] == o.data[9][9 - i];
			}
			if (br) {
				br = data[9][i] == o.data[i][9];
			}
			if (bri) {
				bri = data[9][i] == o.data[9 - i][9];
			}
			if (bl) {
				bl = data[9][i] == o.data[i][0];
			}
			if (bli) {
				bli = data[9][i] == o.data[9 - i][0];
			}
		}

		bool wasstatic = o.is_static;
		if (is_static) {
			if (tt) {
				// correct
				o.flipy();
				o.is_static = true;

				top = &o;
				o.bot = this;
			}
			else if (tti) {
				// correct
				o.rotate();
				o.rotate();
				o.is_static = true;

				top = &o;
				o.bot = this;
			}
			else if (tr) {
				// correct
				o.rotate();
				o.flipy();
				o.is_static = true;

				top = &o;
				o.bot = this;
			}
			else if (tri) {
				o.rotate();
				o.rotate();
				o.rotate();

				o.is_static = true;
				top = &o;
				o.bot = this;
			}
			else if (tb) {
				// correct
				o.is_static = true;
				top = &o;
				o.bot = this;
			}
			else if (tbi) {
				// correct
				o.flipx();

				o.is_static = true;
				top = &o;
				o.bot = this;
			}
			else if (tl) {
				// correct
				o.rotate();

				o.is_static = true;
				top = &o;
				o.bot = this;
			}
			else if (tli) {
				// correct
				o.rotate();
				o.flipx();

				o.is_static = true;
				top = &o;
				o.bot = this;
			}
			else if (lt) {
				o.rotate();
				o.flipx();
				o.flipy();

				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lti) {
				o.rotate();
				o.flipx();

				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lr) {
				// correct
				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lri) {
				o.flipy();

				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lb) {
				// correct
				o.rotateright();
				o.flipx();

				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lbi) {
				// correct
				o.rotate();
				o.rotate();
				o.rotate();
				o.flipx();

				o.flipy();

				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (ll) {
				o.flipx();
				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (lli) {
			// correct
				o.flipx();
				o.flipy();
				o.is_static = true;
				left = &o;
				o.right = this;
			}
			else if (rt) {
			// correct
			o.rotateleft();
			o.flipy();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rti) {
			o.rotateleft();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rr) {
			// correct
			o.rotateleft();
			o.rotateleft();
			o.flipy();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rri) {
			// correct
			o.rotateleft();
			o.rotateleft();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rb) {
			o.rotateright();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rbi) {
			// correct
			o.rotateright();
			o.flipy();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rl) {
			// correct
			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (rli) {
			// correct
			o.flipy();

			o.is_static = true;
			right = &o;
			o.left = this;
			}
			else if (bt) {
			// correct
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bti) {
			o.flipx();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (br) {
			o.rotateleft();

			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bri) {
			// correct
			o.rotateleft();
			o.flipx();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bb) {
			o.rotateleft();
			o.rotateleft();
			o.flipx();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bbi) {
			// correct
			o.rotateleft();
			o.rotateleft();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bl) {
			// correct
			o.rotateright();
			o.flipx();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
			else if (bli) {
			o.rotateright();
			o.is_static = true;
			bot = &o;
			o.top = this;
			}
		}

		static int counter = 0;
		if (o.is_static && !wasstatic && false) {
			cout << endl;
			cout << endl;
			cout << counter++ << endl;
			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {
					cout << data[y][x];
				}
				cout << "   ";
				for (int x = 0; x < 10; x++) {
					cout << o.data[y][x];
				}

				cout << endl;
			}
		}

	return tt || tti || tr || tri || tb || tbi || tl || tli ||
		lt || lti || lr || lri || lb || lbi || ll || lli ||
		rt || rti || rr || rri || rb || rbi || rl || rli ||
		bt || bti || br || bri || bb || bbi || bl || bli;
}

void flipx() {
	vector<vector<char>> newdata = data;
	//for (auto& d : data) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			newdata[y][x] = data[y][9 - x];
		}
	}

	data = newdata;
	//cout << endl;
	//
	//for (auto& d : newdata) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}
}

void flipy() {
	vector<vector<char>> newdata = data;
	//for (auto& d : data) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			newdata[y][x] = data[9 - y][x];
		}
	}
	data = newdata;
	//cout << endl;
	//
	//for (auto& d : newdata) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}
}

void rotate() {
	vector<vector<char>> newdata = data;
	//for (auto& d : data) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}

	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			newdata[y][x] = data[x][9 - y];
		}
	}
	data = newdata;
	//cout << endl;
	//
	//for (auto& d : newdata) {
	//	for (auto c : d)
	//		cout << c;
	//	cout << endl;
	//}
}

void rotateleft() {
	rotate();
}

void rotateright() {
	rotate();
	rotate();
	rotate();
}

vector<vector<char>> data;
int id = -1;
Tile* left = nullptr;
Tile* right = nullptr;
Tile* top = nullptr;
Tile* bot = nullptr;
bool is_static = false;
};

void flipy(vector<vector<char>>& data) {
	vector<vector<char>> newdata = data;
	for (int y = 0; y < data.size(); y++) {
		for (int x = 0; x < data[y].size(); x++) {
			newdata[y][x] = data[data[y].size() - 1 - y][x];
		}
	}
	data = newdata;
}
void flipx(vector<vector<char>>& data) {
	vector<vector<char>> newdata = data;

	for (int y = 0; y < data.size(); y++) {
		for (int x = 0; x < data[y].size(); x++) {
			newdata[y][x] = data[y][data[y].size()-1 - x];
		}
	}

	data = newdata;
}

void rotate(vector<vector<char>>& data) {
	vector<vector<char>> newdata = data;
	
	for (int y = 0; y < data.size(); y++) {
		for (int x = 0; x < data[y].size(); x++) {
			newdata[y][x] = data[x][data[y].size() - 1 - y];
		}
	}
	data = newdata;
}

long long findmonsters(vector<vector<char>>& image) {
	long long counter = 0;
	vector<string> monster = {	"                  # ",
								"#    ##    ##    ###",
								" #  #  #  #  #  #   "
	};
	rotate(image);
	//flipy(image);
	//flipx(image);

	for (int y = 0; y < image.size() - monster.size(); y++) {
		for (int x = 0; x < image[y].size() - monster[0].size(); x++) {
			bool foundmonster = true;
			for (int yy = 0; yy < monster.size() && foundmonster; yy++) {
				for (int xx = 0; xx < monster[yy].size(); xx++) {
					if (monster[yy][xx] == '#') {
						if (image[y + yy][x + xx] == '.') {
							foundmonster = false;
							break;
						}
					}
				}
			}

			if (foundmonster) {
				counter++;

				for (int yy = 0; yy < monster.size() && foundmonster; yy++) {
					for (int xx = 0; xx < monster[yy].size(); xx++) {
						if (monster[yy][xx] == '#') {
							image[y + yy][x + xx] = 'O';
						}
					}
				}
			}
		}
	}

	counter = 0;
	for (auto& r : image) {
		for (auto c : r) {
			if (c == '#') {
				counter++;
			}
		}
	}

	return counter;
}

unsigned long long func() {
	ifstream input("input.txt");

	unsigned long long result = 1;
	string sresult = "";

	if (input.is_open()) {
		string s;

		vector<Tile> tiles;

		Tile temp;
		temp.id = -1;
		while (getline(input, s)) {
			if (s.size() == 0) {
				if (temp.id != -1) {
					tiles.push_back(temp);
					temp.id = -1;
					temp.data.clear();
				}

				continue;
			}
			else if (s[0] == 'T') {
				stringstream ss(s);
				string t;

				ss >> t;
				ss >> temp.id;
			}
			else {
				stringstream ss(s);
				char c;

				temp.data.push_back({});
				while (ss >> c) {
					temp.data.back().push_back(c);
				}
			}
		}

		int num = 0;
		for (int i = 0; i < tiles.size(); i++) {
			int neigbours = 0;
			for (int j = 0; j < tiles.size(); j++) {
				if (i == j)
					continue;

				if (tiles[i].share_border(tiles[j]))
					neigbours++;
			}

			if (neigbours == 2) {
				cout << tiles[i].id << " ";
				result *= tiles[i].id;
				num++;
			}
		}

		bool allstatic = false;
		tiles[0].is_static = true;
		while (!allstatic) {
			allstatic = true;

			for (int i = 0; i < tiles.size(); i++) {
				if (!tiles[i].is_static)
					allstatic = false;
				for (int j = 0; j < tiles.size(); j++) {
					if (i == j)
						continue;

					if (tiles[i].is_static)
						tiles[i].share_border(tiles[j]);
				}
			}
		}

		cout << endl;
		Tile* topleft = nullptr;
		for (auto& t : tiles) {
			if (t.top == nullptr && t.left == nullptr) {
				topleft = &t;
				break;
			}
		}

		vector<vector<char>> image;
		int depth = 0;
		do {
			for (int i = 0; i < 8; i++)
				image.push_back({});
			Tile* r = topleft;
			do {
				for (int y = 1; y < 9; y++) {
					for (int x = 1; x < 9; x++) {
						image[depth * 8 + y - 1].push_back(r->data[y][x]);
					}
				}
				cout << r->id << " ";
				r = r->right;
			} while (r);
			cout << endl;
			depth++;
			topleft = topleft->bot;
		} while (topleft);

		result = findmonsters(image);
		//for (auto& v : image) {
		//	for (auto c : v) {
		//		cout << c;
		//	}
		//	cout << endl;
		//}
		//tiles[0].rotate();
		//cout << endl;
		//tiles[0].flipx();
		//cout << num << endl;
		//cout << tiles.size() << endl;
	}
	else {
		cout << "failed loading file\n";
	}

	return result;
}


int main() {
	cout << func() << endl;
}