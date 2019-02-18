#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 10;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
    return x * g;
}

inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int n;

struct Edge{
    int next, to, val;
} e[maxn << 1];

int head[maxn], cnt = 0;
int d[maxn];

inline void add(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].val = w;
    head[u] = cnt;
}

int tot[maxn], son[maxn], dep[maxn], par[maxn];
int idx[maxn], p[maxn], top[maxn], id = 0;

inline void init() {
    memset(head, 0, sizeof(head));
    memset(son, 0, sizeof(son));
    memset(idx, 0, sizeof(idx));
    memset(p, 0, sizeof(p));
    memset(d, 0, sizeof(d)); 
    id = cnt = 0;
}

inline void dfs1(int now, int fa) {
    tot[now] = 1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dep[to] = dep[now] + 1; par[to] = now; d[to] = e[i].val;
        dfs1(to, now);
        tot[now] += tot[to];
        if(tot[to] > tot[son[now]]) son[now] = to;
    }
}

inline void dfs2(int now, int top_node) {
    idx[now] = ++id, top[now] = top_node, p[id] = now;
    if(!son[now]) return ;
    dfs2(son[now], top_node);
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to != par[now] && to != son[now]) dfs2(to, to);
    }
}

#define lson o << 1
#define rson o << 1 | 1

struct Segment_Tree{
    int l, r, sum;
} seg[maxn << 2];

inline void push_up(int o) {
    seg[o].sum = seg[lson].sum + seg[rson].sum;
}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r;
    if(l == r) {
        seg[o].sum = d[p[l]];
        return ;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
    push_up(o);
}

inline int query(int o, int l, int r) {
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].sum;
    int mid = (seg[o].l + seg[o].r) >> 1;
    int ans = 0;
    if(l <= mid) ans += query(lson, l, r);
    if(r > mid) ans += query(rson, l, r);
    return ans;
}

#undef lson
#undef rson

inline int ask(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += query(1, idx[top[x]], idx[x]);
        x = par[top[x]];
    }
    if(x == y) return ans;
    if(dep[x] > dep[y]) swap(x, y);
    ans += query(1, idx[x] + 1, idx[y]);
    return ans;
}

inline int LCA(int x, int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] > dep[top[y]]) x = par[top[x]];
        else y = par[top[y]];
    }
    if(dep[x] < dep[y]) return x;
    return y;
}

inline int Kth(int x, int y, int k) {
    int lca = LCA(x, y);
    if(dep[x] - dep[lca] + 1 >= k) {
        while(dep[top[x]] > dep[lca]) {
            int dis = dep[x] - dep[top[x]] + 1;
            if(dis >= k) break;
            k -= dis;
            x = par[top[x]];
        }
        return p[idx[x] - k + 1];
    } else {
        k -= dep[x] - dep[lca] + 1;
        k = dep[y] - dep[lca] - k + 1;
        while(dep[top[y]] > dep[lca]) {
            int dis = dep[y] - dep[top[y]] + 1;
            if(dis >= k) break;
            k -= dis;
            y = par[top[y]];
        }
        return p[idx[y] - k + 1];
    }
}

int main() {
    int caseNum = read();
    while(caseNum--) {
        init();
        n = read();
        for(int i = 1; i <= n - 1; ++i) {
            int u = read(), v = read(), w = read();
            add(u, v, w); add(v, u, w);
        }
        dfs1(1, 0); dfs2(1, 1);
        build(1, 1, n);
        char s[10];
        while(scanf("%s", s) == 1) {
            if(s[1] == 'O') break;
            if(s[1] == 'I') {
                int a = read(), b = read();
                write(ask(a, b)), puts("");
            }
            if(s[1] == 'T') {
                int a = read(), b = read(), k = read();
                write(Kth(a, b, k)), puts("");
            }
        }
    }
    return 0;
}