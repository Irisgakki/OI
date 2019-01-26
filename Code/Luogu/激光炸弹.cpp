#include <bits/stdc++.h>

using namespace std;

const int maxn = 5005;
const int inf = 0x3f3f3f3f;

int n, r;
int sum[maxn][maxn];

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> r;
  for(int i = 1; i <= n; ++i) {
    int x, y, v;
    cin >> x >> y >> v;
    sum[x + 1][y + 1] = v;
  }
  for(int i = 1; i < maxn; ++i)
    for(int j = 1; j < maxn; ++j)
      sum[i][j] = sum[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
  int ans = 0;
  for(int i = r; i < maxn; ++i)
    for(int j = r; j < maxn; ++j)
      ans = max(ans, sum[i][j] - sum[i - r][j] - sum[i][j - r] + sum[i - r][j - r]);
  cout << ans;
  return 0;
}