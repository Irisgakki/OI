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
const int maxn = 4e6 + 10;
const int inf = 2147483647;

int n;

int trie[maxn][2], tot = 1;

inline void insert(int x) {
	int p = 0;
	for(int i = 31; i >= 0; --i) {
		int ch = (x >> i) & 1;
		if(!trie[p][ch]) trie[p][ch] = ++tot;
		p = trie[p][ch];
	}
}

inline int search(int x) {
	int p = 0, ans = 0;
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
	int ans = -inf;
	for(int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		ans = max(ans, search(x));
		insert(x);	
	}
	cout << ans;
	return 0;	
}
