#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 500010;
const int inf = 0x3f3f3f3f;
#define Debug printf("Passing [%s] in LINE %d\n", __FUNCTIOIN__,__LINE__)

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

int l, n, m;
int d[maxn], ans = 0;

inline bool check(int x) {
	int tot = 0, now = 0, pos = 0;
	while(pos < n + 1) {
		pos++;
		if(d[pos] - d[now] < x) tot++;
		else now = pos;
	}
	if(tot > m) return false;
	else return true;
}


int main(){
	l = read(), n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		d[i] = read();
	}
	d[0] = 0, d[n + 1] = l;
	int l = 1, r = inf;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d\n", ans);
	return 0;
}