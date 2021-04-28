/*
union-find : weighted quick-union
if a, b connected => get_root(a) == get_root(b)

is_connected(): takes time proportional to depth of p and q O(logN)
connect(): take constant time, given roots (without roots O(logN))
*/
#include <iostream>

#include <vector>
using namespace std;

typedef struct union_find {
	int n;
	vector<int> parent, size;
	union_find(int n) : n(n) {
		size.resize(n, 1);
		parent.resize(n);
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	/*union_find(int n) : n(n) {
		size.resize(n, 1);
		parent.reserve(n);
		for (int i = 0; i < n; i++)
			parent.push_back(i);
	}*/
	int get_root(int idx) {
		int root = parent[idx];
		while (root != parent[root])
			root = parent[root];
		return root;
	}
	bool is_connected(int a, int b) {
		return get_root(a) == get_root(b);
	}
	void connect(int a, int b) {
		if (!is_connected(a, b)) {
			int a_root = get_root(a),
				b_root = get_root(b);
			if (size[a_root] >= size[b_root]) {
				parent[b_root] = a_root;
				size[a_root] += size[b_root];
			}
			else {
				parent[a_root] = b_root;
				size[b_root] += size[a_root];
			}
		}
	}
};


int main() {
	int n = 10;
	
	union_find uf(n);

	uf.connect(0, 1);
	uf.connect(0, 2);

	uf.connect(3, 4);
	uf.connect(4, 5);
	uf.connect(5, 6);

	uf.connect(7, 9);
	uf.connect(8, 9);
	
	cout << "1, 2 : " << uf.is_connected(1, 2)<<'\n';
	cout << "1, 3 : " << uf.is_connected(1, 3) << '\n';

	uf.connect(0, 6);
	cout << "1, 3 : " << uf.is_connected(1, 3) << '\n';
	cout << "1, 9 : " << uf.is_connected(1, 9) << '\n';

	uf.connect(2, 7);
	cout << "1, 9 : " << uf.is_connected(1, 9) << '\n';
}