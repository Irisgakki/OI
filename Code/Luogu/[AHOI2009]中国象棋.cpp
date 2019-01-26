#include <bits/stdc++.h>

using namespace std;

const int maxn = 150;
const int inf = 0x3f3f3f3f;
const int mod = 9999973;

int n, m;
long long dp[maxn][maxn][maxn];//前i行，有j列放了一个，有k列放了两个

inline long long P(long long x) {
  return x * (x - 1) / 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  dp[0][0][0] = 1;
  for(int i = 1; i <= n; ++i) {
    for(int j = 0; j <= m; ++j) {
      for(int k = 0; k <= m - j; ++k) {
        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k]) % mod;
        if(j >= 1)                   dp[i][j - 1][k + 1] = (dp[i][j - 1][k + 1] + dp[i - 1][j][k] * j) % mod;
        if(j >= 2)                   dp[i][j - 2][k + 2] = (dp[i][j - 2][k + 2] + dp[i - 1][j][k] * P(j)) % mod;
        if(m - j - k >= 1)           dp[i][j + 1][k] = (dp[i][j + 1][k] + dp[i - 1][j][k] * (m - j - k)) % mod;
        if(m - j - k >= 2)           dp[i][j + 2][k] = (dp[i][j + 2][k] + dp[i - 1][j][k] * P(m - j - k)) % mod;
        if(m - j - k >= 1 && j >= 1) dp[i][j][k + 1] = (dp[i][j][k + 1] + dp[i - 1][j][k] * (m - j - k) * j) % mod;
      }
    }
  }
  long long ans = 0;
  for(int i = 0; i <= m; ++i) {
    for(int j = 0; j <= m - i; ++j) {
      ans = (ans + dp[n][i][j]) % mod;
    }
  }
  cout << ans % mod;
  return 0;
}