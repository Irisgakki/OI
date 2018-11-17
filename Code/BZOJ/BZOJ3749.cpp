#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, a[maxn];
int dp[maxn][5], ans[maxn];

int main(){
	n = read();
	for(int i = 0; i <= n - 1; ++i) a[i] = read();
	a[n] = a[0];
	for(int i = 1; i <= 4; ++i) {
		memset(dp, 0, sizeof(dp));
		dp[0][i] = 1;
		for(int j = 1; j <= n; ++j) {
			if(dp[j - 1][1] && a[j] * 2 >= a[j - 1]) dp[j][1] = 1;
			if(dp[j - 1][1] && a[j]	>= a[j - 1]) dp[j][4] = 1;
			if(dp[j - 1][2] && a[j - 1] * 2 >= a[j]) dp[j][2] = 2;
			if(dp[j - 1][2] && a[j - 1] >= a[j]) dp[j][3] = 2;
			if(dp[j - 1][3] && a[j] >= a[j - 1]) dp[j][1] = 3;
			if(dp[j - 1][3] && a[j] >= a[j - 1] * 2) dp[j][4] = 3;
			if(dp[j - 1][4] && a[j - 1] >= a[j]) dp[j][2] = 4;
			if(dp[j - 1][4] && a[j - 1] >= a[j] * 2) dp[j][3] = 4;
		}
		if(!dp[n][i]) continue;
		for(int j = n, k = i; j >= 1; --j){
			if(k == 1 || k == 4) ans[j] = j % n + 1;
			if(k == 2 || k == 4) ans[j % n + 1] = j % n + 1;
			k = dp[j][k];
		}
		for(int j = 1; j <= n; ++j){
			printf("%d ", ans[j]);
		}
		return 0;
	}
	printf("NIE");
	return 0;
}