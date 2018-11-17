#include <bits/stdc++.h>
#define int long long
const int maxn = 500010;
const int inf = 1e18;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, x;
int num[maxn];
static int ans;

signed main(){
	n = read();
	for(int i = 1; i <= n; ++i){
		x = read();
		for(int j = 1; j <= 500; ++j){
			if(j * j >= x){
				ans += num[j * j - x];
			}
		}
		num[x]++;
	}
	printf("%lld\n", ans);
	return 0;
}