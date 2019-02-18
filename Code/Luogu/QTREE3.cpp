#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 7;

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

int n, q;

struct Edge{
    int next, to;
} e[maxn << 1];

int head[maxn], cnt = 0;

int tot[maxn], son[maxn], par[maxn], dep[maxn];
int idx[maxn], top[maxn], id = 0, p[maxn];

inline void add(int u, int v) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}

inline void dfs1(int now, int fa) {
    tot[now] = 1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dep[to] = dep[now] + 1, par[to] = now;
        dfs1(to, now);
        tot[now] += tot[to];
        if(tot[to] > tot[son[now]]) son[now] = to;
    }
}

inline void dfs2(int now, int top_node) {
    idx[now] = ++id, p[id] = now, top[now] = top_node;
    if(!son[now]) return ;
    dfs2(son[now], top_node);
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to != par[now] && to != son[now]) dfs2(to, to);
    }
}

#define lson o << 1
#define rson o << 1 | 1

struct Segment{
    int l, r, sum;
} seg[maxn << 2];

inline void push_up(int o) {seg[o].sum = seg[lson].sum + seg[rson].sum;}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r, seg[o].sum = 0;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(lson, l, mid), build(rson, mid + 1, r);
}

inline void modify(int o, int p) {
    if(seg[o].l == seg[o].r) {seg[o].sum ^= 1; return ;}
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(p <= mid) modify(lson, p);
    if(p > mid) modify(rson, p);
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

inline int check(int l, int r) {
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int num = query(1, l, mid);
    if(num >= 1) return check(l, mid);
    else return check(mid + 1, r);
}

inline int ask(int x) {
    int l = 0, r = 0;
    while(top[x] != 1) {
        int num = query(1, idx[top[x]], idx[x]);
        if(num >= 1) l = idx[top[x]], r = idx[x];
        x = par[top[x]];
    }
    int num = query(1, 1, idx[x]);
    if(num >= 1) l = 1, r = idx[x];
    if(l == 0 && r == 0) return -1;
    else return p[check(l, r)];
}

int main() {
    n = read(), q = read();
    for(int i = 1; i <= n - 1; ++i) {
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    dep[1] = 1;
    dfs1(1, 0); dfs2(1, 1);
    build(1, 1, n);
    for(int i = 1; i <= q; ++i) {
        int k = read(), x = read();
        if(k == 0) modify(1, idx[x]);  
        if(k == 1) write(ask(x)),puts("");
    }
    return 0;
}