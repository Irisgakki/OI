#include <bits/stdc++.h>

using namespace std;

const int maxn = 2500;
const int inf = 0x3f3f3f3f;

int n, m;
int G[maxn][maxn];
int h[maxn][maxn], l[maxn][maxn], r[maxn][maxn];

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      cin >> G[i][j];
      h[i][j] = 1;
      l[i][j] = r[i][j] = j;
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 2; j <= m; ++j)
      if(G[i][j] == G[i][j - 1] ^ 1) l[i][j] = l[i][j - 1];
    for(int j = m - 1; j >= 1; --j)
      if(G[i][j] == G[i][j + 1] ^ 1) r[i][j] = r[i][j + 1];
  }
  int S1 = 1, S2 = 1;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      if(i > 1 && G[i][j] == G[i - 1][j] ^ 1) {
        h[i][j] = h[i - 1][j] + 1;
        l[i][j] = max(l[i][j], l[i - 1][j]);
        r[i][j] = min(r[i][j], r[i - 1][j]);
      }
      int x = r[i][j] - l[i][j] + 1;
      int y = h[i][j];
      int z = min(x, y);
      S1 = max(S1, z * z);
      S2 = max(S2, x * y);
    }
  }
  cout << S1 << '\n' << S2;
  return 0;
}