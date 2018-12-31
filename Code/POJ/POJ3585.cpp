//Akasaka Ryunosuke
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define ll long long
#define ull unsigned long long
#define rg register

using namespace std;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int T, n;

struct data{
	int next, to, flow;	
};

data e[maxn << 1];
int head[maxn], cnt = 0;

int C[maxn], F[maxn], vis[maxn], deg[maxn];

inline void add(int u, int v, int w) {
	e[++cnt].next = head[u];
	e[cnt].to = v;
	e[cnt].flow = w;
	head[u] = cnt;	
}

inline void dfs1(int now) {
	vis[now] = 1;
	C[now] = 0;
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(vis[to]) continue;
		dfs1(to);
		if(deg[to] == 1) C[now] += e[i].flow;
		else C[now] += min(C[to], e[i].flow);
	}
}

inline void dfs2(int now) {
	vis[now] = 1;
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(vis[to]) continue;
		if(deg[now] == 1) F[to] = C[to] + e[i].flow;
		else F[to] = C[to] + min(F[now] - min(C[to], e[i].flow), e[i].flow);
		dfs2(to);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--) {
		cnt = 0;
		memset(head, 0, sizeof(head));
		memset(C, 0, sizeof(C));
		memset(F, 0, sizeof(F));
		memset(vis, 0, sizeof(vis));
		memset(deg, 0, sizeof(deg));
		cin >> n;
		for(int i = 1; i <= n - 1; ++i) {
			int u, v, w;
			cin >> u >> v >> w;
			add(u, v, w); add(v, u, w);
			deg[u]++, deg[v]++;
		}
		dfs1(1);
		F[1] = C[1];
		memset(vis, 0, sizeof(vis));
		dfs2(1);
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans = max(ans, F[i]);
		cout << ans << endl;
	}
	return 0;
}

