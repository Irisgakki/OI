#include <bits/stdc++.h>

using namespace std;

const int maxn = 3000;
const int inf = 0x3f3f3f3f;

int dp[maxn][maxn];
int n, beginlevel, maxlevel;
int level[maxn];

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> beginlevel >> maxlevel;
  for(int i = 1; i <= n; ++i) cin >> level[i];
  dp[0][beginlevel] = 1;
  for(int i = 1; i <= n; ++i) {
    for(int j = 0; j + level[i] <= maxlevel; ++j) {
      if(dp[i - 1][j + level[i]]) dp[i][j] = 1;
    }
    for(int j = maxlevel; j - level[i] >= 0; --j) {
      if(dp[i - 1][j - level[i]]) dp[i][j] = 1;
    }
  }
  for(int i = maxlevel; i >= 0; --i)
    if(dp[n][i]) {cout << i; return 0;}
  cout << "-1";
  return 0;
}