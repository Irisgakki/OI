#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 300;
const int inf = 0x3f3f3f3f;

inline int getint() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);	
	putchar(x % 10 + '0');
}

int n, m, K;
int dp[maxn][maxn][maxn], sum[maxn][2];

inline void input() {
	n = getint(), m = getint(), K = getint();
	memset(sum, 0, sizeof(sum));
	for(int i = 1 ;i <= n; ++i) {
		if(m == 1) {
			int x = getint(), y = 0;
			sum[i][1] = sum[i - 1][1] + x;
			sum[i][2] = sum[i - 1][2] + y;	
		} else {
			int x = getint(), y = getint();
			sum[i][1] = sum[i - 1][1] + x;
			sum[i][2] = sum[i - 1][2] + y;
		}
	}
}

inline void solve() {
	memset(dp, 0, sizeof(dp));
	for(int k = 1; k <= K; ++k) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i][j - 1][k]);
				for(int p = 0; p < i; ++p) dp[i][j][k] = std::max(dp[i][j][k], dp[p][j][k - 1] + sum[i][1] - sum[p][1]);
				for(int p = 0; p < j; ++p) dp[i][j][k] = std::max(dp[i][j][k], dp[i][p][k - 1] + sum[j][2] - sum[p][2]);
				if(i == j) for(int p = 0; p < i; ++p) dp[i][j][k] = std::max(dp[i][j][k], dp[p][p][k - 1] + sum[i][1] - sum[p][1] + sum[j][2] - sum[p][2]);
			}
		}
	}
	write(dp[n][n][K]);
}

int main() {
	input();
	solve();
	return 0;	
}