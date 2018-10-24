#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;
const int mod = 1e9;

int m, n;
int dp[20][maxn];
int s[maxn], sta[maxn], top = 0;

int main() {
	scanf("%d %d", &m, &n);
	int S = 1 << n;
	for(int i = 0; i < S; ++i) {
		if(i & (i << 1)) continue;
		sta[++top] = i;
	}
	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= n; ++j) {
			int x;
			scanf("%d", &x);
			if(!x) s[i] += 1 << (n - j);
		}
	}
	memset(dp, 0, sizeof(dp));
	for(int i = 1; i <= top; ++i)
		if(!(sta[i] & s[1])) dp[1][i] = 1;
	for(int i = 2; i <= m; ++i) {
		for(int j = 1; j <= top; ++j) {
			if(sta[j] & s[i]) continue;
			for(int k = 1; k <= top; ++k) {
				if(sta[k] & s[i - 1]) continue;
				if(sta[j] & sta[k]) continue;
				dp[i][j] = (dp[i][j] + dp[i - 1][k]) % mod;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= top; ++i) ans = (ans + dp[m][i]) % mod;
	printf("%d", ans);
	return 0;
}