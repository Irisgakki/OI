#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 300010;
const LL inf = 1e18;
const int mod = 1000000007;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m;
struct Edge{
	int from, to;
	LL val;
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.val < b.val;
	}
} e[maxn << 1];

int F[maxn], vis[maxn];
inline int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

LL ans = 0, cnt = 0, maxx = inf;

int main() {
	n = read(), m = read();
	for(rg int i = 1; i <= n; ++i) F[i] = i, vis[i] = 0;
	for(rg int i = 1; i <= m; ++i) {
		e[i].from = read(), e[i].to = read(), e[i].val = read();
	}
	std::sort(e + 1, e + m + 1);
	for(rg int i = 1; i <= m; ++i) {
		int u = find(e[i].from), v = find(e[i].to);
		if(u != v) {
			F[v] = u;
			ans += e[i].val;
			vis[++cnt] = i;
			if(cnt == n - 1) break;
		}
	}
	for(rg int i = 1; i <= cnt; ++i) {
		LL sec = 0, tot = 0;
		for(rg int j = 1; j <= n; ++j)
			F[j] = j;
		for(rg int j = 1; j <= m; ++j) {
			if(vis[i] == j) continue;
			int u = find(e[j].from), v = find(e[j].to);
			if(u != v) {
				F[v] = u;
				sec += e[j].val;
				tot++;
				if(tot == n - 1) break;
			}
		}
		//printf("%lld\n", sec);
		if(sec > ans) maxx = std::min(maxx, sec);
	}
	if(maxx == inf) maxx = 10;
	printf("%lld\n", maxx);
	return 0;
}