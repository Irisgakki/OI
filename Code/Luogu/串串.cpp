#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 100010;
const int inf = 1 << 30;
const int mod = 1000000007;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int a, b, c, d;
LL fac[maxn], inv[maxn], ans;

inline LL qpow(LL a, LL n) {
	if(n == 0) return 1;
	LL res = 1;
	while(n) {
		if(n & 1) res = (res * a) % mod;
		n >>= 1;
		a = (a * a) % mod;
	}
	return res;
}

inline void init() {
	fac[0] = inv[0] = 1;
	for(rg int i = 1; i <= 10000; ++i) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = qpow(fac[i], mod - 2);
	}
}

inline LL C(LL m, LL n) {
	if(n > m) return 0;
	return fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main() {
	a = read(), b = read(), c = read(), d = read();
	init();
	if(c == 0 || d == 0) {
		ans = C(a + b, a);
		printf("%lld\n", ans);
		return 0;
	}
	ans = 0;
	for(rg int i = 0; i <= a - c; ++i)
		for(rg int j = 0; j <= b - d; ++j)
			ans = (ans + C(a - c - i + d - 1, d - 1) * C(b - d - j + c - 1, c - 1) % mod * C(i + j, i) % mod) % mod;
	ans = ans * C(c + d, c) % mod;
	printf("%lld\n", ans);
	return 0;
}