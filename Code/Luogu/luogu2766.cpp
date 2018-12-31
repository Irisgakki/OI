#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e6 + 7;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn], len = 0;

struct data{
    int next, to, flow;
};

data e[maxn << 1];
int head[maxn], cnt = 1;
int dep[maxn], cur[maxn];
int s, t;

inline void add(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].to = v;
    e[cnt].flow = w;
    head[u] = cnt;
}

inline void ins(int u, int v, int w) {
    add(u, v, w); add(v, u, 0);
}

inline bool bfs() {
    memset(dep, -1, sizeof(dep));
    queue<int> q;
    q.push(s); dep[s] = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        for(int i = head[now]; i; i = e[i].next) {
            int to = e[i].to;
            if(dep[to] == -1 && e[i].flow) {
                dep[to] = dep[now] + 1;
                q.push(to);
            }
        }
    }
    return dep[t] != -1;
}

inline int dfs(int now, int limit) {
    if(now == t) return limit;
    int w, flow = 0;
    for(int &i = cur[now]; i; i = e[i].next) {
        int to = e[i].to;
        if(dep[to] == dep[now] + 1 && e[i].flow) {
            w = dfs(to, min(limit - flow, e[i].flow));
            e[i].flow -= w; e[i ^ 1].flow += w; flow += w;
            if(flow == limit) return limit;
        }
    }
    if(!flow) dep[now] = -1;
    return flow;
}

inline int dinic() {
    int maxflow = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        maxflow += dfs(s, inf);
    }
    return maxflow;
}

int dp[maxn];

inline int SolveProblemOne() {
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i) {
        dp[i] = 1;
        for(int j = 1; j < i; ++j) {
            if(a[i] >= a[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        len = max(len, dp[i]);
    }
    return len;
}

inline int SolveProblemTwo() {
	cnt = 1;
	memset(head, 0, sizeof(head));
    s = 0, t = 3 * n;
    for(int i = 1; i <= n; ++i) {
        if(dp[i] == 1) ins(s, i, 1);
        if(dp[i] == len) ins(i + n, t, 1);
        ins(i, i + n, 1);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            if(a[j] >= a[i] && dp[j] == dp[i] + 1)
                ins(i + n, j, 1);
    int ans = dinic();
    return ans;
}

inline int SolveProblemThree() {
    cnt = 1;
    memset(head, 0, sizeof(head));
    s = 0, t = 3 * n;
    for(int i = 1; i <= n; ++i) {
        int flow = 1;
        if(i == 1 || i == n) flow = inf;
        if(dp[i] == 1) ins(s, i, flow);
        if(dp[i] == len) ins(i + n, t, flow);
        ins(i, i + n, flow);
    }
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            if(a[j] >= a[i] && dp[j] == dp[i] + 1)
                ins(i + n, j, 1);
    int ans = dinic();
    if(ans >= inf) return n;
    else return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    cout << SolveProblemOne() << endl;
    cout << SolveProblemTwo() << endl;
    cout << SolveProblemThree() << endl;
    return 0;
}
