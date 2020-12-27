#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;
struct pos {
	int x;
	int y;
	int z;
	int w;

	bool operator==(const pos& o) const {
		return x == o.x && y == o.y && z == o.z && w == o.w;
	}

	bool operator<(const pos& o) const {
		if (x != o.x) {
			if (x < o.x)
				return true;
			else
				return false;
		}

		if (y != o.y) {
			if (y < o.y)
				return true;
			else
				return false;
		}

		if (z != o.z) {
			if (z < o.z)
				return true;
			else
				return false;
		}

		if (w < o.w)
			return true;

		return false;
	}
};

class MyHashFunction {
public:

	// Use sum of lengths of first and last names 
	// as hash function. 
	size_t operator()(const pos& p) const
	{
		return p.x * (long long)10000 + p.y * (long long)100 + (long long)p.z + (long long)p.w * 1000000;
	}
};



//####.#.#
//#...####
//..#.#.#.
//####.#..
//#.#.#..#
//.####.##
//..#...##

//vector<vector<vector<char>>> loop(const vector<vector<vector<char>>>& map) {
//	vector<vector<vector<char>>> newmap = map;
//
//	for (int z = 0; z < map.size(); z++) {
//		for (int y = 0; y < map[z].size(); y++) {
//			for (int x = 0; x < map[z][y].size(); x++) {
//				int counthash = 0;
//
//				for (int zz = -1; zz < 2; zz++) {
//					for (int yy = -1; yy < 2; yy++) {
//						for (int xx = -1; xx < 2; xx++) {
//							if (xx == 0 && yy == 0 && zz == 0)
//								continue;
//
//							int xxx = x + xx;
//							int yyy = y + yy;
//							int zzz = z + zz;
//
//							if (xxx < 0 || yyy < 0 || zzz < 0 || xxx >= map[z][y].size() || yyy >= map[z].size() || zzz >= map.size())
//								continue;
//
//							if (map[zzz][yyy][xxx] == '#')
//								counthash++;
//						}
//					}
//				}
//
//
//				if (map[z][y][x] == '#') {
//					if (counthash == 2 || counthash == 3) {
//						// stay active
//					}
//					else {
//						newmap[z][y][x] = '.';
//					}
//				}
//				else {
//					if (counthash == 3) {
//						newmap[z][y][x] = '#';
//					}
//				}
//			}
//		}
//	}
//
//	return newmap;
//}

set<pos> loop(set<pos>& map) {
	set<pos> newmap;

	for (int x = -15; x <= 15; x++) {
		for (int y = -15; y <= 15; y++) {
			for (int z = -8; z <= 8; z++) {
				for (int w = -8; w <= 8; w++) {
					int counthash = 0;

					for (int ww = -1; ww < 2; ww++) {
						for (int zz = -1; zz < 2; zz++) {
							for (int yy = -1; yy < 2; yy++) {
								for (int xx = -1; xx < 2; xx++) {
									if (xx == 0 && yy == 0 && zz == 0 && ww == 0)
										continue;

									int xxx = x + xx;
									int yyy = y + yy;
									int zzz = z + zz;
									int www = w + ww;

									auto found = map.find({ xxx,yyy,zzz, www });
									if (found == map.end())
										continue;

									counthash++;

									if (counthash > 3)
										break;
								}
								if (counthash > 3)
									break;
							}
							if (counthash > 3)
								break;
						}
						if (counthash > 3)
							break;
					}

					auto found = map.find({ x,y,z, w });
					if (found != map.end()) {
						if (counthash == 2 || counthash == 3) {
							newmap.insert({x, y, z, w});
						}
						else {
							//newmap[{x, y, z, w}] = '.';
						}
					}
					else {
						if (counthash == 3) {
							newmap.insert({x, y, z, w});
						}
					}
				}
			}
		}
	}

	return newmap;
}

