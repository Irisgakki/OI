#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 100010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m;
struct Edge{
	int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;
int out[maxn], vis[maxn];
double dp[maxn];

inline void add(int u, int v, int w) {
	e[++cnt] = (Edge){head[u], v, w};
	head[u] = cnt;
	++out[u];
}

inline void dfs(int now) {
	if(!vis[now]) vis[now] = 1;
	else return ;
	for(rg int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		dfs(to);
		dp[now] += dp[to] + e[i].val;
	}
	if(out[now]) dp[now] /= out[now];
}

int main() {
	n = read(), m = read();
	for(rg int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		add(u, v, w);
	}
	dfs(1);
	printf("%.2lf", dp[1]);
	return 0;
}