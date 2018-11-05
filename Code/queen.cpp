#include <bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e6 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int n, m, x[maxn], y[maxn], cnt[maxn], ans[maxn];
std::set<int> s[maxn];

inline void reset() {
    for(int i = 1; i <= (n << 1); ++i) {
        s[i].clear();
        s[i].insert(-inf);
        s[i].insert(inf);
    }
}

inline int query(int x, int y) {
    int res = 0;
    if(*--s[x].lower_bound(y) != -inf) res++;
    if(*s[x].upper_bound(y) != inf) res++;
    return res;
}

int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) x[i] = read(), y[i] = read();
    reset();
    for(int i = 1; i <= m; ++i) s[x[i]].insert(y[i]);
    for(int i = 1; i <= m; ++i) cnt[i] += query(x[i], y[i]);
    reset();
    for(int i = 1; i <= m; ++i) s[y[i]].insert(x[i]);
    for(int i = 1; i <= m; ++i) cnt[i] += query(y[i], x[i]);
    reset();
    for(int i = 1; i <= m; ++i) s[x[i] + y[i]].insert(y[i]);
    for(int i = 1; i <= m; ++i) cnt[i] += query(x[i] + y[i], y[i]);
    reset();
    for(int i = 1; i <= m; ++i) s[x[i] - y[i] + n].insert(y[i]);
    for(int i = 1; i <= m; ++i) cnt[i] += query(x[i] - y[i] + n, y[i]);
    for(int i = 1; i <= m; ++i) {
        ans[cnt[i]]++;
    }
    for(int i = 0; i <= 8; ++i) {
        printf("%d%c", ans[i], " \n"[i == 8]);
    }
    return 0;
}