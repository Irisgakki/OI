#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)

using namespace std;

const int maxn = 2010;
const long long inf = 1ll << 60;

int n;
long long dp[maxn][maxn];
int a[maxn], b[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    rep(i,1,n) cin >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    long long last;
    rep(i,1,n) {
        last = inf;
        rep(j,1,n) {
            last = min(last, dp[i - 1][j]);
            dp[i][j] = last + abs(b[j] - a[i]);
        }
    }
    long long ans = inf;
    rep(i,1,n) ans = min(ans, dp[n][i]);
    cout << ans;
    return 0;
}