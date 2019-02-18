#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)

using namespace std;
const int maxn = 2e5 + 7;

int n, m, root, tot;
struct Splay{
    int ch[2];
    int par;
    int val;
    int tag;
    int cnt;
    inline void init(int x, int fa) {
        par = ch[0] = ch[1] = 0;
        cnt = 1; val = x; par = fa;
    }
} t[maxn];

inline void push_up(int x) {
    t[x].cnt = t[t[x].ch[0]].cnt + t[t[x].ch[1]].cnt + 1;
}

inline void push_down(int x) {
    if(t[x].tag) {
        t[t[x].ch[0]].tag ^= 1;
        t[t[x].ch[1]].tag ^= 1;        
        t[x].tag = 0;
        swap(t[x].ch[0], t[x].ch[1]);
    }
}

inline void rotate(int x) {
    int y = t[x].par;
    int z = t[y].par;
    int k = t[y].ch[1] == x;
    t[z].ch[t[z].ch[1] == y] = x; t[x].par = z;
    t[y].ch[k] = t[x].ch[k ^ 1]; t[t[x].ch[k ^ 1]].par = y;
    t[x].ch[k ^ 1] = y; t[y].par = x;
    push_up(y);push_up(x);
}

inline void splay(int x,int goal){
    while(t[x].par != goal)
    {
        int y = t[x].par; int z = t[y].par;
        if(z != goal)
            (t[z].ch[1] == y) ^ (t[y].ch[1] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if(goal == 0) root = x;
}

inline void insert(int x) {
    int u = root, par = 0;
    while(u) par = u, u = t[u].ch[x > t[u].val];
    u = ++tot;
    if(par) t[par].ch[x > t[par].val] = u;
    t[u].init(x, par);
    splay(u, 0);
}

inline int Kth(int k) {
    int u = root;
    while(1) {
        push_down(u);
        if(t[t[u].ch[0]].cnt >= k) u = t[u].ch[0];
        else if(t[t[u].ch[0]].cnt + 1 == k) return u;
        else k -= t[t[u].ch[0]].cnt + 1, u = t[u].ch[1];
    }
}

inline void Flip(int l, int r) {
    l = Kth(l);
    r = Kth(r + 2);
    splay(l, 0);
    splay(r, l);
    t[t[t[root].ch[1]].ch[0]].tag ^= 1;
}

inline void write(int u) {
    push_down(u);
    if(t[u].ch[0]) write(t[u].ch[0]);
    if(t[u].val > 1 && t[u].val < n + 2) printf("%d ", t[u].val - 1);
    if(t[u].ch[1]) write(t[u].ch[1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    rep(i,1,n+2) insert(i);
    while(m--) {
        int l, r;
        cin >> l >> r;
        Flip(l, r);
    }
    write(root);
    return 0;
}