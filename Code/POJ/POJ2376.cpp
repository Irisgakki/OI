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
#define pts puts("")
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

int n, L;
struct Segment {
    int l, r;
    inline friend bool operator < (const Segment &a, const Segment &b) {
        return a.l == b.l ? a.r < b.r : a.l < b.l;
    }
} s[Maxn];

int main() {
    n = read(), L = read();
    rep(i,1,n) s[i].l = read(), s[i].r = read();
    std::sort(s + 1, s + n + 1);
    s[n + 1].l = INF;
    int now = 0, flag = 0, t = 0, ans = 0;
    rep(i,1,n) {
        if(s[i].l <= t + 1) {
            if(s[i].r > now) {
                now = s[i].r;
                flag = 1;
            }
            if(s[i + 1].l > t + 1 && flag == 1) {
                t = now;
                ans++;
                flag = 0;
            }
        }
    }
    if(t < L) printf("-1\n");
    else print(ans), pts;
    return 0;
}