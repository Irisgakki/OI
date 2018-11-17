#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int getint() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void write(LL x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);	
	putchar(x % 10 + '0');
}

int n, m;
LL sum = 0, cnt[maxn];

inline void input() {
	n = getint(), m = getint();	
}

inline void solve() {
	for(int i = std::min(n, m); i >= 1; --i) {
		cnt[i] = 1ll * (n / i) * (m / i);
		for(int j = i << 1; j <= n; j += i) cnt[i] -= cnt[j];
		sum += 1ll * ((i << 1) - 1) * cnt[i];
	}
}

inline void output() {
	write(sum);	
}

int main() {
	input();
	solve();
	output();
	return 0;	
}