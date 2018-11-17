#include <bits/stdc++.h>
#define int long long
const int maxn = 200;
const int inf = 1e18;
const int mod = 998244353;
const int dx[] = {0,1,1,1,0,-1,-1,-1};
const int dy[] = {1,1,0,-1,-1,-1,0,1};

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m;
std::bitset<maxn> dp[maxn][32], ans, tmp;

signed main(){
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		dp[u][0][v] = 1;
	}
	for(int j = 0; j <= 30;++j) {
		for(int i = 1; i <= n; ++i) {
			for(int k = 1; k <= n; ++k) {
				if(dp[i][j][k]) {
					dp[i][j + 1] |= dp[k][j];
				}
			}
		}
	}
	int Q = read();
	while(Q--) {
		int l = read(), a = read(), b = read();
		ans.reset();
		ans[a] = 1;
		for(int i = 0; i <= 30; ++i) {
			if(!(l >> i)) break;
			if((l >> i) & 1) {
				tmp = ans;
				ans.reset();
				for(int j = 1; j <= n; ++j)
					if(tmp[j])
						ans |= dp[j][i];
			}
		}
		ans[b] ? printf("YES\n") : printf("NO\n");
	}
	return 0;
}