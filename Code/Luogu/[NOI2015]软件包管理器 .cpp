#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;
const int inf = 0x3f3f3f3f;

int n;
int val[maxn];

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

int dep[maxn], tot[maxn], par[maxn], son[maxn];
int idx[maxn], top[maxn], id = 0;

inline int dfs1(int now, int fa, int depth) {
    tot[now] = 1, dep[now] = depth, par[now] = fa;
    int maxson = -1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        tot[now] += dfs1(to, now, depth + 1);
        if(tot[to] > maxson) maxson = tot[to], son[now] = to;
    }
    return tot[now];
}

inline void dfs2(int now, int top_node) {
    idx[now] = ++id, top[now] = top_node;
    if(!son[now]) return ;
    dfs2(son[now], top_node);
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(!idx[to]) dfs2(to, to);
    }
}

#define lson o << 1
#define rson o << 1 | 1

struct Segment{
    int l, r, tag, sum, size;
};

Segment seg[maxn << 2];

inline void up(int o) {
    seg[o].sum = seg[lson].sum + seg[rson].sum;
}

inline void down(int o) {
    if(seg[o].tag != -1) {
        seg[lson].tag = seg[rson].tag = seg[o].tag;
        seg[lson].sum = seg[lson].size * seg[o].tag;
        seg[rson].sum = seg[rson].size * seg[o].tag;
        seg[o].tag = -1;
    }
}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r, seg[o].size = r - l + 1, seg[o].tag = -1;
    if(l == r) {
        seg[o].sum = 1;
        return ;
    }
    int mid = l + r >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
    up(o);
}

inline void modify(int o, int l, int r, int v) {
    if(l <= seg[o].l && seg[o].r <= r) {
        seg[o].sum = seg[o].size * v;
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
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].sum;
    down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    int ans = 0;
    if(l <= mid) ans += query(lson, l, r);
    if(r > mid) ans += query(rson, l, r);
    return ans;
}

#undef lson
#undef rson

inline void Tree_modify(int x, int y, int v) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        modify(1, idx[top[x]], idx[x], v);
        x = par[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    modify(1, idx[x], idx[y], v);
}

inline int Tree_sum_query(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += query(1, idx[top[x]], idx[x]);
        x = par[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    ans += query(1, idx[x], idx[y]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 2; i <= n; ++i) {
        int x;
        cin >> x;
        x++;
        add(x, i); add(i, x);
    }
    dfs1(1, 0, 1); dfs2(1, 1);
    build(1, 1, n);
    int q;
    cin >> q;
    while(q--) {
        char opt[10];
        cin >> opt;
        int x;
        cin >> x;
        x++;
        switch(opt[0]) {
            case 'i': {
                cout << Tree_sum_query(1, x) << endl;
                Tree_modify(1, x, 0);
                break;
            }
            case 'u': {
                cout << tot[x] - query(1, idx[x], idx[x] + tot[x] - 1) << endl;
                modify(1, idx[x], idx[x] + tot[x] - 1, 1);
                break;
            }
        }
    }
    return 0;
}
