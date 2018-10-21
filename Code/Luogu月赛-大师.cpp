#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 1010;
const int inf = 1 << 30;
const int mod = 998244353;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

LL n;
LL a[maxn], ans = 0;

std::map<int, int> dp[maxn];

int main() {
	n = read();
	for(rg int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for(rg int i = 1; i <= n; ++i) {
		for(rg int j = 1; j < i; ++j) {
			int d = a[i] - a[j];
			dp[i][d]++;
			if(dp[j][d] != 0) {
				dp[i][d] = (dp[i][d] + dp[j][d]) % mod;
				ans = (ans + dp[j][d]) % mod;
			}
		}
	}
	printf("%lld\n", (ans + n + ((n - 1) * n / 2)) % mod);
	return 0;
}
