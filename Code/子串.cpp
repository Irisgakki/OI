#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define Debug printf("Passing [%s] in LINE %d\n", __FUNCTIOIN__,__LINE__)

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

int n, m, k;
char A[maxn], B[maxn];
int tmp[2][maxn][maxn], dp[2][maxn][maxn];

int main(){
	n = read(), m = read(), k = read();
	scanf("%s %s", A + 1, B + 1);
	int now = 1;
	dp[0][0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		dp[now][0][0] = 1;
		for(int j = 1; j <= m; ++j) {
			for(int l = 1; l <= k; ++l) {
				if(A[i] == B[j]) tmp[now][j][l] = (tmp[now^1][j-1][l]+dp[now^1][j-1][l-1]) % mod;
				else tmp[now][j][l] = 0;
				dp[now][j][l] = (tmp[now][j][l] + dp[now^1][j][l]) % mod;
			}
		}
		now ^= 1;
	}
	printf("%d\n", dp[now^1][m][k]);
	return 0;
}