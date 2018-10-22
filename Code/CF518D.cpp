#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 2010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, t;
double p;
double dp[maxn][maxn];

int main() {
	n = read();
	scanf("%lf", &p);
	t = read();
	dp[0][0] = 1;
	for(rg int i = 0; i < t; ++i) {
		dp[i + 1][n] += dp[i][n];
		for(rg int j = 0; j < n; ++j) {
			dp[i + 1][j + 1] += dp[i][j] * p;
			dp[i + 1][j] += dp[i][j] * (1 - p);
		}
	}
	double ans = 0;
	for(rg int i = 0; i <= n; ++i) ans += i * dp[t][i];
	printf("%.6lf", ans);
	return 0;
}