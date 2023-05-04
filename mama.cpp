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

const ll MOD = 1e9;

struct Node {
	ll cnt = 0;
	ll val = 0;
};

struct SegmentTree {
	int size;
	vector <Node> Tree;
	Node Neutral;

	void init(int n) {
		Neutral.cnt = 0;
		Neutral.val = 0;
		Tree.resize(4 * n, Neutral);
	}

	Node merge(Node a, Node b) {
		Node ret;
		ret.cnt = (a.cnt % MOD + b.cnt % MOD) % MOD;
		ret.val = (a.val % MOD + b.val % MOD) % MOD;
		return ret;
	}

	void update(int id, int lx, int rx, int i, ll k) {
		if (lx > i || rx < i) return;
		if (lx == rx) {
			Tree[id].cnt = (Tree[id].cnt % MOD + 1) % MOD;
			Tree[id].val = (Tree[id].val % MOD + k % MOD) % MOD;
			return;
		}

		int mx = (lx + rx) >> 1;
		update(2 * id, lx, mx, i, k);
		update(2 * id + 1, mx + 1, rx, i, k);

		Tree[id] = merge(Tree[2 * id], Tree[2 * id + 1]);
	}

	Node query(int id, int lx, int rx, int u, int v) {
		if (lx > v || rx < u) return Neutral;
		if (lx >= u && rx <= v) return Tree[id];

		int mx = (lx + rx) >> 1;
		Node x = query(2 * id, lx, mx, u, v);
		Node y = query(2 * id + 1, mx + 1, rx, u, v);

		return merge(x, y);
	}

	void update(int i, ll k) {
		update(1, 1, size, i, k);
	}

	Node query(int l, int r) {
		return query(1, 1, size, l, r);
	}
};

int n;
vector <pll> a;

void discrete(vector <pll> &a) {
	vector <pll> b = a;
	sort(all(b));
	map <ll, ll> mp;
	for (int i = 1; i <= n; ++i) {
		if (mp[b[i].st] == 0) mp[b[i].st] = i;
	}
	for (int i = 1; i <= n; ++i) {
		a[i].nd = mp[a[i].st];
	}
	mp.clear();
}

void solve() {
	cin >> n;
	a.resize(n + 1, {0, 0});
	for (int i = 1; i <= n; ++i) cin >> a[i].st;
	discrete(a);

	SegmentTree St;
	St.size = n;
	St.init(n);

	ll res = 0;
	for (int i = 1; i <= n; ++i) {
		Node q = St.query(a[i].nd, n);
		res += (q.val - ((a[i].st * q.cnt) % MOD) + MOD) % MOD;

		res %= MOD;
		St.update(a[i].nd, a[i].st);
	}

	cout << res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t = 1;
	while (t--) {
		solve();
	}

	return 0;
}
