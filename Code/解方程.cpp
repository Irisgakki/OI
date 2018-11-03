#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
#define int long long
const int maxn = 101000;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=((((x<<2)+x)<<1)+(ch^'0'))%mod;
	return x*g;
}

int n, m, a[maxn];
int flag = 0, ans = 0, b[maxn], top = 0;

inline bool check(int x) {
	int sum = 0;
	for(int i = n; i >= 1; --i) {
		sum = ((sum + a[i]) * x) % mod;
	}
	sum = (sum + a[0]) % mod;
	return !sum;
}

signed main() {
	n = read(), m = read();
	rep(i, 0, n) a[i] = read();
	rep(i, 1, m) {
		if(check(i)){
			flag = 1;
			b[++top] = i;
		}
	}
	if(!flag) return printf("0\n"), 0;
	printf("%lld\n", top);
	rep(i, 1, top) {
		printf("%lld\n", b[i]);
	}
	return 0;
}