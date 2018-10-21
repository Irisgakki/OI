#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 1e7+5;
const int inf = 1 << 30;
const int mod = 1000000007;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, a, b, c, d;
LL x[maxn], odd = 0, even = 0;

inline int get(int x) {
	int cnt = 0;
	while(x) {
		cnt++;
		x &= (x - 1);
	}
	return cnt;
}

int main() {
	n = read(), a = read(), b = read(), c = read(), d = read(), x[0] = read();
	for(rg int i = 1; i <= n; ++i)
		x[i] = (a * x[i - 1] * x[i - 1] % d + b * x[i - 1] % d + c % d) % d;
	for(rg int i = 1; i <= n; ++i) {
		if(get(x[i]) & 1) odd++;
		else even++;
	}
	printf("%lld\n", odd * even);
	return 0;
}