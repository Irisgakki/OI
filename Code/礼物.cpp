#include <bits/stdc++.h>
#define Debug printf("Passing [%s] in LINE %d\n", __FUNCTIOIN__,__LINE__)
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 2001000;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline int lowbit(int x) {
	return x & -x;
}

int n, k;
int a[maxn];
int dp[1 << 20];
std::vector<int> vec[maxn];

int main() {
	n = read(), k = read();
	rep(i, 1, n) {
		int x = read();
		a[x] = 1;
	}
	int S = 1 << k;
	for(int i = 0; i < S; ++i) {
		for(int j = i; j; j ^= lowbit(j)) {
			dp[i] = std::max(dp[i], dp[i ^ lowbit(j)]);
		}
		if(a[i]) vec[++dp[i]].push_back(i);
	}
	printf("1\n%d\n", dp[S - 1]);
	for(int i = 1; i <= dp[S - 1]; ++i) {
		printf("%d ", vec[i].size());
		for(std::vector<int>::iterator it = vec[i].begin(); it != vec[i].end(); ++it)
			printf("%d ", *it);
		printf("\n");
	}
	return 0;
}