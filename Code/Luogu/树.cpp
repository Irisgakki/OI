#include <bits/stdc++.h>
#define rr register
typedef long long ll;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;

inline int read() {
	register int x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') {x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, q;
struct tree{
	int next, to;
}e[maxn << 1];
int cnt = 0, head[maxn];

inline void add(int u, int v) {
	e[++cnt].next = head[u];
	e[cnt].to = v;
	head[u] = cnt;
}
inline void ins(int u, int v) {
	add(u, v);
	add(v, u);
}

int dep[maxn], anc[maxn][31], lgn;

inline void cal_anc() {
	for(int j = 1; (1 << j) <= n; ++j) 
		for(int i = 1; i <= n; ++i)
			anc[i][j] = anc[anc[i][j-1]][j-1];
}

inline void dfs(int now) {
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now][0]) continue;
		dep[to] = dep[now] + 1;
		anc[to][0] = now;
		dfs(to);
	}
}

inline int lca(int x, int y) {
	if(dep[x] > dep[y]) std::swap(x, y);
	int del = dep[y] - dep[x];
	for(int i = 0; (1 << i) <= del; ++i)
		if((1 << i) & del)
			y = anc[y][i];
	if(x == y) return x;
	for(int i = lgn; i >= 0; --i) {
		if(anc[x][i] != anc[y][i]) {
			x = anc[x][i];
			y = anc[y][i];
		}
	}
	return anc[x][0];
}

int main() {
	n = read();
	for(rr int i = 1; i <= n - 1; ++i) {
		ins(read(), read());
	}
	dfs(1);
	cal_anc();
	q = read();
	while(q--) {
		int opt = read(), x, y, col1;
		if(opt == 1) {
			x = read(), y = read(), col1 = read();
			if(col1 != 0) printf("0\n");
			else printf("%d\n", dep[x] + dep[y] - 2 * dep[lca(x, y)]);
		}
		else printf("ORZ\n");
	}
	return 0;
}