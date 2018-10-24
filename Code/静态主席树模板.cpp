#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 200010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int a[maxn], b[maxn];
int node_cnt, n, m;
int sum[maxn << 5], lson[maxn << 5], rson[maxn << 5], rt[maxn << 5];
int l, r, k, p, q, ans;

inline void build(int &rt, int l, int r) {
	rt = ++node_cnt;
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lson[rt], l, mid); build(rson[rt], mid + 1, r);
}

inline int modify(int o, int l, int r) {
	int oo = ++node_cnt;
	lson[oo] = lson[o], rson[oo] = rson[o], sum[oo] = sum[o] + 1;
	if(l == r) return oo;
	int mid = l + r >> 1;
	if(p <= mid) lson[oo] = modify(lson[oo], l, mid);
	else rson[oo] = modify(rson[oo], mid + 1, r);
	return oo;
}

inline int query(int u, int v, int l, int r, int k) {
	int ans;
	int mid = l + r >> 1, x = sum[lson[v]] - sum[lson[u]];
	if(l == r) return l;
	if(x >= k) ans = query(lson[u], lson[v], l, mid, k);
	else ans = query(rson[u], rson[v], mid + 1, r, k - x);
	return ans;
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), b[i] = a[i];
	std::sort(b + 1, b + 1 + n);
	q = std::unique(b + 1, b + 1 + n) - b - 1;//去重后的长度
	build(rt[0], 1, q);
	for(int i = 1; i <= n; ++i) {
		p = std::lower_bound(b + 1, b + 1 + q, a[i]) - b;
		rt[i] = modify(rt[i - 1], 1, q);
	}
	for(int i = 1; i <= m; ++i) {
		l = read(), r = read(), k = read();
		ans = query(rt[l - 1], rt[r], 1, q, k);
		printf("%d\n", b[ans]);
	}
	return 0;
}