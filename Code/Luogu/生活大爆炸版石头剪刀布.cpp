#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, na, nb;
int a[maxn], b[maxn];
int ans1 = 0, ans2 = 0;

int main(){
	n = read(), na = read(), nb = read();
	for(int i = 1; i <= na; ++i) a[i] = read();
	for(int i = 1; i <= nb; ++i) b[i] = read();
	for(int i = na + 1; i <= n; ++i) {
		a[i] = a[i - na];
	}
	for(int i = nb + 1; i <= n; ++i) {
		b[i] = b[i - nb];
	}
	for(int i = 1; i <= n; ++i) {
		if(a[i] == b[i]) continue;
		if(a[i] == 0) {
			if(b[i] == 2 || b[i] == 3) ans1++;
			else ans2++;
		}
		if(a[i] == 1) {
			if(b[i] == 0 || b[i] == 3) ans1++;
			else ans2++;
		}
		if(a[i] == 2) {
			if(b[i] == 1 || b[i] == 4) ans1++;
			else ans2++;
		}
		if(a[i] == 3) {
			if(b[i] == 2 || b[i] == 4) ans1++;
			else ans2++;
		}
		if(a[i] == 4) {
			if(b[i] == 0 || b[i] == 1) ans1++;
			else ans2++;
		}
	}
	printf("%d %d", ans1, ans2);
	return 0;
}