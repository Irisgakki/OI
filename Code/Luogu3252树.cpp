#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n, s, a[maxn];
struct Edge{
	int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;
int anc[maxn], ans = 0;

inline void add(int u, int v) { e[++cnt] = (Edge){head[u], v}; head[u] = cnt; }
inline void ins(int u, int v) { add(u, v); add(v, u); }

inline void dfs(int now, int sum) {
	if(sum > s) return ;
	if(sum == s) {
		ans++;
		return ;
	}
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to == anc[now]) continue;
		dfs(to, sum + a[to]);
	}
	return ;
}

int main() {
	scanf("%d %d", &n, &s);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n - 1; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		ins(u, v);
		anc[v] = u;
	}
	for(int i = 1; i <= n; ++i) {
		dfs(i, a[i]);
	}
	printf("%d\n", ans);
	return 0;
}
