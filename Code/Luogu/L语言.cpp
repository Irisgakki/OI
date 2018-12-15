#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n, m;
int trie[maxn][26], end[maxn], tot = 1;
char sr[maxn];
int dp[maxn];

inline void insert(char *a) {
	int p = 1;
	int len = strlen(a);
	for(int i = 0; i < len; ++i) {
		int ch = a[i] - 'a';
		if(!trie[p][ch]) trie[p][ch] = ++tot;
		p = trie[p][ch];
	}
	end[p] = 1;
}

inline int search(char *a) {
	int p = 1, ans = 0;
	int len = strlen(a);
	memset(dp, 0, sizeof(dp));
	dp[-1] = 1;
	for(int i = -1; i < len; ++i) {
		if(!dp[i]) continue;
		else ans = i;
		for(int j = i + 1, p = 1; j < len; ++j) {
			p = trie[p][a[j] - 'a'];
			if(p == 0) break;
			if(end[p]) dp[j] = 1;
		}
	}
	return ans + 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		cin >> sr;
		insert(sr);
	}
	for(int i = 1; i <= m; ++i) {
		cin >> sr;
		cout << search(sr) << '\n';
	}
	return 0;
}
