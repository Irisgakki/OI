#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1e6+7;
const int inf = 0x3f3f3f3f;

inline LL read() {
	register LL x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m;
int a[maxn], pre[maxn], last[maxn], cost[maxn];
LL maxx[maxn << 2], tag[maxn << 2];

#define lson o << 1
#define rson o << 1 | 1
inline void push_up(int o) {
	maxx[o] = std::max(maxx[lson], maxx[rson]);
}

inline void push_down(int o){
	if(tag[o]) {
		maxx[lson] += tag[o];
		maxx[rson] += tag[o];
		tag[lson] += tag[o];
		tag[rson] += tag[o];
		tag[o] = 0;
	}
}

inline void modify(int o, int ql, int qr, int l, int r, int v) {
	if(ql <= l &&  r <= qr) {
		maxx[o] += v;
		tag[o] += v;
		return ;
	}
	push_down(o);
	int mid = l + r >> 1;
	if(ql <= mid) modify(lson, ql, qr, l, mid, v);
	if(qr > mid) modify(rson, ql, qr, mid + 1, r, v);
	push_up(o);
}

inline LL query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		return maxx[o];
	}
	push_down(o);
	LL ans = 0;
	int mid = l + r >> 1;
	if(ql <= mid) ans = std::max(ans, query(lson, ql, qr, l, mid));
	if(qr > mid) ans = std::max(ans, query(rson, ql, qr, mid + 1, r));
	return ans; 
}

#undef lson
#undef rson

int main(){
	//printf("%lld\n", sizeof(cost) / 1024 / 1024);
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i) cost[i] = read();
	for(int i = 1; i <= n; ++i) pre[i] = last[a[i]], last[a[i]] = i;
	//build(1, 1, n);
	LL ans = 0;
	for(int i = 1; i <= n; ++i){
		modify(1, pre[i] + 1, i, 1, n, cost[a[i]]);
		if(pre[i]) modify(1, pre[pre[i]] + 1, pre[i], 1, n, -cost[a[i]]);
		ans = std::max(ans, query(1, 1, i, 1, n));
	}
	printf("%lld\n", ans);
	return 0;
}