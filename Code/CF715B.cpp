#include <bits/stdc++.h>
typedef int mainint;
#define int long long
const int maxn = 20010;
const int inf = 1e18;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}

int n, m, L, S, T;
struct Edge{
	int from, to, dis, id;
} e[maxn << 1];
int cnt = 0;

std::vector<Edge> G[maxn];

struct heap{
	int now, val;
	bool operator < (const heap &x) const {
		return x.val > val;
	}
};

//inline int dij(int idx, int v) {
//	static int dis[maxn], vis[maxn];
//	int cost;
//	for(register int i = 0; i <= n; ++i) dis[i] = inf, vis[i] = 0;
//	std::priority_queue<heap> q;
//	q.push((heap){S,0});
//	dis[S] = 0;
//	while(!q.empty()) {
//		heap U = q.top(); q.pop();
//		int now = U.now;
//		if(vis[now]) continue;
//		vis[now] = 1;
//		int sz = G[now].size();
//		for(register int i = 0; i < sz; ++i) {
//			const Edge &e = G[now][i];
//			if(e.dis == 0) {
//				if(e.id == idx) cost = v;
//				else if(e.id < idx) cost = 1;
//				else cost = inf;
//			} else cost = e.dis;
//			if(dis[e.to] > dis[now] + cost) {
//				dis[e.to] = dis[now] + cost;
//				q.push((heap){e.to, dis[e.to]});
//			}
//		}
//	}
//	return dis[T];
//}

inline int spfa(int idx, int v) {
	int dis[maxn], vis[maxn];
	int cost;
	for(register int i = 0; i <= n; ++i) dis[i] = inf, vis[i] = 0;
	dis[S] = 0, vis[S] = 1;
	std::queue<int> q;
	q.push(S);
	while(!q.empty()) {
		int now = q.front(); q.pop();
		vis[now] = 0;
		for(register int i = 0; i < G[now].size(); ++i) {
			const Edge &e = G[now][i];
			if(e.dis == 0) {
				if(e.id == idx) cost = v;
				else if(e.id < idx) cost = 1;
				else cost = inf;
			} else cost = e.dis;
			if(dis[e.to] > dis[now] + cost) {
				dis[e.to] = dis[now] + cost;
				if(!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
	}
	return dis[T];
}

inline void solve() {
	int l = -1, r = cnt;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(spfa(mid, 1) <= L) r = mid;
		else l = mid;
	}
	int p = r;
	l = 1, r = inf;
	while(l + 1 < r) {
		int mid = (l + r) >> 1;
		if(spfa(p, mid) <= L) l = mid;
		else r = mid;
	}
	printf("YES\n");
	for(register int i = 0; i < m; ++i) {
		if(!e[i].dis)
			printf("%I64d %I64d %I64d\n", e[i].from, e[i].to, e[i].id < p ? 1 : (e[i].id == p ? l : inf));
		else printf("%I64d %I64d %I64d\n", e[i].from, e[i].to, e[i].dis);
	}
}

mainint main() {
	n = read(), m = read(), L = read(), S = read(), T = read();
	for(register int i = 0; i < m; ++i) {
		int u = read(), v = read(), w = read();
		e[i].from = u, e[i].to = v, e[i].dis = w;
		if(w == 0) e[i].id = cnt++;
		G[u].push_back(e[i]), G[v].push_back(e[i]);
		std::swap(G[v].back().from, G[v].back().to);
	}
	if(spfa(-1, 0) < L || spfa(cnt, 0) > L) printf("NO\n");
	else solve();
	return 0;
}