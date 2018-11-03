#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 50010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, m;
struct Edge{
	int next, to, val;
} e[maxn];
int head[maxn], cnt = 0;

inline void add(int u, int v) {
	e[++cnt] = (Edge) {head[u], v};
	head[u] = cnt;
}

int dfn[maxn], low[maxn], s[maxn], top = 0, idx = 0;
int vis[maxn], Bcnt = 0;
int belong[maxn], col[maxn], du[maxn];

inline void tarjan(int x) {
	int to;
	dfn[x] = low[x] = ++idx;
	vis[x] = 1;
	s[++top] = x;
	for(register int i = head[x]; i; i = e[i].next) {
		to = e[i].to;
		if(!dfn[to]) {
			tarjan(to);
			low[x] = std::min(low[x], low[to]);
		} else if(vis[to]) low[x] = std::min(low[x], dfn[to]);
	}
	if(dfn[x] == low[x]) {
		Bcnt++;
		do {
			to = s[top--];
			vis[to] = 0;
			belong[to] = Bcnt;
			col[Bcnt]++;
		} while(to != x);
	}
}

int main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read(), v = read();
		add(u, v);
	}
	for(int i = 1; i <= n; ++i)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; ++i) {
		for(int j = head[i]; j; j = e[j].next) {
			int to = e[j].to;
			if(belong[i] != belong[to]) {
				du[belong[i]]++;
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= Bcnt; ++i) {
		if(!du[i]) {
			if(ans) return printf("0"), 0;
			ans = i;
		}
	}
	printf("%d", col[ans]);
	return 0;
}