#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1e7+9;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline LL mul(LL a, LL b) {
	LL res = 0;
	while(b) {
		if(b & 1) res = (res + a) % mod;
		b >>= 1;
		a = (a + a) % mod; 
	} 
	return res;
}

inline LL qpow(LL a, LL n) {
	if(n == 0) return 1;
	LL res = 1;
	while(n) {
		if(n & 1) res = mul(res, a) % mod;
		n >>= 1;
		a = mul(a, a) % mod;
	}
	return res;
}

LL n, g, l;
LL p[maxn], top = 0, ans = 1;

inline void sieve(LL x) {
	for(LL i = 2; i * i <= x; ++i) {
		if(!(x % i)) {
			top++;
			while(!(x % i)) {
				p[top]++;
				x /= i;
			}
		}
	}
	if(x != 1) p[++top] = 1;
}

int main() {
	scanf("%lld %lld %lld", &n, &g, &l);
	if(l % g != 0) return printf("0\n"), 0;
	l = l / g;
	g = 1;
	sieve(l);
	for(int i = 1; i <= top; ++i) {
		LL tmp = qpow(p[i] + 1, n) - qpow(p[i], n) - qpow(p[i], n) + qpow(p[i] - 1, n);
		tmp = (tmp % mod + mod) % mod;
		ans = mul(ans, tmp);
	}
	printf("%lld\n", ans);
	return 0;
}