void expand(unordered_map<pos, char, MyHashFunction>& map) {
	int minx = 0, maxx = 0, miny = 0, maxy = 0, minz = 0, maxz = 0, minw = 0, maxw = 0;

	for (auto& p : map) {
		if (p.second == '#') {
			if (p.first.x < minx)
				minx = p.first.x;
			if (p.first.x > maxx)
				maxx = p.first.x;

			if (p.first.y < miny)
				miny = p.first.y;
			if (p.first.y > maxy)
				maxy = p.first.y;

			if (p.first.z < minz)
				minz = p.first.z;
			if (p.first.z > maxz)
				maxz = p.first.z;

			if (p.first.w < minw)
				minw = p.first.w;
			if (p.first.w > maxw)
				maxw = p.first.w;
		}
	}

	for (int w = minw - 1; w <= maxw + 1; w++) {
		for (int z = minz - 1; z <= maxz + 1; z++) {
			for (int y = miny - 1; y <= maxy + 1; y++) {
				for (int x = minx - 1; x <= maxx + 1; x++) {
					auto found = map.find({ x,y,z, w });
					if (found == map.end())
						map[{x, y, z, w}] = '.';
				}
			}
		}
	}
}

long long func() {
	long long result = 0;
	//vector<vector<vector<char>>> map;
	//unordered_map<pos, bool, MyHashFunction> umap;
	set<pos> map;
	
	//for (int z = 0; z < 20; z++) {
	//	for (int y = 0; y < 20; y++) {
	//		for (int x = 0; x < 20; x++)
	//			umap[{x, y, z}] = '.';
	//	}
	//}

//##...#.#
//####.#.#
//#...####
//..#.#.#.
//####.#..
//#.#.#..#
//.####.##
//..#...##
	vector<vector<char>> start({
			{ '#','#','.','.','.','#','.','#',},
			{ '#','#','#','#','.','#','.','#',},
			{ '#','.','.','.','#','#','#','#', },
			{ '.','.','#','.','#','.','#','.',},
			{ '#','#','#','#','.','#','.','.', },
			{ '#','.','#','.','#','.','.','#', },
			{ '.','#','#','#','#','.','#','#', },
			{ '.','.','#','.','.','.','#','#', }, });
	for (int y = 0; y < start.size(); y++) {
		for (int x = 0; x < start[y].size(); x++) {
			if (start[y][x] == '#')
				map.insert({ x,y,0,0 });
		}
	}

	//for (int z = -6; z <= 6; z++) {
	//	if (z == 0) {
	//		map.push_back({
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','#','#','.','.','.','#','.','#','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','#','.','.','.','#','#','#','#','.','.','.','.','.','.', },
	//			{'.','.','.','.','.','.', '.','.','#','.','#','.','#','.','.','.','.','.','.','.', },
	//			{ '.','.','.','.','.','.','#','#','#','#','.','#','.','.','.','.','.','.','.','.', },
	//			{ '.','.','.','.','.','.','#','.','#','.','#','.','.','#','.','.','.','.','.','.', },
	//			{ '.','.','.','.','.','.','.','#','#','#','#','.','#','#','.','.','.','.','.','.', },
	//			{ '.','.','.','.','.','.','.','.','#','.','.','.','#','#','.','.','.','.','.','.', },
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',},
	//			{ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.',}, });
	//		continue;
	//	}
	//	vector<vector<char>> temp;
	//	for (int y = -6; y <= 8 + 6; y++) {
	//		temp.push_back({ '.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.', });
	//	}
	//	map.push_back(temp);
	//}

	for (int i = 0; i < 6; i++) {
		//expand(umap);
		map = loop(map);
		cout << "loop\n";
	}

	//for (auto& a : map) {
	//	for (auto& b : a) {
	//		for (auto c : b) {
	//			if (c == '#')
	//				result++;
	//		}
	//	}
	//}

	//for (auto& p : umap) {
	//	if (p.second == '#')
	//		result++;
	//}

	result = map.size();

	return result;
}


int main() {
	cout << func() << endl;
}