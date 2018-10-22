#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 300010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n;
char a[maxn];
double dp[maxn], len[maxn];

int main() {
	n = read();
	scanf("%s", a + 1);
	for(rg int i = 1; i <= n; ++i) {
		if(a[i] == 'o') {
			dp[i] = dp[i - 1] + len[i - 1] * 2 + 1;
			len[i] = len[i - 1] + 1;
		}
		if(a[i] == 'x') {
			dp[i] = dp[i - 1];
			len[i] = 0;
		}
		if(a[i] == '?') {
			dp[i] = dp[i - 1] + (len[i - 1] * 2 + 1) / 2;
			len[i] = (len[i - 1] + 1) / 2;
		}
	}
	printf("%.4lf", dp[n]);
	return 0;
}