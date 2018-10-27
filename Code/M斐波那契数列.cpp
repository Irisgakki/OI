#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
typedef long long LL;
const int mod = 1000000007;

LL a, b, n;

struct mat{
	LL m[3][3];
} A, unit;

inline LL qmul(LL a, LL b) {
	LL res = 0;
	while(b) {
		if(b & 1) res = (res + a) % mod;
		b >>= 1;
		a = (a + a) % mod;
	}
	return res;
}

inline mat mul(mat a, mat b) {
	mat c;
	for(int i = 1; i <= 2; ++i)
		for(int j = 1; j <= 2; ++j)
			c.m[i][j] = 0;
	for(int i = 1; i <= 2; ++i)
		for(int j = 1; j <= 2; ++j)
			for(int k = 1; k <= 2; ++k)
				c.m[i][j] = (c.m[i][j] % (mod - 1) + a.m[i][k] * b.m[k][j] % (mod - 1)) % (mod - 1);
	return c;
}

inline LL qpow(mat a, LL n){ 
	mat res = unit;
	while(n){
		if(n & 1) res = mul(res, a);
		n >>= 1;
		a = mul(a, a);
	}
	return res.m[1][2];
}

inline LL qupow(LL a, LL n) {
	LL res = 1;
	while(n) {
		if(n & 1) res = qmul(res, a) % mod;
		n >>= 1;
		a = qmul(a, a) % mod;
	}
	return res;
}

int main(){
	while(scanf("%lld %lld %lld", &a, &b, &n) != EOF){
		for(int i = 1; i <= 2; ++i)
			unit.m[i][i] = 1;
		A.m[1][1] = A.m[1][2] = A.m[2][1] = 1;
		A.m[2][2] = 0;
		if(n == 0) {
			printf("%lld\n", a);
			continue;
		} else if(n == 1) {
			printf("%lld\n", b);
			continue;
		} else {
			LL x = qpow(A, n - 1) % (mod - 1);
			LL y = qpow(A, n) % (mod - 1);
			LL ans = qupow(a, x) * qupow(b, y) % mod;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
