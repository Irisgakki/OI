#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline LL read(){
	register LL x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

LL a[maxn];
LL n, k, q;

int main(){
	n = read(), k = read(), q = read();
	a[0] = 1;
	for(LL i = 1; i <= 100; ++i) {
		a[i] = (a[i - 1] * (k + 1)) % q;
	}
	k = std::min(k, n);
	LL ans = a[n - k];
	for(LL i = 2; i + k <= n; ++i) {
		ans = (ans + (n - k + 1 - i) * a[n - k + 1 - i]) % q;
	}
	for(LL i = 3; i + k <= n; ++i) {
		ans = (ans + (n - k + 1 - i) * a[n - k - 1]) % q;
	}
	for(LL i = 1; i <= k; ++i) {
		ans = (ans * i) % q;
	}
	printf("%lld\n", ans);
	return 0;
}