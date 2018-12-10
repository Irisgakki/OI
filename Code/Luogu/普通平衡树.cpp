#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<climits>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<numeric>
#include<iomanip>
#include<bitset>
#include<sstream>
#include<fstream>
#define debug puts("-----")
#define rep(i,l,r) for(register int i=l;i<=r;++i)
#define dep(i,r,l) for(register int i=r;i>=l;--i)

typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int Maxn = 2e5 + 7;
const int INF = 2147483647;
const int mod = 19260817;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

struct Splay{
    int ch[2];
    int val;
    int fa;
    int size;
    int cnt;
} a[Maxn];

int root, tot;

inline void up(int now) {
    a[now].size = a[a[now].ch[0]].size + a[a[now].ch[1]].size + a[now].cnt;
}

inline void rotate(int now) {
    int par = a[now].fa;
    int anc = a[par].fa;
    int k = (a[par].ch[1] == now);
    a[anc].ch[a[anc].ch[1] == par] = now;
    a[now].fa = anc;
    a[par].ch[k] = a[now].ch[k ^ 1];
    a[a[now].ch[k ^ 1]].fa = par;
    a[now].ch[k ^ 1] = par;
    a[par].fa = now;
    up(par), up(now);
}

inline void splay(int now, int tar) {
    while(a[now].fa != tar) {
        int par = a[now].fa;
        int anc = a[par].fa;
        if(anc != tar)
            (a[par].ch[0] == now) ^ (a[now].ch[0] == par) ? rotate(now) : rotate(par);
        rotate(now);
    }
    if(!tar) root = now;
}

inline void Insert(int x) {
    int now = root, par = 0;
    while(now && a[now].val != x) {
        par = now;
        now = a[now].ch[x > a[now].val];
    }
    if(now) a[now].cnt++;
    else {
        now = ++tot;
        if(par) a[par].ch[x > a[par].val] = now;
        a[now].ch[0] = a[now].ch[1] = 0;
        a[tot].fa = par;
        a[tot].val = x;
        a[tot].cnt = 1;
        a[tot].size = 1;
    }
    splay(now, 0);
}

inline void find(int x) {
    int now = root;
    if(!now) return ;
    while(a[now].ch[x > a[now].val] && x != a[now].val)
        now = a[now].ch[x > a[now].val];
    splay(now, 0);
}

inline int near(int x, int f) {
    find(x);
    int now = root;
    if(a[now].val > x && f) return now;
    if(a[now].val < x && !f) return now;
    now = a[now].ch[f];
    while(a[now].ch[f ^ 1]) now = a[now].ch[f ^ 1];
    return now;
}

inline void Delete(int x) {
    int pre = near(x, 0);
    int nex = near(x, 1);
    splay(pre, 0); splay(nex, pre);
    int del = a[nex].ch[0];
    if(a[del].cnt > 1) {
        a[del].cnt--;
        splay(del, 0);
    } else a[nex].ch[0] = 0;
}

inline int Kth(int x) {
    int now = root;
    if(a[now].size < x) return 0;
    while(1) {
        int lson = a[now].ch[0];
        if(x > a[lson].size + a[now].cnt) {
            x -= a[lson].size + a[now].cnt;
            now = a[now].ch[1];
        } else {
            if(a[lson].size >= x)
                now = lson;
            else return a[now].val;
        }
    }
}

int main() {
    int n = read();
    Insert(INF);
    Insert(-INF);
    while(n--) {
        int opt = read(), x = read();
        switch(opt) {
            case 1: Insert(x);break;
            case 2: Delete(x);break;
            case 3: {
                find(x);
                print(a[a[root].ch[0]].size); puts("");
                break;
            }
            case 4: print(Kth(x + 1)), puts("");break;
            case 5: print(a[near(x,0)].val), puts("");break;
            case 6: print(a[near(x, 1)].val), puts("");break;
        }
    }
    return 0;
}