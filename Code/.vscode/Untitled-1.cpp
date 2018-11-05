#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 1e6 + 7;
const int arr = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

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

int n;
int dp[1 << 21], a[arr][arr];

int main() {
    freopen("proficiency.in","r",stdin);
    freopen("proficiency.out","w",stdout);
    n = getint();
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) a[i][j] = getint();
    int Max = 1 << n;
    for(int sta = 0; sta < Max; ++sta) {
        for(int i = 1; i <= n; ++i) {
            if(sta & (1 << i - 1)) continue;
            int next_sta = sta | (1 << i - 1);
            int sum = 0;
            for(int j = 1; j <= n; ++j) if(!(sta & (1 << j - 1))) sum += a[j][i];
            dp[next_sta] = std::max(dp[next_sta], dp[sta] + sum);
        }
    }
    write(dp[Max - 1]);
    return 0;
}