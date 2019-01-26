#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 60;
const int inf = 0x3f3f3f3f;

int n, m, t;
int dp[maxn][maxn][2550];
int sum[maxn][maxn];
int bag[2550];
char ch[maxn];


int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m >> t;
  for(int i = 1; i <= n; ++i) {
    cin >> ch;
    for(int j = 1; j <= m; ++j) {
      sum[i][j] = sum[i][j - 1] + (ch[j - 1] == '1');
    }
  }
  memset(dp, 0, sizeof(dp));
  for(int r = 1; r <= n; ++r) {
    for(int j = 1; j <= min(m, t); ++j) {
      for(int i = 1; i <= m; ++i) {
        dp[r][i][j] = 0;
        for(int k = 0; k < i; ++k) {
          int tmp = max(sum[r][i] - sum[r][k], (i - k) - (sum[r][i] - sum[r][k]));
          dp[r][i][j] = max(dp[r][i][j], dp[r][k][j - 1] + tmp);
        }
      }
    }
  }
  // for(int i = 1; i <= n; ++i) {
  //   cout << dp[i][m][3] << endl;
  // }
  for(int i = 1; i <= n; ++i) {
    for(int j = t; j >= 0; --j) {
      for(int k = 1; k <= t; ++k) {
        if(j - k >= 0 && bag[j] < bag[j - k] + dp[i][m][k])
          bag[j] = bag[j - k] + dp[i][m][k];
      }
    }
  }
  cout << bag[t];
  return 0;
}