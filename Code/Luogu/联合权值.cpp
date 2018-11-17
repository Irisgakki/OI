#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;
const int mod = 10007;

inline int read() {
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n;
struct Edge{
	int next, to;
} e[maxn << 1];
int head[maxn], cnt = 0;
int val[maxn];

LL maxx = 0, sum = 0;

inline void add(int u, int v) { e[++cnt] = (Edge) {head[u], v}; head[u] = cnt; };
inline void ins(int u, int v) { add(u, v); add(v, u); }

inline void dfs(int now, int fa) {
	LL maxx1 = 0, maxx2 = 0;
	LL sum1 = 0, sum2 = 0;
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(to != fa) dfs(to, now);
		if(val[to] > maxx2) {
			if(val[to] > maxx1) {
				maxx2 = maxx1;
				maxx1 = val[to];
			} else {
				maxx2 = val[to];
			}
		}
		sum1 += val[to], sum2 += val[to] * val[to];
	}
	sum = (sum + ((sum1 % mod) * (sum1 % mod) - sum2 % mod)) % mod;
	maxx = std::max(maxx, maxx1 * maxx2);
	}

int main(){
	n = read();
	for(int i = 1; i <= n - 1; ++i) {
		int u = read(), v = read();
		ins(u, v);
	}
	for(int i = 1; i <= n; ++i) val[i] = read();
	dfs(1, 0);
	printf("%lld %lld", maxx, sum % mod);
	return 0;
}
