#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;
const int mod = 1000000007;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m, need;
struct Edge{
	int from, to, val, col;
	friend bool operator < (const Edge &a, const Edge &b) {
		if(a.val == b.val) return a.col < b.col;
		return a.val < b.val;
	}
} e[maxn << 1];
int u[maxn], v[maxn], w[maxn], c[maxn];
int tot, cnt, ans = 0;

int F[maxn];
inline int find(int x) { return x == F[x] ? x : F[x] = find(F[x]); }

inline bool check(int x) {
	tot = cnt = 0;
	for(rg int i = 1; i <= n; ++i) F[i] = i;
	for(rg int i = 1; i <= m; ++i) {
		if(!c[i]) e[i] = (Edge){u[i], v[i], w[i] + x, c[i]};
		else e[i] = (Edge){u[i], v[i], w[i], c[i]};
	}
	std::sort(e + 1, e + m + 1);
	for(rg int i = 1; i <= m; ++i) {
		int u = find(e[i].from), v = find(e[i].to);
		if(u != v) {
			F[v] = u;
			tot += e[i].val;
			if(!e[i].col) cnt++;
		}
	}
	return cnt >= need;
}

int main() {
	n = read(), m = read(), need = read();
	for(rg int i = 1; i <= m; ++i) {
		u[i] = read() + 1, v[i] = read() + 1, w[i] = read(), c[i] = read();
	}
	int l = -inf, r = inf;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) {
			l = mid + 1;
			ans = tot - need * mid;
		} else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}