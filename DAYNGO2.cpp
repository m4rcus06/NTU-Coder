#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define st first
#define nd second

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct Node {
	int total = 0; //sum of '(' and ')'
	int open = 0; //number of invalid '('
	int close = 0; //number of invalid ')'
};
//mark '(' as 1 and ') as -1
//reason: idk lol but it works well

struct SegmentTree {
	int size;
	vector <Node> Tree;
	Node Neutral;

	void init(int n) {
		Tree.resize(4 * n, Neutral);
	}
//for C++ 11 bruh
	Node compute(char a) {
		Node ret;
		if (a == '(') {
			ret.total = 1;
			ret.open = 1;
		}
		else {
			ret.total = -1;
			ret.close = -1;
		}
		return ret;
	}

	Node merge(Node &a, Node &b) {
		Node c;
		c.total = a.total + b.total;
		c.open = max(0, a.open + b.close) + b.open; //the max() is incase of a.op + b.op < 0, here we only count the invalid'('
		c.close = min(0, a.open + b.close) + a.close; //same here
		return c;
	}

	void build(int id, int lx, int rx, string &s) {
		if (lx == rx) {
			Tree[id] = compute(s[lx - 1]);
			return;
		}

		int mx = (lx + rx) >> 1;
		build(2 * id, lx, mx, s);
		build(2 * id + 1, mx + 1, rx, s);

		Tree[id] = merge(Tree[2 * id], Tree[2 * id + 1]);
	}

	Node get(int id, int lx, int rx, int u, int v) {
		if (lx > v || rx < u) return Neutral;
		if (lx >= u && rx <= v) return Tree[id];

		int mx = (lx + rx) >> 1;
		Node x = get(2 * id, lx, mx, u, v);
		Node y = get(2 * id + 1, mx + 1, rx, u, v);

		return merge(x, y);
	}

	void build(string &s) {
		build(1, 1, size, s);
	}

	bool valid(int l, int r) {
		Node x = get(1, 1, size, l, r);
		return (x.total == 0 && x.open == 0 && x.close == 0);
	}
};

void solve() {
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;

	SegmentTree St;
	St.size = n;
	St.init(n);
	St.build(s);
	while (m--) {
		int lx, rx;
		cin >> lx >> rx;
		cout << ((St.valid(lx, rx)) ? "YES" : "NO") << '\n';
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t = 1;
	while (t--) {
		solve();
	}

	return 0;
}
