#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<climits>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<numeric>
#include<iomanip>
#include<bitset>
#include<sstream>
#include<fstream>
#define debug puts("-----")
#define rg register
#define pts puts("")
#define pii pair<int, int>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int maxn = 3000010;
const ll INF = 1e18;
const int mod = 19260817;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
    return x * g;
}

inline void print(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n;
int s, t;
struct Edge{
    int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) {
    e[++cnt] = (Edge){head[u], v, w};
    head[u] = cnt;
}

ll dis[maxn];
int vis[maxn];

inline void spfa() {
    for(int i = s; i <= t + 1; ++i)
        dis[i] = INF;
    memset(vis, 0, sizeof(vis));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        vis[now] = 0;
        for(int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(dis[to] > dis[now] + e[i].val) {
                dis[to] = dis[now] + e[i].val;
                if(!vis[to]) {vis[to] = 1; q.push(to);}
            }
        }
    }
}

int main() {
    n = read(), s = read(), t = read();
    for(int i = s; i <= t + 1; ++i) add(i + 1, i, 0);
    for(int i = 1; i <= n; ++i) {
        int l = read(), r = read(), val = read();
        if(l <= t && r >= s) {
            add(max(l, s), min(r + 1, t + 1), val);
            add(min(r + 1, t + 1), max(l, s), val);
        }
    }
    spfa();
    if(dis[t + 1] == INF) printf("-1\n");
    else print(dis[t + 1]);
    return 0;
}