#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

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

LL n, top = 0;
LL prime[maxn], phi[maxn];
bool not_prime[maxn];


int main(){
	memset(not_prime, 0, sizeof(not_prime));
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!not_prime[i]) {prime[++top] = i; phi[i] = i - 1;}
		for(int j = 1; j <= top && i * prime[j] < maxn; ++j) {
			not_prime[i * prime[j]] = 1;
			if(!(i % prime[j])) {phi[i * prime[j]] = phi[i] * prime[j]; break;}
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for(int i = 1; i < maxn; ++i) phi[i] += phi[i - 1];
	while(scanf("%lld", &n)) {
		if(!n) break;
		LL ans = 0;
		for(int i = 1; i <= n; ++i) ans += (phi[n / i] - 1) * i;
		print(ans);puts("");
	}
	return 0;
}