#include <bits/stdc++.h>
#define int long long
const int maxn = 500010;
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

int n, a[maxn];
int vis[maxn], ans = 0;

signed main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	for(int i = 1; i <= n; ++i) {
		for(int j = i << 1; j <= n; j += i) {
			if(!vis[j] && a[i] != a[j]) {
				ans++;
				vis[j] = 1;
			}
		}
	}
	printf("%lld\n", ans + 1);
	return 0;
}