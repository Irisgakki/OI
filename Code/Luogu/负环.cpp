//luogu O2
#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int read() {
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

int T;
int n, m;
struct Edge{
    int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0, _count[maxn];

inline void add(int u, int v, int w) {
    e[++cnt] = (Edge){head[u], v, w};
    head[u] = cnt;
}

inline void ins(int u, int v, int w) {
    add(u, v, w); add(v, u, w);
}

int dis[maxn], vis[maxn], flag = 0;
inline void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    std::queue<int> q;
    q.push(1);
    dis[1] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        vis[now] = 0;
        if(_count[now] >= n) {
            flag = 1;
            return ;
        }
        for(int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(dis[to] > dis[now] + e[i].val) {
                dis[to] = dis[now] + e[i].val;
                if(!vis[to]) {
                    vis[to] = 1;
                    _count[to]++;
                    q.push(to);
                    if(_count[to] >= n) {
                        flag = 1;
                        return ;
                    }
                }
            }
        }
    }
}

int main() {
    T = read();
    while(T--) {
        memset(_count, 0, sizeof(_count));
        memset(head, 0, sizeof(head));
        cnt = flag = 0;
        n = read(), m = read();
        for(int i = 1; i <= m; ++i) {
            int u = read(), v = read(), w = read();
            if(w < 0) add(u, v, w);
            else ins(u, v, w);
        }
        spfa();
        if(flag) printf("YE5\n");
        else printf("N0\n");
    }
    return 0;
}