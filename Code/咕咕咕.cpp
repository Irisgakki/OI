#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e6 + 7;
const int inf = 0x3f3f3f3f;
const int base = 31;
const int mod = 998244353;

inline ll read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register ll x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void print(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

ll n, m, _count = 0, a;
ll C[100][100], dp[100], ans, sum[maxn];
char s[maxn];

int main() {
    n = read(), m = read();
    C[0][0] = 1;
    for(int i = 0; i <= n; ++i) C[i][0] = 1;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= i; ++j) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    dp[0] = 1;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= i; ++j) dp[i] = (dp[i] + 1ll * dp[i - j] * C[i][j]) % mod;
    for(int i = 1; i <= m; ++i) {
        scanf("%s", s);
        a = read();
        _count = 0;
        for(int j = 0; j < n; ++j) _count += s[j] == '1'; 
        ans = (ans + 1ll * a * dp[_count] % mod * dp[n - _count] % mod) % mod;
    }
    print(ans);
    return 0;
}