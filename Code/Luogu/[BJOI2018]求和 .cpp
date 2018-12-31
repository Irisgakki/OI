#include <bits/stdc++.h>
#define pts puts("")

using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
    return x * g;
}

inline void print(ll x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, q;

struct data{
    int next, to;
};

data e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}

inline ll fpow(ll a, int n) {
    ll res = 1;
    while(n) {
        if(n & 1) res = (res * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

int dep[maxn], anc[maxn][30];
ll val[maxn][55];
inline void dfs(int now) {
    for(int i = 1; i <= 20; ++i)
        anc[now][i] = anc[anc[now][i - 1]][i - 1];
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == anc[now][0]) continue;
        dep[to] = dep[now] + 1;
        anc[to][0] = now;
        for(int j = 1; j <= 50; ++j) val[to][j] = (fpow(dep[to], j) + val[now][j]) % mod;
        dfs(to);
    }
}

inline int lca(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    int del = dep[y] - dep[x];
    for(int i = 0; (1 << i) <= del; ++i)
        if((1 << i) & del) y = anc[y][i];
    if(x == y) return x;
    for(int i = 25; i >= 0; --i)
        if(anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}

int main() {
    n = read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    dfs(1);
    q = read();
    while(q--) {
        int u = read(), v = read(), k = read();
        print(((val[u][k] + val[v][k] - val[lca(u, v)][k] + mod) % mod - val[anc[lca(u,v)][0]][k] + mod) % mod), pts;
    }
    return 0;
}
