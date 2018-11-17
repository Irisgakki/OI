#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int T;
LL a, b, n;
int fac[maxn], top = 0;

inline void sieve(LL x) {
	top = 0;
	for(int i = 2; i * i <= x; ++i) {
		if(x % i == 0) {
			fac[++top] = i;
			while(x % i == 0) {
				x /= i;
			}
		}
	}
	if(x > 1) fac[++top] = x;
}

inline LL cal(LL n) {
	LL sum = 0, tmp, que[maxn], sz = 0;
	que[sz++] = -1;
	for(int i = 1; i <= top; ++i) {
		tmp = sz;
		for(int j = 0; j < tmp; ++j) {
			que[sz++] = que[j] * fac[i] * (-1);
		}
	}
	for(int i = 1; i < sz; ++i) {
		sum += n / que[i];
	}
	return sum;
}

int main() {
	scanf("%d", &T);
	for(int cas = 1; cas <= T; ++cas) {
		scanf("%lld %lld %lld", &a, &b, &n);
		sieve(n);
		LL ans = b - cal(b) - (a - 1 - cal(a - 1));
		//printf("%lld\n %lld\n", a - 1 - cal(a - 1), b - cal(b));
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}