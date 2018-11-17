#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
typedef long long LL;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int read() {
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

char s[maxn];
int a[maxn], top = 0;
LL dp[maxn][15][2];//i = pos, j = pre, 0 = down, 1 = up; 

inline LL DP(int pos, int pre, int sta, int limit) {
	if(pos == -1) return 1;
	if(!limit && dp[pos][pre][sta] != -1) return dp[pos][pre][sta];
	int up = limit ? a[pos] : 9;
	LL ans = 0;
	for(int i = 0; i <= up; ++i) {
		if(pre == 10 && i == 0) {//pre 0
			ans = (ans + DP(pos - 1, 10, 0, limit && i == up)) % mod;
			continue;
		}
		if(i < pre && sta == 1) continue;//前一位比枚举的大，并且处于递增，不满足要求 
		if(i <= pre) ans = (ans + DP(pos - 1, i, sta, limit && i == up)) % mod;
		else ans = (ans + DP(pos - 1, i, 1, limit && i == up)) % mod;//pre < i,转递增 
	}
	if(!limit) dp[pos][pre][sta] = ans;
	return ans;
}

int main() {
	freopen("victory.in","r",stdin);
	freopen("victory.out","w",stdout);
	//printf("%d\n", sizeof(dp) / 1024 / 1024);
	scanf("%s", s);
	int len = strlen(s);
	for(int i = 0; i < len; ++i)
		a[len - 1 - i] = s[i] - '0';
	//1220
	memset(dp, -1, sizeof(dp));
	printf("%lld", DP(len - 1, 10, 0, 1) - 1);
	return 0;
}
