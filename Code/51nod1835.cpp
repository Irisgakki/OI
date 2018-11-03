#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

typedef long long LL;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

inline LL read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void print(LL x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

inline LL fpow(LL a, LL n) {
	if(n == 0) return 1;
	LL res = 1;
	while(n) {
		if(n & 1) res = (res * a) % mod;
		n >>= 1;
		a = (a * a) % mod;
	}
	return res;
}

LL n, m;
LL fac[maxn], inv[maxn];
LL dp[maxn][maxn], tmp1, tmp2;

inline void init() {
	fac[0] = 1;
	for(int i = 1; i < maxn; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[maxn - 1] = fpow(fac[maxn - 1], mod - 2);
	for(int i = maxn - 2; i >= 0; --i) inv[i] = (inv[i + 1] * (i + 1)) % mod;
}

inline LL C(LL m, LL n) {
	if(n > m) return 0;
	return fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main(){
	init();
	n = read(), m = read();
	dp[1][1] = 1;
	for(int i = 2; i <= n; ++i) {
		for(int j = 2; j <= i; ++j) {
			dp[i][j] = 0;
			for(int k = 1; k <= i - (j - 1); ++k) {
				(dp[i][j] += C(i - 1, k - 1) * dp[k][1] % mod * dp[i - k][j - 1] % mod) %= mod;
			}
		}
		dp[i][1] = fpow(2, i * (i - 1) / 2);
		for(int k = 2; k <= i; ++k)
			dp[i][1] = (dp[i][1] - dp[i][k] + mod) % mod;
	}
	if(m == 1) print((dp[n][1] - 1) % mod);
	else print(dp[n][m] % mod);
	return 0;
}