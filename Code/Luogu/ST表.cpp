#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n, m, a[maxn];
int st[maxn][31];

inline int query(int l, int r) {
	int k = log2(r - l + 1);
	return std::max(st[l][k], st[r - (1 << k) + 1][k]);
}

inline void ST() {
	for(int j = 1; j <= 30; ++j) {
		for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[i][j] = std::max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		st[i][0] = a[i];
	}
	ST();
	while(m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", query(l, r));
	}
	return 0;
}