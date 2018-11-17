#include <bits/stdc++.h>
#define int long long
const int maxn = 1000100;
const int inf = 1e18;
const int mod = 998244353;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

char s[maxn];
static int ans[maxn];

signed main(){
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	for(int i = 2; i <= len; ++i) {
		if(s[i] == 'a') {
			ans[i - 1] ^= 1;
			ans[i] = 1;
		}
	}
	for(int i = 1; i <= len; ++i)
		printf("%lld ", ans[i]);
	return 0;
}