#include <bits/stdc++.h>
#define rg register

template <class T> T max(T a, T b) {return a > b ? a : b;}
template <class T> T min(T a, T b) {return a > b ? b : a;}

typedef long long ll;
const int maxn = 100010;

inline int read() {
  rg int g = 1; rg char ch;
  while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
  rg int x = ch ^ '0';
  while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
  return x * g;
}

int n, u, v;
int a[maxn];
int dp[maxn][2], fa[maxn];

struct Edge{
  int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) {e[++cnt] = (Edge){head[u], v}; head[u] = cnt;}

inline void dfs(int now) {
  dp[now][1] += a[now];
  for(rg int i = head[now]; i; i = e[i].next) {
    int to = e[i].to;
    dfs(to);
    dp[now][0] += max(dp[to][0], dp[to][1]);
    dp[now][1] += dp[to][0];
  }
}

int main() {
  n = read();
  for(rg int i = 1; i <= n; ++i) a[i] = read();
  while(scanf("%d %d", &u, &v)) {
    if(!u && !v) break;
    add(v, u);
    fa[u] = v;
  }
  for(rg int i = 1; i <= n; ++i) {
    if(fa[i] == 0) {
      dfs(i);
      printf("%d\n", max(dp[i][0], dp[i][1]));
      return 0;
    }
  }
  return 0;
}
