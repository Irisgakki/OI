#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 400010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

inline int read(){
	register int x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int T;
int n, m, q, k, s;

struct edge{
	int next, to, val, h;
} e[maxn], p[maxn];

struct Edge{
	int next, to, val;
} E[maxn << 1];
int head[maxn], cnt = 0;

inline void AddEdge(int u, int v, int w){
	E[++cnt].next = head[u];
	E[cnt].to = v;
	E[cnt].val = w;
	head[u] = cnt;
}

inline void ins(int u, int v, int w){
	AddEdge(u, v, w);
	AddEdge(v, u, w);
}

struct heap{
	int node, val;
	bool operator < (const heap &x) const{
		return val > x.val;
	}
};

int dis[maxn], vis[maxn];
inline void dijkstra(){
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	std::priority_queue<heap> q;
	q.push((heap){1, 0});
	dis[1] = 0;
	while(!q.empty()){
		heap u = q.top(); q.pop();
		if(vis[u.node]) continue;
		vis[u.node] = 1;
		int now = u.node;
		for(int i = head[now]; i; i = E[i].next){
			int to = E[i].to;
			if(dis[to] > dis[now] + E[i].val){
				dis[to] = dis[now] + E[i].val;
				q.push((heap){to, dis[to]});
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		p[i].val = dis[i];
}

struct Tree{
	int next, to;
} tr[maxn << 1];
int last[maxn], size = 0;

inline void AddNode(int u, int v){
	tr[++size].next = last[u];
	tr[size].to = v;
	last[u] = size;
}

int f[maxn];
inline int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x, int y){
	f[find(y)] = find(x);
}

inline bool cmp(edge a, edge b){
	return a.h > b.h;
}

int dep[maxn], anc[maxn][30];
inline void dfs(int now, int fa){
	dep[now] = dep[fa] + 1;
	anc[now][0] = fa;
	for(int i = 1; i <= 20; ++i)
		anc[now][i] = anc[anc[now][i - 1]][i - 1];
	for(int i = last[now]; i; i = tr[i].next){
		int to = tr[i].to;
		if(to == fa) continue;
		dfs(to, now);
		p[now].val = std::min(p[now].val, p[to].val);
	}
}

int lastans = 0;

inline int query(int x, int y){
	for(int i = 20; i >= 0; --i){
		if(dep[x] - (1 << i) > 0 && p[anc[x][i]].h > y)
			x = anc[x][i];
	}
	return p[x].val;
}

inline void kruskal(){
	int sz = n;
	int tot = 0;
	std::sort(e + 1, e + m + 1, cmp);
	for(int i = 1; i <= n << 1; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i){
		int u = find(e[i].next), v = find(e[i].to);
		if(u != v){
			AddNode(++sz, u);
			AddNode(sz, v);
			f[u] = sz;
			f[v] = sz;
			p[sz].h = e[i].h;
			++tot;
		}
		if(tot == n - 1) break;
	}
	dfs(sz, 0);
	while(q--){
		int x = (k * lastans + read() - 1) % n + 1;
		int y = (k * lastans + read()) % (s + 1);
		printf("%d\n", lastans = query(x,y));
	}
}

int main(){
	T = read();
	while(T--){
		n = read(), m = read();
		lastans = size = cnt = 0;
		memset(head, 0, sizeof(head));
		memset(last, 0, sizeof(last));
		memset(anc, 0, sizeof(anc));
		memset(e, 0, sizeof(e));
		for(int i = 1; i <= m; ++i){
		    e[i].next = read(), e[i].to = read(), e[i].val = read(), e[i].h = read();
			ins(e[i].next, e[i].to, e[i].val);
		}
		for(int i = n + 1; i <= n << 1; ++i) p[i].val = inf;
		dijkstra();
		q = read(), k = read(), s = read();
	    kruskal();
	}
	return 0;
}
