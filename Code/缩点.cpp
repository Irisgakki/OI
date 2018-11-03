#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 300010;
const int inf = 0x3f3f3f3f;

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

int n, m, w[maxn];
int dfn[maxn], low[maxn], vis[maxn], s[maxn];
int belong[maxn], val[maxn];
int id = 0, cir = 0, top = 0;
struct Edge{
    int next, to;
} e[maxn << 1], t[maxn << 1];
int head[maxn], cnt = 0;

struct Group{
    int next, to;
} g[maxn << 1];
int last[maxn], ct = 0, in[maxn];

inline void add(int u, int v) {
    e[++cnt] = (Edge){head[u], v};
    head[u] = cnt;
}

inline void ins(int u, int v) {
    g[++ct] = (Group){last[u], v};
    last[u] = ct; in[v]++;
}

inline void tarjan(int x) {
    int now = 0;
    dfn[x] = low[x] = ++id;
    vis[x] = 1;
    s[++top] = x;
    for(register int i = head[x]; i; i = e[i].next) {
        int to = e[i].to;
        if(!dfn[to]) {
            tarjan(to);
            low[x] = std::min(low[x], low[to]);
        } else if(vis[to]) low[x] = std::min(low[x], dfn[to]);
    }
    if(dfn[x] == low[x]) {
        cir++;
        while(now != x) {
            now = s[top--];
            belong[now] = cir;
            val[cir] += w[now];
            vis[now] = 0;
        }
    }
}

inline void rebuild() {
    ct = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = head[i]; j; j = e[j].next) {
            if(belong[i] != belong[e[j].to]) {
                ins(belong[i], belong[e[j].to]);
            }
        }
    }
}

int dis[maxn], ans = 0;
inline void spfa(int s) {
    std::queue<int> q;
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    q.push(belong[s]); dis[belong[s]] = val[belong[s]];
    while(!q.empty()) {
        int now = q.front(); q.pop();
        vis[now] = 0;
        for(int i = last[now]; i; i = g[i].next) {
            int to = g[i].to;
            if(dis[to] < dis[now] + val[to]) {
                dis[to] = dis[now] + val[to];
                if(!vis[to]) {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    for(int i = 1; i <= cir; ++i)
        ans = std::max(ans, dis[i]);
}

int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) w[i] = read();
    for(int i = 1; i <= m; ++i) {
        t[i].next = read(), t[i].to = read();
        add(t[i].next, t[i].to);
    }
    for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);
    rebuild();
    for(int i = 1; i <= n; ++i) {
        spfa(i);
    }
    print(ans);
    return 0;
}