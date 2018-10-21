#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 1000010;
const int inf = 1 << 30;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

LL n;
LL ans1 = 0, ans2 = 0;
LL a[maxn], b[maxn], c[maxn << 1], pre[maxn];

int main() {
	n = read();
	ans1 = 0, ans2 = 0;
	for(rg int i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
	for(rg int i = 1; i <= n; ++i) ans1 += a[i], ans2 += b[i];
	ans1 = std::min(ans1, ans2);
	for(rg int i = 1; i <= n; ++i) c[i * 2] = a[i], c[i * 2 - 1] = b[i];
	std::sort(c + 1, c + 2 * n + 1);
	for(rg int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + c[i];
	for(rg int i = 1; i <= n; ++i) {
		ans2 = 0;
		int now = n;
		if(a[i] >= c[now]) ans2 += a[i], now--;
		if(b[i] >= c[now]) ans2 += b[i], now--;
		ans1 = std::min(ans1, ans2 + pre[now]);
	}
	printf("%lld\n", ans1);
	return 0;
}