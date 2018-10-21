#include <bits/stdc++.h>
#define rr register
const int maxn = 1000010;
const int inf = 1 << 30;
const int mod = 998244353;

inline LL read() {
	register LL x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') {x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

LL n, m;
LL d[maxn];
struct Edge{
	LL next, to, dis;
}e[maxn << 1];
LL head[maxn], cnt = 0;

inline void add(LL u, LL v, LL w) { e[++cnt] = (Edge){head[u], v, w}; head[u] = cnt; }

inline void dfs(int now) {
	
}

int main() {
	n = read(), m = read();
	d[0] = 1;
	for(rr int i = 1; i <= m; ++i)
		d[i] = (d[i - 1] * 29) % mod;
	for(rr int i = 1; i <= m; ++i)
		add(read(), read(), read());
	for(rr int i = 1; i <= n; ++i) {
		dfs(i);

	}
	return 0;
}