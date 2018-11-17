#include <bits/stdc++.h>
#define int long long
const int maxn = 1000010;
const int inf = 1e18;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

char s[maxn];
static int ans, n;
static int a[maxn], b[maxn], c[maxn];

signed main(){
	n = read();
	scanf("%s", s + 1);
	for(int i = 1; i <= n; ++i){
		a[i] = a[i - 1] + (s[i] == 'B');
		b[i] = b[i - 1] + (s[i] == 'C');
		c[i] = c[i - 1] + (s[i] == 'S');
	}
	for(int i = 1; i <= 3; ++i){
		for(int j = n; j - i + 1 > ans; --j){
			int tmp1 = a[j] - a[i - 1];
			int tmp2 = b[j] - b[i - 1];
			int tmp3 = c[j] - c[i - 1];
			if((tmp1 != tmp2 && tmp2 != tmp3 && tmp1 != tmp3) || (!tmp1) + (!tmp2) + (!tmp3) == 2) {
				ans = j - i + 1;
				break;
			}
		}
	}
	for(int j = n - 2; j <= n; ++j){
		for(int i = 1; j - i + 1 > ans; ++i){
			int tmp1 = a[j] - a[i - 1];
			int tmp2 = b[j] - b[i - 1];
			int tmp3 = c[j] - c[i - 1];
			if((tmp1 != tmp2 && tmp2 != tmp3 && tmp1 != tmp3) || (!tmp1) + (!tmp2) + (!tmp3) == 2) {
				ans = j - i + 1;
				break;
			}	
		}
	}
	printf("%lld\n", ans);
	return 0;
}