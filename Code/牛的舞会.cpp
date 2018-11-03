#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 500010;
const int inf = 0x7f7f7f7f;

inline int read(){
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, m;
struct Edge{
    int next, to;
} e[maxn];
int head[maxn], cnt = 0;

inline void add(int u, int v) {
    e[++cnt] = (Edge){head[u], v};
    head[u] = cnt;
}

int dfn[maxn], low[maxn], vis[maxn], s[maxn], belong[maxn];
int id = 0, top = 0, cir = 0;

inline void tarjan(int x) {
    int now = 0;
    dfn[x] = low[x] = ++id;
    s[++top] = x;
    vis[x] = 1;
    for(register int i = head[x]; i; i = e[i].next) {
        if(!dfn[e[i].to]) {
            tarjan(e[i].to);
            low[x] = std::min(low[x], low[e[i].to]);
        } else if(vis[e[i].to]) low[x] = std::min(low[x], dfn[e[i].to]); 
    }
    if(dfn[x] == low[x]) {
        ++cir;
        while(now != x) {
            now = s[top--];
            belong[cir]++;
            vis[x] = 0;
        }
    }
}

int main() {
	n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        int u = read(), v = read();
        add(u, v);
    }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) tarjan(i);
    int ans = 0;
    for(int i = 1; i <= cir; ++i) {
        if(belong[i] > 1) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
