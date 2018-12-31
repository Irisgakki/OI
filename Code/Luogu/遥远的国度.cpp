#include <bits/stdc++.h>
#define pts puts("")

using namespace std;
typedef long long ll;
const int maxn = 3e5 + 7;
const int inf = 1 << 30;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, q, root;

struct data{
    int next, to;
};

data e[maxn << 1];
int head[maxn], val[maxn], cnt = 0;

inline void add(int u, int v) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    head[u] = cnt;
}

int tot[maxn], dep[maxn], son[maxn];
int idx[maxn], top[maxn], id = 0, a[maxn];
int anc[maxn][32];

inline int dfs1(int now, int fa, int depth) {
    tot[now] = 1, anc[now][0] = fa, dep[now] = depth;
    int maxson = -1;
    for(int i = 1; i <= 20; ++i)
        anc[now][i] = anc[anc[now][i - 1]][i - 1];
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        tot[now] += dfs1(to, now, depth + 1);
        if(tot[to] > maxson) maxson = tot[to], son[now] = to;
    }
    return tot[now];
}

inline void dfs2(int now, int top_node) {
    idx[now] = ++id; a[id] = val[now]; top[now] = top_node;
    if(!son[now]) return ;
    dfs2(son[now], top_node);
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(!idx[to]) dfs2(to, to);
    }
}

inline int lca(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    int del = dep[y] - dep[x];
    for(int i = 0; (1 << i) <= del; ++i)
        if((1 << i) & del) y = anc[y][i];
    if(x == y) return x;
    for(int i = 20; i >= 0; --i) {
        if(anc[x][i] != anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}

struct Segment_Tree{
    int l, r, minn, tag;
};

Segment_Tree seg[maxn << 2];

#define lson o << 1
#define rson o << 1 | 1

inline void up(int o) {
    seg[o].minn = min(seg[lson].minn, seg[rson].minn);
}

inline void down(int o) {
    if(seg[o].tag != -1) {
        seg[lson].tag = seg[rson].tag = seg[o].tag;
        seg[lson].minn = seg[rson].minn = seg[o].tag;
        seg[o].tag = -1;
    }
}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r, seg[o].tag = -1;
    if(l == r) {
        seg[o].minn = a[l];
        return ;
    }
    int mid = l + r >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
    up(o);
}

inline void modify(int o, int l, int r, int v) {
    if(l <= seg[o].l && seg[o].r <= r) {
        seg[o].minn = v;
        seg[o].tag = v;
        return ;
    }
    down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    if(l <= mid) modify(lson, l, r, v);
    if(r > mid) modify(rson, l, r, v);
    up(o);
}

inline int query(int o, int l, int r) {
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].minn;
    down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    int ans = inf;
    if(l <= mid) ans = min(ans, query(lson, l, r));
    if(r > mid) ans = min(ans, query(rson, l, r));
    return ans;
}

#undef lson
#undef rson

inline void Tree_modify(int x, int y, int v) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(1, idx[top[x]], idx[x], v);
        x = anc[top[x]][0];
    }
    if(dep[x] > dep[y]) swap(x, y);
    modify(1, idx[x], idx[y], v);
}

inline int getans(int x) {
    if(root == x) return query(1, 1, n);
    if(lca(root, x) == x) {
        int del = dep[root] - dep[x] - 1, y = root;
        for(int i = 0; i <= 20; ++i)
            if((1 << i) & del) y = anc[y][i];
        return min(query(1, 1, idx[y] - 1), query(1, idx[y] + tot[y], n));
    } else return query(1, idx[x], idx[x] + tot[x] - 1);
}

int main() {
    n = read(), q =  read();
    for(int i = 1; i < n; ++i) {
        int u = read(), v = read();
        add(u, v); add(v, u);
    }
    for(int i = 1; i <= n; ++i) val[i] = read();
    root = read();
    dfs1(1, 0, 1); dfs2(1, 1);
    build(1, 1, n);
    while(q--) {
        int opt = read();
        switch(opt) {
            case 1: {
                root = read();
                break;
            }
            case 2: {
                int l = read(), r = read(), v = read();
                Tree_modify(l, r, v);
                break;
            }
            case 3: {
                int x = read();
                print(getans(x)), pts;
                break;
            }
        }
    }
    return 0;
} 
