#include <bits/stdc++.h>
#define int long long
const int inf = 1e18;
const int mod = 9901;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

inline int read(){
    register int x = 0, g = 1;
    register char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
    return x * g;
}

const int maxn = 100010;
const int Max_ = 50;

static int n, a[maxn], suf[maxn], b[maxn];
static int dp[maxn];

signed main(){
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) b[i] = log2(a[i]);
    for(int i = n; i >= 1; --i) suf[i] = suf[i + 1] + b[i];
    // for(int i = n; i >= 1; --i) printf("%d ", suf[i]);
    int ans = inf;
    memset(dp, 0x10, sizeof(dp));
    dp[0] = 0;
    for(int i = 1; i <= n; ++i){
        for(int j = Max_ - 1; j >= 1; --j){
            if((ans >> j) >= a[i]) dp[j] = std::min(dp[j] + (a[i] << j), dp[j - 1] + (int)log2(a[i]) + j - 1);
            else dp[j] = dp[j - 1] + (int)log2(a[i]) + j - 1;
        }
        dp[0] += a[i];
        ans = std::min(ans, dp[Max_ - 1] + suf[i + 1] + 1ll * (n - i) * (Max_ * 2 - 3 + n - i) / 2);
    }
    for(int i = 0; i <= Max_; ++i)
        ans = std::min(ans, dp[i]);
    printf("%lld\n", ans);
    return 0;
}