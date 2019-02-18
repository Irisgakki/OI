#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;
const int inf = 0x3f3f3f3f;

char s[maxn];
int dp[maxn][maxn][2];

inline bool check(const char *a, int &n) {
    if(n & 1) return false;
    int mid = n >> 1;
    for(int i = 0; i < mid; ++i)
        if(a[i] != a[i + mid]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> s;
    int len = strlen(s);
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 0; i < len; ++i) dp[i][i][0] = dp[i][i][1] = 1;
    for(int l = 2; l <= len; ++l) {
        for(int i = 0; i + l - 1 < len; ++i) {
            int j = i + l - 1;
            for(int k = i; k < j; ++k) {
                dp[i][j][0] = min(dp[i][j][0], dp[i][k][0] + j - k);
                dp[i][j][1] = min(dp[i][j][1], dp[i][k][1] + 1 + dp[k + 1][j][1]);
            }
            if(check(s + i, l)) dp[i][j][0] = min(dp[i][j][0], dp[i][(i + j) >> 1][0] + 1);
            dp[i][j][1] = min(dp[i][j][1], dp[i][j][0]);
        }
    }
    cout << dp[0][len - 1][1];
    return 0;
}