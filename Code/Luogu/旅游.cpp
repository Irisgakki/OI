#include <bits/stdc++.h>
#define rr register
typedef long long LL;
const int maxn = 500010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m, ans;
int d[maxn], f[maxn], du[maxn];
struct Edge{
	int next, to, size;
}e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) { e[++cnt] = (Edge) {head[u], v, w}; head[u] = cnt; }
inline void ins(int u, int v, int w) { add(u, v, w); add(v, u, w); }
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
inline void merge(int x, int y) { f[find(y)] = find(x); }

inline void dfs(int now, int fa, int w) {
	for(rr int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == fa) continue;
		dfs(to, now, e[i].size);
	}
	if(du[now]) {
		du[fa] ^= 1;
		ans = (ans + d[w]) % mod;
	}
}

int main() {
	n = read(), m = read();
	d[0] = 1;
	for(rr int i = 1; i <= m; ++i) d[i] = (d[i - 1] << 1) % mod;
	for(rr int i = 1; i <= m; ++i) f[i] = i;
	ans = ((d[m] << 1) - 2) % mod;
	for(rr int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		du[u] ^= 1; du[v] ^= 1;
		if(find(u) != find(v)) {
			merge(u, v);
			ins(u, v, i);
		}
	}
	dfs(1, 0, 0);
	printf("%d", ans);
	return 0;
}