#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 1010;
const int inf = 1 << 30;
const int mod = 998244353;

inline LL read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

LL w, h, k, ans = 0;

int main() {
	w = read(), h = read(), k = read();
	for(rg int i = 1; i <= k; ++i) {
		ans += (w - 2) * 2 + h * 2;
		w -= 4, h -= 4;
	}
	printf("%I64d", ans);
	return 0;
}