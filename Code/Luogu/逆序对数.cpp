#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 10000;

inline int read() {
  register int g = 1; register char ch;
  while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
  register int x = ch ^ '0';
  while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
  return x * g;
}

int n, k;
int dp[maxn][maxn];//dp[i][j]表示前i个数，有j个逆序对的排列数

int main() {
  n = read(), k = read();
  for(int i = 0; i <= n; ++i) dp[i][0] = 1;
  for(int i = 1; i <= n; ++i) {
    int now = dp[i - 1][0];
    for(int j = 1; j <= k; ++j) {
      if(j >= i) now -= dp[i - 1][j -i];
      now += dp[i - 1][j];
      (dp[i][j] += now) %= mod;
    }
  }
  cout << dp[n][k];
  return 0;
}