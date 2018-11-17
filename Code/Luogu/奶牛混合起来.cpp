#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

LL n, k, a[maxn], ans = 0;
LL dp[maxn][1 << 16];//dp[i][j]表示以i牛为结尾的状态为j时的方案数

inline void DP(){
  //初始化
  for(int i = 0; i < n; ++i)
    dp[i][1 << i] = 1;
  for(int i = 0; i < (1 << n); ++i)
    for(int j = 0; j < n; ++j)
      if(i & (1 << j))
    for(int p = 0; p < n; ++p)
      if(!(i & (1 << p)) && abs(a[j] - a[p]) > k)
         dp[p][i | (1 << p)] += dp[j][i];
  for(int i = 0; i < n; ++i)
    ans += dp[i][(1 << n) - 1];
  printf("%lld\n", ans);
}

int main() {
  scanf("%lld %lld", &n, &k);
  for(int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  DP();
  return 0;
}
