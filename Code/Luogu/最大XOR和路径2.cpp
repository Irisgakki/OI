#include <bits/stdc++.h>
#define int long long

const int arr = 3e5 + 7;
const int inf = 0x3f3f3f3f;
const int base = 60;

int n, m;
struct Data {
    int from, next, to;
    int val;
}; 

Data e[arr << 1];
int head[arr], cnt = 0;

int vis[arr];
int xor_value[arr];

int top = 0;
int a[arr], b[base + 1];

inline void add(int u, int v, int w) {
    e[++cnt].next = head[u];
    e[cnt].from = u;
    e[cnt].to = v;
    e[cnt].val = w;
    head[u] = cnt;
}

inline void dfs(int now, int par) {
    vis[now] = 1;
    for(int i = head[now]; i; i = e[i].next) {
        int to = e[i].to;
        //int from = e[i].from;
        if(to != par) {
            if(!vis[to]) {
                xor_value[to] = xor_value[now] ^ e[i].val;
                dfs(to, now);
            } else a[++top] = xor_value[now] ^ xor_value[to] ^ e[i].val; 
        }
    }
}

//int dfn[arr], low[arr], s[arr], vis[arr];
//int scc[arr];
//int id = 0, top = 0;

//inline void tarjan(int x) {
//	int now = 0;
//	dfn[x] = low[x] = ++id;
//	vis[x] = 1;
//	s[++top] = x;
//	for(int i = head[x]; i; i = e[i].next) {
//		int to = e[i].to;
//		if(!dfn[to]) {
//			tarjan(to);
//			low[x] = std::min(low[x], low[to]);
//		} else if(vis[to]) low[x] = std::min(low[x], dfn[to]);
//	}
//	if(dfn[x] == low[x]) {
//		cir++;
//		while(now != x) {
//			now = s[top--];
//			scc[now] = cir;
//			xor_value[cir] = 
//		}
//	}
//}

inline void CalBasis() {
    for(int i = 1; i <= top; ++i) {
        for(int j = base; j >= 0; --j) {
            if(a[i] >> j & 1) {
                if(b[j]) a[i] ^= b[j];
                else {
                    b[j] = a[i];
                    for(int k = j - 1; k >= 0; --k) if(b[k] && (b[j] >> k & 1)) b[j] ^= b[k];
                    for(int k = j + 1; k <= base; ++k) if(b[k] >> j & 1) b[k] ^= b[j];
                    break; 
                }
            }
        }
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    dfs(1, 0);
    CalBasis();
    int ans = xor_value[n];
    for(int i = base; i >= 0; --i)
        ans = std::max(ans, ans ^ b[i]);
    std::cout << ans;
    return 0;
}