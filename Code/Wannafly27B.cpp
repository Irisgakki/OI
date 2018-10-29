#include <bits/stdc++.h>
#define int long long
const int maxn = 101000;
const int inf = 1e18;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m, flag = 0;
int col[maxn];
struct Edge{
	int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) { e[++cnt] = (Edge) {head[u], v}; head[u] = cnt; }
inline void ins(int u, int v) { add(u, v); add(v, u); }

inline void dfs(int now){
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(col[to] && col[now] == col[to]) flag = 1;
		if(col[to]) continue;
		if(col[now] == 1) col[to] = -1;
		if(col[now] == -1) col[to] = 1;
		dfs(to);
	}
}

signed main(){
	memset(col, 0, sizeof(col));
	n = read(), m = read();
	if(!m) return printf("0\n"), 0;
	for(int i = 1; i <= m; ++i){
		int u = read(), v = read();
		ins(u, v);
	}
	col[1] = 1;
	dfs(1);
	flag == 1 ? printf("3\n") : printf("2\n");
	return 0;
}