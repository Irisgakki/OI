#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, m;
struct Edge{
	int next, to, val;
} e[maxn << 1];
int head[maxn], cnt = 0;
int dis[maxn], vis[maxn];

inline void add(int u, int v, int w) {e[++cnt] = (Edge) {head[u], v, w}; head[u] = cnt;}

inline void spfa(){
	memset(dis, 0, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	std::queue<int> q;
	dis[1] = 0;
	vis[1] = 1;
	q.push(1);
	while(!q.empty()) {
		int now = q.front(); q.pop();
		vis[now] = 0;
		for(register int i = head[now]; i; i = e[i].next) {
			int to = e[i].to;
			if(dis[to] < dis[now] + e[i].val) {
				dis[to] = dis[now] + e[i].val;
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
	rep(i,1,m) {
		int u = read(), v = read(), w = read();
		add(u, v, w);
	}
	spfa();
	if(dis[n] == 0) printf("-1\n");
	else printf("%d\n", dis[n]);
	return 0;
}