#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int inf = 1 << 30;
const int maxn = 100010;
const int mod = 31011;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m;
struct Edge{
	int from, to, val;
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.val < b.val;
	}
} e[maxn << 1];

struct Node{
	int s, t, w;
} t[maxn];
int cnt = 0, sum = 0, ans = 1;

int F[maxn];
inline int find(int x) { return x == F[x] ? x : find(F[x]); }

inline void dfs(int x, int now, int k) {
	if(now == t[x].t + 1) {
		if(k == t[x].w) sum++;
		return ;
	}
	int u = find(e[now].from), v = find(e[now].to);
	if(u != v) {
		F[u] = v;
		dfs(x, now + 1, k + 1);
		F[u] = u; F[v] = v;
	}
	dfs(x, now + 1, k);
}

int main() {
	n = read(), m = read();
	for(rg int i = 1; i <= m; ++i) {
		e[i].from = read(), e[i].to = read(), e[i].val = read();
	}
	std::sort(e + 1, e + m + 1);
	int k = 0;
	for(rg int i = 1; i <= n; ++i) F[i] = i;
	for(rg int i = 1; i <= m; ++i) {
		if(e[i].val != e[i - 1].val) {
			t[++cnt].s = i;
			t[cnt - 1].t = i - 1;
		}
		int x = find(e[i].from), y = find(e[i].to);
		if(x != y) {
			F[x] = y;
			t[cnt].w++;
			k++;
		}
	}
	t[cnt].t = m;
	if(k != n - 1) 
		return printf("0\n"), 0;
	for(rg int i = 1; i <= n; ++i) F[i] = i;
	for(rg int i = 1; i <= cnt; ++i) {
		sum = 0;
		dfs(i, t[i].s, 0);
		ans = (ans * sum) % mod;
		for(rg int j = t[i].s; j <= t[i].t; ++j) {
			int x = find(e[j].from), y = find(e[j].to);
			if(x != y) F[x] = y;
		}
	}
	printf("%d", ans % mod);
	return 0;
}