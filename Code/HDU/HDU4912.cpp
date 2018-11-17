#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

const int maxn = 1e5 + 7;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

int n, m;
struct Edge{
	int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;

struct Road{
	int from, to, LCA, depth;
	friend bool operator < (Road a, Road b) {
		return a.depth > b.depth;
	}
} r[maxn];
int vis[maxn];

inline void add(int u, int v) {
	e[++cnt].next = head[u];
	e[cnt].to = v;
	head[u] = cnt;
}

inline void ins(int u, int v) {
	add(u, v); add(v, u);
}

int dep[maxn], anc[maxn][30];

inline void dfs1(int now) {
	for(register int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now][0]) continue;
		dep[to] = dep[now] + 1;
		anc[to][0] = now;
		dfs1(to);
	}
}

inline void cal() {
	for(int j = 1; (1 << j) <= n; ++j) 
		for(int i = 1; i <= n; ++i)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
}

inline int lca(int x, int y) {
	if(dep[x] > dep[y]) std::swap(x, y);
	int del = dep[y] - dep[x];
	for(register int i = 0; (1 << i) <= del; ++i)
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

inline void dfs(int now) {
	vis[now] = 1;
	for(register int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now][0] || vis[to]) continue;
		dfs(to);
	}
}

int main(){
	while(scanf("%d %d", &n, &m) != EOF) {
		memset(head, 0, sizeof(head));
		cnt = 0;
		for(int i = 1; i <= n - 1; ++i) {
			int u = read(), v = read();
			ins(u, v);
		}
		dfs1(1); cal();
		for(int i = 1; i <= m; ++i) {
			int u = read(), v = read();
			int l = lca(u, v);
			r[i].from = u;
			r[i].to = v;
			r[i].LCA = l;
			r[i].depth = dep[l];
		}
		std::sort(r + 1, r + m + 1);
		int ans = 0;
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= m; ++i) {
			if(vis[r[i].from] || vis[r[i].to]) continue;
			dfs(r[i].LCA);
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}