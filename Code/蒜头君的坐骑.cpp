#include <bits/stdc++.h>
const int maxn = 550;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m, t, k, h, atk;
int dp[maxn][maxn][110];//dp[i][j][t]琛ㄧず鍒癷,j鏃剁敤浜唗娆℃妧鑳芥椂鐨勬渶灏忓彈浼ゅ€?
int a[maxn][maxn];

inline int cal(int hp, int atk) {
	return (h - 1) / atk * hp;
}

inline void dfs(int x, int y, int p, int trans, int atk, int depth) {
	if(depth > k) {
		dp[x][y][p + 1] = std::min(dp[x][y][p + 1], trans);
		return ;
	}
	if(x + 1 <= n)
		dfs(x + 1, y, p, trans + cal(a[x + 1][y], atk + a[x + 1][y]), atk + a[x + 1][y], depth + 1);
	if(y + 1 <= m)
		dfs(x, y + 1, p, trans + cal(a[x][y + 1], atk + a[x][y + 1]), atk + a[x][y + 1], depth + 1);
}

int main(){
	n = read(), m = read(), t = read(), k = read(), h = read(), atk = read();
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) 
			a[i][j] = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			for(int p = 0; p <= t; ++p)
				dp[i][j][p] = inf;	
	dp[1][1][0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			for(int p = 0; p <= t; ++p) {
				if(p != t)
					dfs(i, j, p, dp[i][j][p], atk, 1);
				if(i + 1 <= n)
					dp[i + 1][j][p] = std::min(dp[i + 1][j][p], dp[i][j][p] + cal(a[i + 1][j], atk));
				if(j + 1 <= m)
					dp[i][j + 1][p] = std::min(dp[i][j + 1][p], dp[i][j][p] + cal(a[i][j + 1], atk));
			}
		}
	}
	int ans = inf;
	for(int i = 0; i <= t; ++i)
		ans = std::min(ans, dp[n][m][i]);
	printf("%d\n", ans);
	return 0;
}