#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x7f7f7f7f;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n;
int not_prime[maxn], prime[maxn], top = 0;

inline void sieve() {
	memset(not_prime, 0, sizeof(not_prime));
	for(rg int i = 2; i < maxn; ++i) {
		if(!not_prime[i]) prime[++top] = i;
		for(rg int j = 1; j <= top && i * prime[j] < maxn; ++j) {
			not_prime[i * prime[j]] = 1;
			if(!(i % prime[j])) break;
		}
	}
}

int main() {
	sieve();
	while(1) {
		n = read();
		if(!n) break;
		printf("%d ", n);
		int s = sqrt(n), ans = 1;
		for(rg int i = 1; i <= top && prime[i] <= s; ++i) {
			int cnt = 0;
			while(!(n % prime[i])) {
				cnt++;
				n /= prime[i];
			}
			ans *= cnt * 2 + 1;
		}
		if(n > 1) ans *= 3;
		printf("%d\n", ans / 2 + 1);
	}
	return 0;
}