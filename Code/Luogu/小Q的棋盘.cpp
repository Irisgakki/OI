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

int v, n;
int dp[2][arr][arr];
struct Edge{
    int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) {
    e[++cnt] = (Edge){head[u], v};
    head[u] = cnt;
}

int fa[maxn];
inline void dfs1(int now) {
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa[now]) continue;
        fa[to] = now;
        dfs1(to);
    }
}

inline void dfs2(int now) {
    dp[0][now][0] = dp[1][now][0] = 1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to != fa[now]) {
            dfs2(to);
            for(int j = n; j > 0; --j) {
                for(int k = 0; k < j; ++k) {
                    if(j - k >= 2) {
                        dp[1][now][j] = std::max(dp[1][now][j], dp[1][to][k] + dp[1][now][j - k - 2]);
                        dp[0][now][j] = std::max(dp[0][now][j], dp[1][to][k] + dp[0][now][j - k - 2]);
                    }
                    dp[0][now][j] = std::max(dp[0][now][j], dp[0][to][k] + dp[1][now][j - k - 1]);
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i){
        dp[0][now][i] = std::max(dp[0][now][i], dp[0][now][i - 1]);
        dp[1][now][i] = std::max(dp[1][now][i], dp[1][now][i - 1]);
    }
}


int main() {
    v = getint(), n = getint();
    for(int i = 1; i <= v - 1; ++i) {
        int u = getint(), v = getint();
        add(u, v); add(v, u);
    }
    dfs1(0);
    dfs2(0);
    write(dp[0][0][n]);
    return 0;
}