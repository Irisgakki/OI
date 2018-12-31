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
const int maxn = 1e6 + 7;
const int inf = 0x3f3f3f3f;

int n, m;
char sr[maxn];

int trie[maxn][26], tot = 1;
int cnt[maxn];

inline void insert(char *a) {
	int p = 1;
	int len = strlen(a);
	for(int i = 0; i < len; ++i) {
		int ch = a[i] - 'a';
		if(!trie[p][ch]) trie[p][ch] = ++tot;
		p = trie[p][ch];
	}
	cnt[p]++;
}

inline int search(char *a) {
	int p = 1, ans = 0;
	int len = strlen(a);
	for(int i = 0; i < len; ++i) {
		p = trie[p][a[i] - 'a'];
		ans += cnt[p];
	}
	return ans;
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
