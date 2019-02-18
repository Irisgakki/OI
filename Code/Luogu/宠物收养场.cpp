#include <bits/stdc++.h>

using namespace std;

struct Splay{
    int ch[2];
    int val, par, size, cnt;
};

Splay t[200010];
int n;
int tot, root;

inline void maintain(int x) {t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + t[x].cnt;}

inline void rotate(int x) {
    int y = t[x].par, z = t[y].par;
    int k = t[y].ch[1] == x;
    t[z].ch[t[z].ch[1] == y] = x, t[x].par = z;
    t[y].ch[k] = t[x].ch[k ^ 1], t[t[x].ch[k ^ 1]].par = y;
    t[x].ch[k ^ 1] = y, t[y].par = x;
    maintain(y), maintain(x);
}

inline void splay(int x, int goal) {
    while(t[x].par != goal) {
        int y = t[x].par, z = t[y].par;
        if(z != goal)
            (t[z].ch[0] == y) ^ (t[y].ch[0] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if(!goal) root = x;
}

inline void insert(int x) {
    int u = root, par = 0;
    while(u && t[u].val != x) par = u, u = t[u].ch[x > t[u].val];
    if(u) t[u].cnt++;
    else {
        u = ++tot;
        if(par) t[par].ch[x > t[par].val] = u;
        t[u].ch[0] = t[u].ch[1] = 0;
        t[u].par = par, t[u].val = x;
        t[u].size = t[u].cnt = 1;
    }
    splay(u, 0);
}

inline void find(int x) {
    int u = root;
    if(!u) return ;
    while(t[u].ch[x > t[u].val] && x != t[u].val)
        u = t[u].ch[x > t[u].val];
    splay(u, 0);
}

inline int near(int x, int k) {
    find(x);
    int u = root;
    if(t[u].val > x && k) return u;
    if(t[u].val < x && !k) return u;
    u = t[u].ch[k];
    while(t[u].ch[k ^ 1]) u = t[u].ch[k ^ 1];
    return u; 
}

inline void del(int x) {
    int pre = near(x, 0), nex = near(x, 1);
    splay(pre, 0); splay(nex, pre);
    int Del = t[nex].ch[0];
    if(t[Del].cnt > 1) {
        t[Del].cnt--; splay(Del, 0);
    } else t[nex].ch[0] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    insert(1 << 30); insert(-(1 << 30));
    int ans = 0, num = 0, now;
    for(int i = 1; i <= n; ++i) {
        int opt, x;
        cin >> opt >> x;
        if(num == 0) {
            now = opt, num++;
            insert(x);
        } else if((opt ^ now) == 0)
            insert(x), num++;
          else {
            int _pre = near(x, 0), _nex = near(x, 1);
            int a = abs(x - t[_pre].val), b = abs(x - t[_nex].val);
            if(a <= b) {
                ans += a; del(t[_pre].val);
            } else {
                ans += b; del(t[_nex].val);
            }
            num--, ans %= 1000000;
        }
    }
    cout << ans;
    return 0;
}