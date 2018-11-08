#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 1e6 + 7;
const int arr = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

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

int n, m, ans = inf;
int dis[arr][arr], link[arr][arr], K[maxn];
int dp[1 << 13];

inline void dfs(int sta) {
	for(int i = 1; i <= n; ++i) {
		if(sta & (1 << i - 1)) {
			for(int j = 1; j <= n; ++j) {
				if(!(sta & (1 << j - 1)) && link[i][j]) {
					if(dp[sta | (1 << j - 1)] > dp[sta] + dis[i][j] * K[i]) {
						int tmp = K[j];
						K[j] = K[i] + 1;
						dp[sta | (1 << j - 1)] = dp[sta] + dis[i][j] * K[i];
						dfs(sta | (1 << j - 1));
						K[j] = tmp;
					}
				}
			}
		}
	}
}


int main() {
	memset(dis, 0x3f, sizeof(dis));
	n = getint(), m = getint();
	for(int i = 1; i <= m; ++i) {
		int u = getint(), v = getint(), w = getint();
		dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
		link[u][v] = link[v][u] = 1;
	}
	for(int i = 1; i <= 12; ++i) {
		memset(K, 127 / 3, sizeof(K));
		for(int j = 1; j < (1 << n); ++j) dp[j] = inf;
		K[i] = 1, dp[1 << i - 1] = 0;
		dfs(1 << i - 1);
		ans = std::min(ans, dp[(1 << n) - 1]);
	}
	write(ans);
    return 0;
}
