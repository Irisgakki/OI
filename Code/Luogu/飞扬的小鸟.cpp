// luogu-judger-enable-o2
#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10010;
const int inf = 0x7f7f7f7f;
const int mod = 10007;

inline int read() {
    register int x = 0, g = 1; register char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
    return x * g;
}

int n, m, k;
int x[maxn], y[maxn];
int down[maxn], up[maxn];
int dp[maxn][2010];
bool is_pipe[maxn];

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d",&x[i],&y[i]);
        down[i] = 1;
        up[i] = m;
    }
    for(int i = 1; i <= k; ++i) {
        int p, l, h;
        scanf("%d%d%d",&p,&l,&h);
        is_pipe[p] = 1;
        down[p] = l + 1;
        up[p] = h - 1;
    }
    memset(dp, 0x7f, sizeof(dp));
    for(int i = 1; i <= m; ++i) dp[0][i] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = x[i] + 1; j <= m + x[i]; ++j)
            dp[i][j] = std::min(dp[i][j - x[i]] + 1, dp[i - 1][j - x[i]] + 1);
        for(int j = 1; j <= m - y[i]; ++j)
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j + y[i]]);
        for(int j = m + 1; j <= m + x[i]; ++j)
            dp[i][m] = std::min(dp[i][m], dp[i][j]);
        for(int j = 1; j < down[i]; ++j)
            dp[i][j] = inf;
        for(int j = up[i] + 1; j <= m; ++j)
            dp[i][j] = inf;
    }
    int ans = inf;
    for(int i = 1; i <= m; ++i)
        ans = std::min(ans, dp[n][i]);
    if(ans < inf) {
        printf("1\n%d", ans);
    } else {
        int i, j;
        for(i = n; i >= 1; --i) {
            for(j = 1; j <= m; ++j) {
                if(dp[i][j] < inf) break;
            }
            if(j <= m) break;
        }
        ans = 0;
        for(int l = 1; l <= i; ++l)
            if(is_pipe[l]) ans++;
        printf("0\n%d", ans);
    }
    return 0;
}