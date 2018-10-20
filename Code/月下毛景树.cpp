#include <bits/stdc++.h>
typedef long long ll;
const int maxn = 100010;
const int inf = 1 << 30;

inline int read() {
    register int x = 0, g = 1;
    register char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') g = 1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
    return x * g;
}

int n;
struct Edge{
    int next, to, val;
} e[maxn<<1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) { e[++cnt] = (Edge) {head[u], v, w}; head[u] = cnt; }
inline void ins(int u, int v, int w) { add(u, v, w); add(v, u, w); }

struct Segment{
    int l, r, addtag, moditag, sz, sum, max;
} seg[maxn<<2];

int tot[maxn], son[maxn], anc[maxn], dep[maxn], a[maxn], b[maxn];
int idx[maxn], top[maxn], size = 0;

struct Sub_tree{

    inline int dfs1(int now, int fa, int depth) {
        dep[now] = depth; anc[now] = fa; tot[now] = 1;
        int maxson = -1;
        for(register int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(to == fa) continue;
            a[to] = e[i].val;
            tot[now] += dfs1(to, now, depth + 1);
            if(tot[to] > maxson) maxson = tot[to], son[now] = to;
        }
        return tot[now];
    }

    inline void dfs2(int now, int top_node) {
        idx[now] = ++size; b[size] = a[now]; top[now] = top_node;
        if(!son[now]) return ;
        dfs2(son[now], top_node);
        for(register int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(!idx[to]) dfs2(to, to);
        }
    }

} sub;

struct Segment_Tree{
    #define lson o << 1
    #define rson o << 1 | 1
    #define mid (seg[o].l + seg[o].r) >> 1
    inline void push_up(int o) {
        seg[o].sum = seg[lson].sum + seg[rson].sum;
        seg[o].max = std::max(seg[lson].max, seg[rson].max);
    }

    inline void push_down(int o) {
        if(seg[o].moditag != -1) {
            seg[lson].moditag = seg[o].moditag;
            seg[rson].moditag = seg[o].tag;
            seg[lson].sum = seg[o].moditag * seg[lson].sz;
            seg[rson].sum = seg[o].moditag * seg[rson].sz;
            seg[lson].max = seg[o].tag;
            seg[rson].max = seg[o].tag;
            seg[o].moditag = -1;
        }
        if(seg[o].tag) {
            seg[lson].tag += seg[o].tag; seg[rson].tag += seg[o].tag;
            seg[lson].sum += seg[o].tag * seg[lson].sz;
            seg[rson].sum += seg[o].tag * seg[rson].sz;
            seg[lson].max += seg[o].tag;
            seg[rson].max += seg[o].tag;
            seg[o].tag = 0;
        }
    }

    inline void build(int o, int l, int r) {
        seg[o].moditag = -1; seg[o].addtag = 0;
        seg[o].l = l, seg[o].r = r, seg[o].sz = r - l + 1;
        if(l == r) {
            seg[o].sum = seg[o].max = b[l];
            return ;
        }
        int midd = (l + r) >> 1;
        build(lson, l, midd); build(rson, midd + 1, r);
        push_up(o);
    }

    inline void modify_node(int o, int l, int r, int v) {
        if(l <= seg[o].l && seg[o].r <= r) {
            seg[o].sum = seg[o].sz * v;
            seg[o].max = v;
            seg[o].moditag = v;
            return ;
        }
        push_down(o);
        if(l <= mid) modify_node(lson, l, r, v);
        if(r > mid) modify_node(rson, l, r, v);
        push_up(o);
    }

    inline void modify_req(int o, int l, int r, int v) {
        if(l <= seg[o].l && seg[o].r <= r) {
            seg[o].sum += seg[o].sz * v;
            seg[o].max += v;
            seg[o].tag += v;
            return ;
        }
        push_down(o);
        if(l <= mid) modify_req(lson, l, r, v);
        if(r > mid) modify_req(rson, l, r, v);
        push_up(o);
    }

    inline int query_req(int o, int l, int r) {
        if(l <= seg[o].l && seg[o].r <= r) {
            return seg[o].max;
        }
        int ans = 0;
        if(l <= mid) ans = std::max(ans, query_req(lson, l, r));
        if(r > mid) ans = std::max(ans, query_req(rson, l, r));
        push_up(o);
        return ans;
    }
} Seg;

struct Sub_Tree{

    inline void modify(int x, int y, int w) {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
            Seg.modify_node(1, idx[top[x]], idx[x], w);
            x = anc[top[x]];
        }
        if(dep[x] > dep[y]) std::swap(x, y);
        Seg.modify_node(1, idx[x] + 1, idx[y], w);
    }

    inline void assign(int x, int y, int w) {
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
            Seg.modify_req(1, idx[top[x]], idx[x], w);
            x = anc[top[x]];
        }
        if(dep[x] > dep[y]) std::swap(x, y);
        Seg.modify_node(1, idx[x] + 1, idx[y], w);
    }

    inline int query_max(int x, int y) {
        int ans = 0;
        while(top[x] != top[y]) {
            if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
            ans = std::max(ans, Seg.query_req(1, idx[top[x]], idx[x]));
            x = anc[top[x]];
        }
        if(dep[x] > dep[y]) std::swap(x, y);
        ans = std::max(ans, Seg.query_req(1, idx[x] + 1, idx[y]));
        return ans;
    }
} Sub;

int main() {
    n = read();
    for(register int i = 1; i <= n - 1; ++i) {
        int u = read(), v = read(), w = read();
        ins(u, v, w);
    }
    sub.dfs1(1, 0, 1); sub.dfs2(1, 1);
    Seg.build(1, 1, n);
    char ch[10];
    while(cin >> ch) {
        if(ch[0] == 'S') break;
        int u, v, w, k;
        if(ch[0] == 'C' && ch[1] == 'h') {
            k = read(), w = read();
            Seg.modify_node(1, idx[k << 1], idx[k << 1], w);
        }
        if(ch[0] == 'C' && ch[1] == 'o') {
            u = read(), v = read(), w = read();
            Sub.modify(u, v, w);
        }
        if(ch[0] == 'A') {
            u = read(), v = read(), w = read();
            Sub.assign(u, v, w);
        }
        if(ch[0] == 'M') {
            u = read(), v = read();
            printf("%d\n", Sub.query(u, v));
        }
    }
    return 0;
}