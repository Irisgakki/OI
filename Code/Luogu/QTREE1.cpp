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

int from[maxn], to[maxn], val[maxn];
int head[maxn], cnt = 0;

int tot[maxn], son[maxn], dep[maxn], par[maxn];
int idx[maxn], top[maxn], d[maxn], p[maxn], id = 0;

inline void init() {
    memset(head, 0, sizeof(head));
    memset(son, 0, sizeof(son));
    cnt = id = 0;
}

inline void add(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].val = w;
    head[u] = cnt;
}

inline void dfs1(int now, int fa) {
    tot[now] = 1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        dep[to] = dep[now] + 1, par[to] = now, d[to] = e[i].val;
        dfs1(to, now);
        tot[now] += tot[now];
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
    int l, r, maxx;
}seg[maxn << 2];

inline void push_up(int o) {
    seg[o].maxx = max(seg[lson].maxx, seg[rson].maxx);
}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r;
    if(l == r) {
        seg[o].maxx = d[p[l]];
        return ;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
    push_up(o);
}

inline void update(int o, int k, int v) {
    if(seg[o].l == k && seg[o].r == k) {
        seg[o].maxx = v;
        return ;
    }
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(k <= mid) update(lson, k, v);
    if(k > mid) update(rson, k, v);
    push_up(o);
}

inline int query_max(int o, int l, int r) {
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].maxx;
    int mid = (seg[o].l + seg[o].r) >> 1;
    int ans = 0;
    if(r <= mid) return query_max(lson, l, r);
    else if(l > mid) return query_max(rson, l, r);
    else return max(query_max(lson, l, mid), query_max(rson, mid + 1, r));
}

#undef lson
#undef rson

inline int query(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        if(top[x] == 1) ans = max(ans, query_max(1, idx[top[x]] + 1, idx[x]));/////////
        else ans = max(ans, query_max(1, idx[top[x]], idx[x]));
        x = par[top[x]];
    }
    if(x == y) return ans;//////////////////
    if(dep[x] > dep[y]) swap(x, y);
    ans = max(ans, query_max(1, idx[x] + 1, idx[y]));//////////
    return ans;
}

int main() {
    int caseNum = read();
    while(caseNum--) {
        init();
        n = read();
        for(int i = 1; i <= n - 1; ++i) {
            from[i] = read(), to[i] = read(), val[i] = read();
            add(from[i], to[i], val[i]);
            add(to[i], from[i], val[i]);
        }
        dfs1(1, 0); dfs2(1, 1);
        build(1, 1, n);
        char s[20];
        while(scanf("%s", s) == 1) {
            if(s[0] == 'D') break;
            int x = read(), y = read();
            if(s[0] == 'Q') write(query(x, y)), puts("");
            if(s[0] == 'C') {
                if(dep[from[x]] < dep[to[x]]) swap(from[x], to[x]);/////////
                update(1, idx[from[x]], y);
            }
        }
    }
    return 0;
}