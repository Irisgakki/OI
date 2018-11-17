#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 5000;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, m;
LL tr[maxn][maxn];

inline int lowbit(int x) {return x & -x;}
inline void add(int x, int y, int k) {
	while(x <= n) {
		for(int i = y; i <= m; i += lowbit(i)) {
			tr[x][i] += k;
		}
		x += lowbit(x);
	}
}
inline LL sum(int x, int y) {
	LL ans = 0;
	while(x > 0) {
		for(int i = y; i >= 1; i -= lowbit(i)){
			ans += tr[x][i];
		}
		x -= lowbit(x);
	}
	return ans;
}
inline LL query(int a, int b, int c, int d) {
	return sum(c, d) + sum(a - 1, b - 1) - sum(c, b - 1) - sum(a - 1, d);
}

int main() {
	n = read(), m = read();
	int opt;
	while(scanf("%d", &opt) != EOF) {
		int x, y, k, a, b, c, d;
		if(opt == 1){
			x = read(), y = read(), k = read();
			add(x, y, k);
		} else {
			a = read(), b = read(), c = read(), d = read();
			printf("%lld\n", query(a, b, c, d));
		}
	}
	return 0;
}