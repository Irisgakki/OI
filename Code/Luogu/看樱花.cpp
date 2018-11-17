#include <bits/stdc++.h>
#define int long long

const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int getint() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);	
	putchar(x % 10 + '0');
}

int n, l, r, now, ans;
int d[maxn], f[maxn], c[maxn], sum[maxn];
int cl[maxn], cr[maxn];

inline void input() {
	cl[0] = cl[n + 1] = cr[0] = cr[n + 1] = sum[0] = 0;
	n = getint(), l = getint(), r = getint();
	for(int i = 1; i <= n; ++i) d[i] = getint();
	for(int i = 1; i <= n; ++i) f[i] = getint();
	for(int i = 1; i <= n; ++i) c[i] = getint();
	for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + c[i];
	for(int i = 1; i <= n; ++i) cl[i] = std::max(cl[i - 1] - l - r, 1ll*0) + c[i];
	for(int i = n; i >= 1; --i) cr[i] = std::max(cr[i + 1] - l - r, 1ll*0) + c[i];  
}

inline void output() {
	ans = -inf, now = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(i < j) now = (cl[i] + cr[j]) + (sum[j - 1] - sum[i]) - (j - i) * r - d[i] - f[j];
			else if(i > j) now = (cr[i] + cl[j]) + (sum[i - 1] - sum[j]) - (i - j) * l - d[i] - f[j];
			else now = c[i] - d[i] - f[j];
			ans = std::max(ans, now);  
		}
	}
	write(ans);
} 

signed main() {
	input();
	output();	
	return 0;	
}
