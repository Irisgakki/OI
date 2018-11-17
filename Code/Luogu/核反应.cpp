#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100;
const int inf = 0x3f3f3f3f;

std::string ch;

int n, m;
int hahaha[maxn], target[maxn];
int vis[maxn]#include <bits/stdc++.h>
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

,  flag = 0;

std::map<std::string, int> mp;

inline void init(){
  std::string a[] = {
	"H","He","Li","Be","B","C","N","O","F","Ne",
	"Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca",
	"Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu",
	"Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr",
	"Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag",
	"Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba",
	"La","Ce","Pr","Nd","Pm","Sm","Eu","Gd",
	"Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta",
	"W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb",
	"Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa",
	"U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm",
  };
  for(int i = 0; i < 100; ++i)
    mp[a[i]] = i + 1;
}

inline void dfs(int x, int y, int sum) {
  if(y == n + 1) return ;
  if(vis[y]) {
    dfs(x, y + 1, sum);
    return ;
  }
  int now = sum + hahaha[y];
  if(now > target[x]) return ;
  if(now == target[x]) {
    vis[y] = 1;
    if(x == m) {
      printf("YES\n");
      flag = 1;
      return ;
    }
    dfs(x + 1, 0, 0);
    vis[y] = 0;
    return ;
  }
  dfs(x, y + 1, sum);
  if(flag == 1) return ;
  vis[y] = 1;
  dfs(x, y + 1, now);
  vis[y] = 0;
}

int main(){
  init();
  while(scanf("%d %d", &n, &m) != EOF) {
    flag = 0;
    memset(vis, 0, sizeof(vis));
    for(int i = 1; i <= n; ++i) {
      std::cin >> ch;
      hahaha[i] = mp[ch];
    }
    for(int i = 1; i <= m; ++i) {
      std::cin >> ch;
      target[i] = mp[ch];
    }
    std::sort(hahaha + 1, hahaha + 1 + n);
    std::sort(target + 1, target + 1 + m);
    if(hahaha[n] > target[m] || hahaha[1] > target[1]) flag = 0;//
    else dfs(1, 1, 0);
    if(!flag) printf("NO\n");
  }
  return 0;
}
