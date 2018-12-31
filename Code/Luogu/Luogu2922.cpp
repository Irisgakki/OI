#include <bits/stdc++.h>
#define maxn 1000010
#define inf 0x3f3f3f3f
#define eps 1e-6
#define ll long long

using namespace std;

int n, m, num;

int tmp[maxn];
int trie[maxn][2], end[maxn], cnt[maxn], tot = 1;

inline void insert(int *a) {
	int p = 1;
	for(int i = 1; i <= num; ++i) {
		if(!trie[p][a[i]]) trie[p][a[i]] = ++tot;
		p = trie[p][a[i]];
		cnt[p]++;
	}
	end[p]++;
}

inline int search(int *a) {
	int p = 1, ans = 0;
	for(int i = 1; i <= num; ++i) {
		if(!trie[p][a[i]]) return ans;
		p = trie[p][a[i]];
		ans += end[p];
	}
	return ans - end[p] + cnt[p];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		cin >> num;
		for(int j = 1; j <= num; ++j) {
			int x;
			cin >> x;
			tmp[j] = x;
		}
		insert(tmp);
	}
	for(int i = 1; i <= m; ++i) {
		cin >> num;
		for(int j = 1; j <= num; ++j) {
			int x;
			cin >> x;
			tmp[j] = x;
		}
		cout << search(tmp) << '\n';
	}
	return 0;
}
