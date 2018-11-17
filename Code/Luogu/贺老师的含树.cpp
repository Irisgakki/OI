#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int n, q;
struct Edge{
	int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) { e[++cnt] = (Edge){head[u], v}; head[u] = cnt; }
inline void ins(int u, int v) { add(u, v); add(v, u); }

int dep[maxn], anc[maxn][30], in[maxn], out[maxn], id = 0;
inline void dfs(int now) {
	in[now]=++id;
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now][0]) continue;
		dep[to] = dep[now] + 1;
		anc[to][0] = now;
		dfs(to); 
	}
	out[now]=id;
}

inline void cal() {
	for(int j = 1; (1 << j) <= n; ++j) {
		for(int i = 1; i <= n; ++i) {
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
		}
	}
}

inline int lca(int x, int y) {
	if(dep[x] > dep[y]) std::swap(x, y);
	int del = dep[y] - dep[x];
	for(int i = 0; (1 << i) <= del; ++i)
		if((1 << i) & del) y = anc[y][i];
	if(x == y) return x;
	for(int i = 21; i >= 0; --i) {
		if(anc[x][i] != anc[y][i]) {
			x = anc[x][i];
			y = anc[y][i];
		}
 	}
 	return anc[x][0];
}

int sz = 1;
int maxx[maxn << 2], lson[maxn << 2], rson[maxn << 2];
inline void build(int &rt, int p, int l, int r, int v) {
	if(!rt) {//动态开点？ 
		rt = ++sz;
		maxx[rt] = lson[rt] = rson[rt] = 0;
	}
	if(l == p && p == r) {
		maxx[rt] = std::max(maxx[rt], v);
		return ;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) build(lson[rt], p, l, mid, v);
	if(p > mid) build(rson[rt], p, mid + 1, r, v);
	maxx[rt] = std::max(maxx[lson[rt]], maxx[rson[rt]]);
	return ;
}

inline int query(int &rt, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		return maxx[rt];
	}
	int mid = (l + r) >> 1;
	int ans = 0;
	if(ql <= mid) ans = std::max(ans, query(lson[rt], ql, qr, l, mid));
	if(qr > mid) ans = std::max(ans, query(rson[rt], ql, qr, mid + 1,r ));
	return ans;
}

#undef lson
#undef rson

int main() {
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n - 1; ++i) {
		int x;
		scanf("%d", &x);
		ins(i + 1, x);
	}
	dep[1] = 1;
	dfs(1);
	cal();
	while(q--) {
		int opt, x, y;
		scanf("%d", &opt);
		if(opt == 1) {
			scanf("%d %d", &x, &y);
			int L = lca(x, y);
			int v = dep[x] + dep[y] - 2 * dep[lca(x, y)] + 1;
			int rt = 1;
			build(rt, in[L], 1, n, v);
		}
		if(opt == 2) {
			scanf("%d", &x);
			int rt = 1;
			printf("%d\n", query(rt, in[x], out[x], 1, n));
		}
		// int x, y;
		// scanf("%d %d", &x, &y);
		// printf("%d", lca(x, y));
	}
	return 0;
}