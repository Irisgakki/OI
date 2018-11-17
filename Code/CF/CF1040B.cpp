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

int n, k;
static int ans, a[maxn];


int main(){
	n = read(), k = read();
	int kk = 2 * k + 1;
	if(!k){
		ans = n;
		for(int i = 1; i <= n; ++i) a[i] = i;
	} else if(n <= kk) {
		ans = 1;
		a[1] = n / 2 + 1;
	} else if(n > kk) {
		if(n % kk > k || !(n % kk)) {
			ans = 0;
			for(int i = k + 1; i <= n; i += kk)
				a[++ans] = i;
		} else{
			ans = 0;
			for(int i = 1; i <= n; i += kk) {
				a[++ans] = i;
			}
		}
	}
	printf("%d\n", ans);
	for(int i = 1; i <= ans; ++i)
		printf("%d ", a[i]);
	return 0;
}