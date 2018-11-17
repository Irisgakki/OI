#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 2010;
const int maxv = 500;
const int inf = 0x3f3f3f3f;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, m, v, e;
int c[maxn][2], dis[maxv][maxv];
double k[maxn], dp[maxn][maxn][2];


int main() {
	memset(dis, 0x3f, sizeof(dis));
    n = read(), m = read(), v = read(), e = read();
    for(int i = 1; i <= n; ++i)
		c[i][0] = read();
    for(int i = 1; i <= n; ++i)
		c[i][1] = read();
    for(int i = 1; i <= n; ++i) scanf("%lf", &k[i]);
    for(int i = 1; i <= e; ++i) {
        int u = read(), v = read(), w = read();
        dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
    }
    for(int p = 1; p <= v; ++p)
        for(int i = 1; i <= v; ++i)
            for(int j = 1; j <= v; ++j)
                dis[i][j] = std::min(dis[i][j], dis[i][p] + dis[p][j]);
       for(int i = 1; i <= v; ++i) dis[i][i] = dis[i][0] = dis[0][i] = 0;
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= m; ++j)
            dp[i][j][0] = dp[i][j][1] = 1e10;
    dp[1][0][0] = dp[1][1][1] = 0;
    for(int i = 2; i <= n; ++i) {
    	dp[i][0][0] = dp[i - 1][0][0] + dis[c[i - 1][0]][c[i][0]];
        for(int j = 1; j <= std::min(i, m); ++j) {
            int C1 = c[i - 1][0], C2 = c[i - 1][1], C3 = c[i][0], C4 = c[i][1];
            dp[i][j][0] = std::min(dp[i][j][0], std::min(dp[i - 1][j][0] + dis[C1][C3], dp[i - 1][j][1] + dis[C1][C3] * (1 - k[i - 1]) + dis[C2][C3] * k[i - 1]));
			dp[i][j][1] = std::min(dp[i][j][1], std::min(dp[i - 1][j - 1][0] + dis[C1][C3] * (1 - k[i]) + dis[C1][C4] * k[i], dp[i - 1][j - 1][1] + dis[C2][C4] * k[i] * k[i - 1] + dis[C2][C3] * k[i - 1] * (1 - k[i]) + dis[C1][C4] * (1 - k[i - 1]) * k[i] + dis[C1][C3] * (1 - k[i - 1]) * (1 - k[i])));
        }
    }
    double ans = 1e10;
    for(int i = 0; i <= m; ++i)
     	ans = std::min(ans, std::min(dp[n][i][0], dp[n][i][1]));   
    printf("%.2lf", ans);
    return 0;
}
