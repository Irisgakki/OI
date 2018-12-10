#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int n, q, root, f;
int val[maxn];
struct Edge{
	int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) {
	e[++cnt].next = head[u];
	e[cnt].to = v;
	head[u] = cnt;
}

int in[maxn], out[maxn], id = 0, a[maxn], dep[maxn];
int anc[maxn][30];
inline void dfs(int now) {
	in[now] = ++id;
	a[id] = now;
	for(int i = 1; i <= 16; ++i)
		if(dep[now] < (1 << i)) break;
		else anc[now][i] = anc[anc[now][i - 1]][i - 1];
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now][0]) continue;
		anc[to][0] = now;
		dep[to] = dep[now] + 1;
		dfs(to);
	}
	out[now] = id;
}

struct Segment{
	int l, r, minn;
} seg[maxn << 2];

#define lson o << 1
#define rson o << 1 | 1

inline void push_up(int o) {
	seg[o].minn = std::min(seg[lson].minn, seg[rson].minn);
}

inline void build(int o, int l, int r) {
	seg[o].l = l, seg[o].r = r;
	if(l == r) {
		seg[o].minn = val[a[l]];
		return ;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid); build(rson, mid + 1, r);
	push_up(o);
}

inline void modify(int o, int p, int v) {
	if(seg[o].l == seg[o].r) {
		seg[o].minn = v;
		return ;
	}
	int mid = (seg[o].l + seg[o].r) >> 1;
	if(p <= mid) modify(lson, p, v);
	if(p > mid) modify(rson, p, v);
	push_up(o);
}

inline int query(int o, int l, int r) {
	if(l <= seg[o].l && seg[o].r <= r) {
		return seg[o].minn;
	}
	int ans = inf;
	int mid = (seg[o].l + seg[o].r) >> 1;
	if(l <= mid) ans = std::min(ans, query(lson, l, r));
	if(r > mid) ans = std::min(ans, query(rson, l, r));
	return ans;
}

int main() {
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d", &f, &val[i]);
		if(f) add(f, i), add(i, f);
	}
	dfs(root = 1);
	build(1, 1, n);
	while(q--) {
		char opt[5];
		scanf("%s", opt);
		if(opt[0] == 'V') {
			int x, y;
			scanf("%d %d", &x, &y);
			modify(1, in[x], y);
		}
		if(opt[0] == 'E') {
			int x;
			scanf("%d", &x);
			root = x;
		}
		if(opt[0] == 'Q') {
			int x;
			scanf("%d", &x);
			if(x == root) {
				printf("%d\n", seg[1].minn);
			} else if(in[x] <= in[root] && out[root] <= out[x]) {
				int y = root, del = dep[y] - dep[x] - 1;
				for(int i = 0; i <= 16; ++i)
					if((1 << i) & del) y = anc[y][i];
				printf("%d\n", std::min(query(1, 1, in[y] - 1), query(1, out[y] + 1, n)));
			} else {
				printf("%d\n", query(1, in[x], out[x]));
			}
		}
	}
	return 0;
}
