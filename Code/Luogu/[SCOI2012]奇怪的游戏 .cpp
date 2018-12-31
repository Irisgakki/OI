/**************************************************************
    Problem: 2756
    User: lgakki
    Language: C++
    Result: Accepted
    Time:10872 ms
    Memory:1588 kb
****************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 70;
const int maxm = 5000;
const ll inf = 1LL<<40;

inline void readll(ll &x) {
    int g=1;x=0;char m=getchar();
    while(m<'0'||m>'9'){if(m=='-')g=-1;m=getchar();}
    while(m>='0'&&m<='9'){x=(x<<1)+(x<<3)+m-'0';m=getchar();}
    x*=g;
}

inline void readint(int &x) {
    int g=1;x=0;char m=getchar();
    while(m<'0'||m>'9'){if(m=='-')g=-1;m=getchar();}
    while(m>='0'&&m<='9'){x=(x<<1)+(x<<3)+m-'0';m=getchar();}
    x*=g;
}

struct edge{
    int next, to;
    ll flow;
}e[maxm<<1];
int head[maxm], cnt = 1, cur[maxm], dep[maxm];

int T, s, t;
int n, m;
ll map[maxn][maxn], col[maxn][maxn];
ll sb, sw, cb, cw, maxx;

int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, 1, 0, -1, 0};

inline ll pos(int i, int j) {return (i - 1) * m + j;}

inline void add(int u,int v,ll w){e[++cnt]=(edge){head[u], v, w};head[u]=cnt;}
inline void ins(int u,int v,ll w){add(u,v,w);add(v,u,0);}

inline bool bfs() {
    memset(dep, -1, sizeof(dep));
    queue<int> q;
    q.push(s);dep[s] = 0;
    while(!q.empty()) {
        int now = q.front();q.pop();
        for(int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(e[i].flow && dep[to] == -1) {
                dep[to] = dep[now] + 1;
                q.push(to);
            }
        }
    }
    return dep[t]!=-1;
}

inline ll dfs(int now, ll limit) {
    if(now == t) return limit;
    ll w, flow = 0;
    for(int &i = cur[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(dep[to] == dep[now] + 1 && e[i].flow) {
            w = dfs(to, min(limit - flow, e[i].flow));
            e[i].flow -= w;
            e[i^1].flow += w;
            flow += w;
            if(flow == limit) return limit;
        }
    }
    if(!flow) dep[now] = -1;
    return flow;
}

ll maxflow = 0;
inline void dinic() {
    while(bfs()) {
        for(int i = s ; i <= t + 1; ++i)
            cur[i] = head[i];
        maxflow += dfs(s, inf);
    }
}

inline bool check(ll x) {
    memset(head, 0, sizeof(head));
    cnt = 1;
    ll sum = 0;
    maxflow = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(col[i][j]) {
                ins(s, pos(i, j), 1LL*(x - map[i][j]));
                sum += x - map[i][j];
                for(int k = 1; k <= 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if(nx >= 1 && nx <= n && ny >= 1 && ny <= m)
                        ins(pos(i, j), pos(nx, ny), inf);
                }
            }
            else ins(pos(i, j), t, 1LL*(x - map[i][j]));
        }
    }
    dinic();
    if(maxflow == sum) return 1;
    return 0;
}

int main() {
    readint(T);
    while(T--) {
        readint(n), readint(m);
        sb = sw = cb = cw = 0;
        s = 0, t = pos(n, m) + 1;
        maxx = -inf;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                readll(map[i][j]);
                maxx = max(maxx, (ll)map[i][j]);
                col[i][j] = (i + j) & 1;
            }
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(col[i][j]) sb += map[i][j], cb++;
                else sw += map[i][j], cw++;
            }
        }
        //黑色的分数总和为sb, 白色的分数总和为sw
        //黑色的个数为cb, 白色的个数为cw
        //设最后的分数为x
        //则sb - cb * x = sw - cw * x
        //x = (sw - sb) / (cw - cb)
        if(cw != cb) {
            ll x = (sw - sb) / (cw - cb);
            if(x >= maxx) {
                if(check(x)) {
                    printf("%lld\n", x * cb - sb);
                    continue;
                }
            }
            printf("-1\n");
        }
        else {
            if(sw != sb) {
                printf("-1\n");
                continue;
            }
            ll l = maxx, r = inf;
            while(l <= r) {
                ll mid = (l + r) >> 1;
                if(check(mid)) r = mid - 1;
                else l = mid + 1;
            }
            printf("%lld\n", (ll)l * cb - sb);
        }
    }
    return 0;
}
