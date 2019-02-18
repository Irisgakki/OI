#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e4 + 7;
const int inf = 0x3f3f3f3f;

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
    int next, to;
} e[maxn << 1];

int head[maxn], cnt = 0;

inline void add(int u, int v) {
    e[cnt].next = head[u];
    e[cnt].to = v;
    head[u] = cnt++;
}

int tot[maxn], son[maxn], dep[maxn], par[maxn];
int idx[maxn], top[maxn], id = 0;

inline int dfs1(int now, int fa, int depth) {
    tot[now] = 1, dep[now] = depth, par[now] = fa;
    int maxson = -1;
    for(int i = head[now]; i != -1; i = e[i].next) {
        int to = e[i].to;
        if(to == fa) continue;
        tot[now] += dfs1(to, now, depth + 1);
        if(tot[to] > maxson) maxson = tot[to], son[now] = to;
    }
    return tot[now];
}

inline void dfs2(int now, int top_node) {
    idx[now] = id++, top[now] = top_node;
    if(!son[now]) return ;
    dfs2(son[now], top_node);
    for(int i = head[now]; i != -1; i = e[i].next) {
        int to = e[i].to;
        if(to != son[now] && to != par[now]) dfs2(to, to);
    }
}

#define lson o << 1
#define rson o << 1 | 1

struct Segment_Tree{
    int l, r, maxx;
} seg[maxn << 2];

inline void push_up(int o) {
    seg[o].maxx = max(seg[lson].maxx, seg[rson].maxx);
}

inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r, seg[o].maxx = 0;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
}

inline void update(int o, int p, int v) {
    if(seg[o].l == p && seg[o].r == p) {
        seg[o].maxx = v;
        return ;
    }
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(p <= mid) update(lson, p, v);
    if(p > mid) update(rson, p, v);
    push_up(o);
}

inline int query_max(int o, int l, int r) {
    if(l == seg[o].l && seg[o].r == r) return seg[o].maxx;
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(r <= mid) return query_max(lson, l, r);
    else if(l > mid) return query_max(rson, l, r);
    else return max(query_max(lson, l, mid), query_max(rson, mid + 1, r));
}

inline int query(int x, int y) {
    int t1 = top[x], t2 = top[y];
    int ans = 0;
    while(t1 != t2) {
        if(dep[t1] < dep[t2]) swap(t1, t2), swap(x, y);
        ans = max(ans, query_max(1, idx[t1], idx[x]));
        x = par[t1]; t1 = top[x];
    }
    if(x == y) return ans;
    if(dep[x] > dep[y]) swap(x, y);
    return max(ans, query_max(1, idx[son[x]], idx[y]));
}

int E[maxn][3];

int main() {
    int caseNum = read();
    while(caseNum--) {
        memset(head, -1, sizeof(head));
        memset(son, 0, sizeof(son));
        id = cnt = 0;
        n = read();
        for(int i = 0; i < n - 1; ++i) {
            E[i][0] = read(), E[i][1] = read(), E[i][2] = read();
            add(E[i][0], E[i][1]); add(E[i][1], E[i][0]);
        }
        dfs1(1, 0, 1); dfs2(1, 1);
        build(1, 0, id - 1);
        for(int i = 0; i < n - 1; ++i) {
            if(dep[E[i][0]] > dep[E[i][1]]) swap(E[i][0], E[i][1]);
            update(1, idx[E[i][1]], E[i][2]);
        }
        char s[10];
        while(scanf("%s", s) == 1) {
            if(s[0] == 'D') break;
            int x = read(), y = read();
            if(s[0] == 'Q') write(query(x, y)), puts("");
            if(s[0] == 'C') update(1, idx[E[x - 1][1]], y);
        }
    }
    return 0;
}