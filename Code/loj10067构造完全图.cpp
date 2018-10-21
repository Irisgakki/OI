#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 300010;
const int inf = 1 << 30;
const int mod = 1000000007;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n;
struct Edge{
	int from, to;
	LL val;
	friend bool operator < (const Edge &a, const Edge &b) {
		return a.val < b.val;
	}
}e[maxn << 1];

int f[maxn], cnt[maxn];
LL ans = 0;
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main() {
	n = read();
	for(rg int i = 1; i <= n - 1; ++i) {
		e[i].from = read(); e[i].to = read(); e[i].val = read();
		ans += e[i].val;
	}
	std::sort(e + 1, e + n);
	for(rg int i = 1; i <= n; ++i) f[i] = i, cnt[i] = 1;
	for(rg int i = 1; i <= n - 1; ++i) {
		int u = find(e[i].from), v = find(e[i].to);
		if(u != v) {
			ans += (LL)(cnt[u] * cnt[v] - 1) * (LL)(e[i].val + 1);
			f[v] = u;
			cnt[u] += cnt[v];
		}
	}
	printf("%lld", ans);
	return 0;
}