#include <bits/stdc++.h>
#define int long long
const int maxn = 2030;
const int inf = 1e18;
const int mod = 998244353;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, k;
struct Edge{
	int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) { e[++cnt] = (Edge) {head[u], v}; head[u] = cnt; }
inline void ins(int u, int v) { add(u, v); add(v, u); }

static int son[maxn], dp[maxn][maxn], tmp[maxn];
inline void dfs(int now, int fa){
	son[now] = dp[now][1] = 1;
	for(int i = head[now]; i; i = e[i].next){
		int to = e[i].to;
		if(to == fa) continue;
		dfs(to, now);
		memset(tmp, 0, sizeof(tmp));
		for(int i = 1; i <= son[now]; ++i){
			for(int j = 0; j <= std::min(son[to], k - i); ++j){
				tmp[i + j] = (tmp[i + j] + dp[now][i] * dp[to][j]) % mod;
			}
		}
		memcpy(dp[now], tmp, sizeof(dp[now]));
		son[now] += son[to];
	}
	for(int i = 1; i <= k; ++i)
		dp[now][0] = (dp[now][0] + dp[now][i]) % mod;
}

signed main(){
	n = read(), k = read();
	for(int i = 1; i <= n - 1; ++i){
		int u = read(), v = read();
		ins(u, v);
	}
	dfs(1, 0);
	static int ans;
	for(int i = 1; i <= k; ++i)
		ans = (ans + dp[1][i]) % mod;
	printf("%lld\n", ans);
	return 0;
}