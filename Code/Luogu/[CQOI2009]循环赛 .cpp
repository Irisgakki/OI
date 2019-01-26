#include <cstdio>
#include <iostream>

using namespace std;
const int maxn = 10;
const int inf = 0x3f3f3f3f;
const int score[] = {3, 1, 0, 0};

int n, ans = 0;
int a[maxn], b[maxn];

inline void dfs(register int u, register int v) {
  if(b[u] > a[u] || b[v] > a[v]) return ;
  if(b[u] + (n - v + 1) * 3 < a[u]) return ;
  if(u == n) {
    ++ans;
    return ;
  }
  if(v == n) {
    register int del = a[u] - b[u];
    if(del == 2) return ;
    if(del > 3) return ;
    b[v] += score[del];
    if(b[v] <= a[v]) dfs(u + 1, u + 2);
    b[v] -= score[del];
    return ;
  }
  b[u] += 3; if(b[u] <= a[u]) dfs(u, v + 1); b[u] -= 3;
  b[v] += 3; if(b[v] <= a[v]) dfs(u, v + 1); b[v] -= 3;
  b[u]++, b[v]++; dfs(u, v + 1); b[u]--, b[v]--;
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for(int i = 1; i <= n; ++i) cin >> a[i];
  dfs(1, 2);
  cout << ans;
  return 0;
}
