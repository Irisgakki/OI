#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n;

struct data{
	int next, to, val;
};

data e[maxn << 1];
int head[maxn], cnt = 0;

inline void add(int u, int v, int w) {
	e[++cnt].next = head[u];
	e[cnt].to = v;
	e[cnt].val = w;
	head[u] = cnt;
}

int dis[maxn], vis[maxn];
inline void dfs(int now, int val) {
	vis[now] = 1;
	dis[now] = val;
	for(int i = head[now]; i; i = e[i].next) {
		int to = e[i].to;
		if(vis[to]) continue;
		dfs(to, val ^ e[i].val);
	}
}

int trie[maxn][2], tot = 1;

inline void insert(int x) {
	int p = 1;
	for(int i = 31; i >= 0; --i) {
		int ch = (x >> i) & 1;
		if(!trie[p][ch]) trie[p][ch] = ++tot;
		p = trie[p][ch];
	}
}

inline int search(int x) {
	int p = 1, ans = 0;
	for(int i = 31; i >= 0; --i) {
		int ch1 = (x >> i) & 1;
		int ch2 = ch1 ^ 1;
		if(trie[p][ch2]) p = trie[p][ch2], ans = ans << 1 | 1;
		else p = trie[p][ch1], ans = ans << 1;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for(int i = 1; i <= n - 1; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w); add(v, u, w);
	}
	dfs(1, 0);
	int ans = -inf;
	for(int i = 1; i <= n; ++i) {
		ans = max(ans, search(dis[i]));
		insert(dis[i]);
	}
	cout << ans;
	return 0;
} 
