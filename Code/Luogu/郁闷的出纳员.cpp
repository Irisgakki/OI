#include <bits/stdc++.h>
using namespace std;

struct Splay{
    int ch[2];
    int val, par, cnt, size;
};

Splay t[100010];
int n, minn;
int tot, root, v;

inline void maintain(int x) {
    t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + t[x].cnt;
}

void rotate(int x) {
    int y = t[x].par, z = t[y].par;
    int k = (t[y].ch[1] == x);
    t[z].ch[t[z].ch[1] == y] = x; t[x].par = z;
    t[y].ch[k] = t[x].ch[k ^ 1]; t[t[x].ch[k ^ 1]].par = y;
    t[x].ch[k ^ 1] = y; t[y].par = x;
    maintain(y); maintain(x);
}

void splay(int x, int goal) {
    while(t[x].par != goal) {
        int y = t[x].par, z = t[y].par;
        if(z != goal) (t[z].ch[0] == y) ^ (t[y].ch[0] == x) ? rotate(x) : rotate(y);
        rotate(x);
    }
    if(!goal) root = x;
}

void insert(int x) {
    int u = root, par = 0;
    while(u && x != t[u].val) par = u, u = t[u].ch[x > t[u].val];
    if(u) t[u].cnt++;
    else {
        u = ++tot;
        if(par) t[par].ch[x > t[par].val] = u;
        t[u].ch[0] = t[u].ch[1] = 0;
        t[u].val = x, t[u].par = par;
        t[u].size = t[u].cnt = 1;
    }
    splay(u, 0);
}

void find(int x) {
    int u = root;
    if(!u) return ;
    while(t[u].ch[x > t[u].val] && x != t[u].val)
        u = t[u].ch[x > t[u].val];
    splay(u, 0);
}

int near(int x, int k) {
    find(x);
    int u = root;
    if(t[u].val >= x && k) return u;
    if(t[u].val <= x && !k) return u;
    u = t[u].ch[k];
    while(t[u].ch[k ^ 1]) u = t[u].ch[k ^ 1];
    return u;
}

void Delete(int x) {
    int pre = near(x, 0), nex = near(x, 1);
    splay(pre, 0); splay(nex, pre);
    int del = t[nex].ch[0];
    if(t[del].cnt > 1) t[del].cnt--, splay(del, 0);
    else t[nex].ch[0] = 0;
}

int Kth(int x) {
    int u = root;
    if(t[u].size < x || x <= 0) return -(1 << 30);
    while(1) {
        int lson = t[u].ch[0];
        if(x > t[lson].size + t[u].cnt) {
            x -= t[lson].size + t[u].cnt;
            u = t[u].ch[1];
        } else {
            if(t[lson].size >= x) u = lson;
            else return t[u].val;
        }
    }
}

int main() {
    scanf("%d %d", &n, &minn);
    int p = 0, ans = 0;
    insert(1 << 30);
    for(int i = 1; i <= n; ++i) {
        char opt; int k;
        scanf(" %c %d", &opt, &k);
        switch(opt) {
            case 'I': {
                if(k >= minn) {
                    insert(k - v);
                    p++;
                }
                break;
            }
            case 'A': {
                v += k;
                break;
            }
            case 'S': {
                v -= k;
                int nex = near(minn - v, 1);
                splay(nex, 0);
                ans += t[t[root].ch[0]].size;
                p -= t[t[root].ch[0]].size;
                t[t[root].ch[0]].size = t[t[root].ch[0]].cnt = 0;
                t[root].ch[0] = 0, t[0].size = 0;
                maintain(root);
                break;
            }
            case 'F': {
                int rank = Kth(p - k + 1);
                printf("%d\n", rank == -(1 << 30) ? -1 : (rank + v));
                break;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}