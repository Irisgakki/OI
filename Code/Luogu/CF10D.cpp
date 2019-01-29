#include <bits/stdc++.h>

using namespace std;

const int maxn = 500;
const int inf = 0x3f3f3f3f;

int n, m;
int a[maxn], b[maxn], pre[maxn][maxn];
int dp[maxn][maxn];
int lics[maxn];
int ans = 0, pos = 0, top = 0;

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for(int i = 1; i <= n; ++i) cin >> a[i];
  cin >> m;
  for(int i = 1; i <= m; ++i) cin >> b[i];
  a[0] = b[0] = -1;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      if(a[i] == b[j]) {
        for(int k = 0; k < j; ++k) {
          if(b[k] < a[i] && dp[i][j] < dp[i - 1][k] + 1) {
            dp[i][j] = dp[i - 1][k] + 1;
            pre[i][j] = k;
          }
        }
      } else {
        dp[i][j] = dp[i - 1][j];
        pre[i][j] = pre[i - 1][j];
      }
    }
  }
  for(int i = 1; i <= m; ++i) {
    if(ans < dp[n][i]) {
      ans = dp[n][i];
      pos = i;
    }
  }
  cout << ans << '\n';
  for(; pos; pos = pre[n][pos])
    lics[++top] = b[pos];
  while(top) cout << lics[top--] << " ";
  return 0;
}