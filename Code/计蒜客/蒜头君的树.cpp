#include <bits/stdc++.h>
#define int long long
const int maxn = 100010;
const int inf = 1e18;
const int mod = 998244353;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

inline int read(){
    register int x = 0, g = 1; register char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
    return x * g;   
}

int n, m;
struct Edge{
    int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) { e[++cnt] = (Edge) {head[u], v, w}; head[u] = cnt; }
inline void ins(int u, int v, int w) { add(u, v, w); add(v, u, w); }

int tot[maxn], node[maxn];

inline int dfs(int now, int fa){
    tot[now] = 1;
    for(int i = head[now]; i; i = e[i].next){
        int to = e[i].to;
        if(to == fa) continue;
        tot[now] += dfs(to, now);   
    }
    return tot[now];
}

signed main(){
//  freopen("tree.in","r",stdin);
//  freopen("tree.out","w",stdout);
    n = read();
    for(int i = 2; i <= n; ++i) {
        int v = read(), w = read();
        ins(i, v, w);
        node[i] = w;
    }
    dfs(1, 0);
    static int sum;
    for(int i = 2; i <= n; ++i) {
        sum += tot[i] * (n - tot[i]) * node[i];
    }
    printf("%lld\n", sum);
    m = read();
    while(m--){
        int u = read(), w = read();
        sum -= tot[u] * (n - tot[u]) * node[u];
        node[u] = w;
        sum += tot[u] * (n - tot[u]) * node[u];
        printf("%lld\n", sum);
    }
    return 0;
}