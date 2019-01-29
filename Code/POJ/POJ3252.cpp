#include <bits/stdc++.h>

using namespace std;

const int maxn = 50;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
	return x * g;
}

inline void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');	
}

int l, r;
int a[maxn];
int dp[maxn][maxn][maxn];

inline int dfs(int pos, int num0, int num1, int limit, int zero) {
	if(pos == -1) {
		if(zero)	return 0;
		return num0 >= num1;
	}
	if(!zero && !limit && dp[pos][num0][num1] != -1) return dp[pos][num0][num1];
	int ans = 0;
	int up = limit ? a[pos] : 1;
	for(int i = 0; i <= up; ++i) {
		if(zero) {
			if(!i) ans += dfs(pos - 1, num0, num1, limit && i == up, 1);
			else ans += dfs(pos - 1, num0, num1 + 1, limit && i == up, 0);		
		} else {
			if(!i) ans += dfs(pos - 1, num0 + 1, num1, limit && i == up, 0);
			else ans += dfs(pos - 1, num0, num1 + 1, limit && i == up, 0);
		}
	}
	if(!limit && !zero) dp[pos][num0][num1] = ans;
	return ans;
}


inline int solve(int x) {
	memset(dp, -1, sizeof(dp));
	int pos = 0;
	while(x) {
		a[pos++] = x & 1;
		x >>= 1;
	}
	return dfs(pos - 1, 0, 0, 1, 1);
}

int main() {
	// freopen("rndnum.in","r",stdin);
	// freopen("rndnum.out","w",stdout);
	l = read(), r = read();
	printf("%d\n", solve(r) - solve(l - 1));
	return 0;	
}
