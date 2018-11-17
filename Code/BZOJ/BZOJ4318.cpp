#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 300010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n;
double p, len1, len2, dp;

int main() {
	n = read();
	for(rg int i = 1; i <= n; ++i) {
		scanf("%lf", &p);
		dp += (3 * len2 + 3 * len1 + 1) * p;
		len2 = (len2 + 2 * len1 + 1) * p;
		len1 = (len1 + 1) * p;
	}
	printf("%.1lf", dp);
	return 0;
}