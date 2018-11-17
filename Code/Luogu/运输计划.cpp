#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
using namespace std;
typedef long long ll;
const int maxn = 501000;
const int inf = 0x7f7f7f7f;

struct edge{
    int next, to, val;
}e[maxn<<1];
int head[maxn], cnt=0;
int n, m;
int s[maxn], t[maxn];

inline void add(int u,int v,int w){e[++cnt]=(edge){head[u], v, w};head[u]=cnt;}
inline void ins(int u,int v,int w){add(u,v,w);add(v,u,w);}

int lgn, dep[maxn], anc[maxn][31];
int dis[maxn], dif[maxn], savelca[maxn], sz = 0, node[maxn], preval[maxn];
inline void dfs(int now){
    node[++sz] = now;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == anc[now][0]) continue;
        dis[to] = dis[now] + e[i].val;
        preval[to] = e[i].val;
        anc[to][0] = now;
        dep[to] = dep[now] + 1;
        dfs(to);
    }
}

inline void calanc() {
    for(int j = 1; (1 << j) <= n; ++j)
        for(int i = 1; i <= n; ++i)
            anc[i][j] = anc[anc[i][j-1]][j-1];
}

inline int lca(int x,int y) {
    if(dep[x] > dep[y]) swap(x, y);
    int del = dep[y] - dep[x];
    for(int i = 0; (1 << i) <= del; ++i)
        if((1 << i) & del) y = anc[y][i];
    if(x == y) return x;
    for(int i = 30; i >= 0; --i) {
        if(anc[x][i] != anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}

int l = -inf, r = -inf;
int f[maxn];
inline bool check(int mid) {
    memset(f, 0, sizeof(f));
    sz = 0;
    for(int i = 1; i <= m; ++i) {
        if(dif[i] > mid) {
            ++f[s[i]];
            ++f[t[i]];
            f[savelca[i]]-=2;
            ++sz;
        }
    }
    for(int i = n; i >= 1; --i) {
        f[anc[node[i]][0]] += f[node[i]];
        if(preval[node[i]] >= r - mid && f[node[i]] == sz) return true;
    }
    return false;
}

inline void solve(int l, int r) {
    while(l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid - 1;
        else l = mid + 1;
    }
    printf("%d\n", l);
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n - 1; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        ins(u,v,w);
        l = max(l, w);
    }
    dfs(1);
    calanc();
    dep[1] = 1; 
    for(int i = 1; i <= m; ++i) {
        scanf("%d %d", &s[i], &t[i]);
        savelca[i] = lca(s[i], t[i]);
        dif[i] = dis[s[i]] + dis[t[i]] - (dis[savelca[i]] << 1);
        r = max(r, dif[i]);
    }
    solve(r - l, r + 1);
    return 0;
}