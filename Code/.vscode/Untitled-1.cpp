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
#define pts puts("")
#define pii pair<int, int>
#define rep(i,l,r) for(register int i=l;i<=r;++i)
#define dep(i,r,l) for(register int i=r;i>=l;--i)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int maxn = 2e5 + 7;
const int INF = 0x3f3f3f3f;
const int mod = 19260817;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, T;

struct Edge{
    int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].val = w;
    head[u] = cnt;
}

int dis[maxn], vis[maxn];

inline void dijkstra() {
    priority_queue<pii, vector<pii>, greater<pii> > q;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[0] = 0;
    q.push(make_pair(0, 0));
    while(!q.empty()) {
        int now = q.top().first; q.pop();
        if(vis[now]) continue;
        vis[now] = 1;
        for(int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(dis[to] > dis[now] + e[i].val) {
                dis[to] = dis[now] + e[i].val;
                q.push(make_pair(to, dis[to]));
            }
        }
    }
}

int main() {
    n = read(), T = read();
    rep(i,1,T) add(i, i - 1, 0);
    rep(i,1,n) {
        int l = read(), r = read();
        add(l - 1, r, 1);
    }
    dijkstra();
    if(dis[T] == INF) printf("-1\n");
    else print(dis[T]), pts;
    return 0;
}