#include <bits/stdc++.h>
#define Debug printf("Passing [%s] in LINE %d\n", __FUNCTIOIN__,__LINE__)

typedef long long LL;
const int maxn = 500010;
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

int n, m, S, p;
int money[maxn];
struct Edge{
	int next, to;
} e[maxn];
int head[maxn], cnt = 0;

struct Group{
	int next, to;
} G[maxn];
int last[maxn], val[maxn], sz = 0;

int dis[maxn], in[maxn];

inline void AddEdge(int u, int v) {
	e[++cnt] = (Edge){head[u], v};
	head[u] = cnt;
}

inline void AddGroup(int u, int v) {
	G[++sz] = (Group){last[u], v};
	last[u] = sz;
}

int dfn[maxn], low[maxn], s[maxn], belong[maxn], vis[maxn];
int id = 0, cir = 0, top = 0;

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
			belong[now] = cir;
			val[cir] += money[now];
			vis[now] = 0;
		}
	}
}

inline void rebuild() {
	sz = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = head[i]; j; j = e[j].next)
			if(belong[i] != belong[e[j].to])
				AddGroup(belong[i], belong[e[j].to]);
}

inline void spfa(int s) {
	memset(dis, 0, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	std::queue<int> q;
	q.push(belong[s]);
	dis[belong[s]] = val[belong[s]];
	while(!q.empty()) {
		int now = q.front(); q.pop();
		vis[now] = 0;
		for(register int i = last[now]; i; i = G[i].next) {
			int to = G[i].to;
			if(dis[to] < dis[now] + val[to]) {
				dis[to] = dis[now] + val[to];
				if(!vis[to]) {
					vis[to] = 1;
					q.push(to);
				}
			}
		}
	}
}


int main(){
	n = read(), m = read();
	for(int i = 1; i <= m; ++i){
		int u = read(), v = read();
		AddEdge(u, v);
	}
	for(int i = 1; i <= n; ++i) money[i] = read();
	for(int i = 1; i <= n; ++i) if(!dfn[i]) tarjan(i);
	S = read(), p = read();
	rebuild();
	spfa(S);
	int ans = 0;
	for(int i = 1; i <= p; ++i) {
		int x = read();
		if(dis[belong[x]] > ans) ans = dis[belong[x]];
	}
	print(ans);
	return 0;
}