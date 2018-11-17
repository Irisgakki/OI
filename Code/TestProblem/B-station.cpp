#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 150010;
const int inf = 0x3f3f3f3f;

int cost[maxn];
struct node{
  int num;
  friend bool operator < (const node &a, const node &b) {
    return cost[a.num] < cost[b.num];
  }
};

int n;
int l[maxn], p[maxn], pre[maxn];

std::priority_queue<node> q;

int main(){
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    int tmp;
    scanf("%d %d %d", &tmp, l + i, p + i);
    pre[i] = pre[i - 1] + tmp;
    cost[i] = pre[i] - l[i];
  }
  int ans = n, minn = p[n], now = 0;
  for(int i = n; i >= 1; --i){
    now += p[i];
    q.push((node){i});
    while(q.size() && cost[q.top().num] > pre[i - 1]){
      now -= p[q.top().num];
      q.pop();
    }
    if(now < minn) {
      ans = i;
      now = minn;
    }
  }
  for(int i = ans; i <= n; ++i) {
    if(pre[ans - 1] >= cost[i])
      printf("%d\n", i);
  }
  return 0;
}

