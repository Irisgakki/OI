#include <bits/stdc++.h>

using namespace std;

const int maxn = 3000;
const int inf = 0x3f3f3f3f;

inline int read() {
  register int g = 1; register char ch;
  while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
  register int x = ch ^ '0';
  while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
  return x * g;
}

int n, m, k, E, d;

struct Data{
  int next, to, val;
};

Data e[maxn << 1];
int head[maxn], cnt = 0;

int Use_day[maxn][maxn];
int dis[maxn], vis[maxn];
int dp[maxn][maxn];

inline void add(int u, int v, int w) {
  e[++cnt].next = head[u];
  e[cnt].to = v;
  e[cnt].val = w;
  head[u] = cnt;
}

inline bool CanUse(int node, int begin, int end) {
  for(int i = begin; i <= end; ++i)
    if(!Use_day[node][i]) return false;
  return true;
}

inline int spfa(int begin, int end) {
  memset(dis, 0x3f, sizeof(dis));
  memset(vis, 0, sizeof(vis));
  queue<int> q;
  q.push(1); dis[1] = 0;
  while(!q.empty()) {
    int now = q.front(); q.pop();
    vis[now] = 0;
    for(int i = head[now]; i; i = e[i].next) {
      int to = e[i].to;
      if(CanUse(to, begin, end) && dis[to] > dis[now] + e[i].val) {
        dis[to] = dis[now] + e[i].val;
        if(!vis[to]) {vis[to] = 1; q.push(to);}
      }
    }
  }
  if(dis[m] == inf) return inf;
  return dis[m] * (end - begin + 1);
}

int main() {
  ios::sync_with_stdio(false);
  n = read(), m = read(), k = read(), E = read();
  for(int i = 1; i <= E; ++i) {
    int u = read(), v = read(), w = read();
    add(u, v, w); add(v, u, w);
  }
  d = read();
  memset(Use_day, 1, sizeof(Use_day));
  for(int i = 1; i <= d; ++i) {
    int p = read(), a = read(), b = read();
    for(int j = a; j <= b; ++j) {
      Use_day[p][j] = 0;
    }
  }
  for(int i = 1; i <= n; ++i)
    for(int j = i; j <= n; ++j)
      dp[i][j] = spfa(i, j);
  for(int l = 2; l <= n; ++l) {
    for(int i = 1; i + l - 1 <= n; ++i) {
      int j = i + l - 1;
        for(int p = i; p < j; ++p) {
          dp[i][j] = min(dp[i][j], dp[i][p] + dp[p + 1][j] + k);
        }
    }
  }
  cout << dp[1][n];
  return 0;
}