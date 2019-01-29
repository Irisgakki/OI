#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 5e5 + 7;
const int Max_base = 63;

int n, m;
int head[maxn], cnt = 0;
long long cir[maxn], vis[maxn];
long long bas[maxn];

struct Edge{
    int next, to;
    long long val; 
};
Edge e[maxn << 1];

inline void AddEdge(int from, int to, long long val) {
    e[++cnt] = (Edge){head[from], to, val};
    head[from] = cnt;
}

inline bool insert(long long x) {
    for(int i = Max_base; i >= 0; --i) {
        if((x >> i) & 1) {
            if(!bas[i]) {
                bas[i] = x; return true;
            }
            x ^= bas[i];
        }
    }
    return false;
}

inline long long query(long long x) {
    long long ans = x;
    for(int i = Max_base; i >= 0; --i) {
        ans = max(ans, ans ^ bas[i]);
    }
    return ans;
}

inline void Dfs(int now, long long dis) {
    vis[now] = 1; cir[now] = dis;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(!vis[to]) Dfs(to, e[i].val ^ dis);
        else insert(cir[to] ^ e[i].val ^ dis);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        AddEdge(u, v, w);  AddEdge(v, u, w);     
    }
    Dfs(1, 0);
    printf("%lld\n", query(cir[n]));
    return 0;
}