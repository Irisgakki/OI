#include <bits/stdc++.h>
#define rg register
typedef long long LL;
const int maxn = 300010;
const int inf = 1 << 30;
const int mod = 998244353;

inline int read() {
	register char ch;
	while(!isdigit(ch = getchar()));
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x;
}


int n;
LL ans = 0;
std::string a;
std::string tmp;

inline LL get(std::string &str) {
	int cnt = 0, cur = 0;
	for(int i = 0; i < n; ++i) {
		if(a[i] == str[cnt]) {
			cnt++;
			if(cnt == str.size()) {
				cnt = 0;
				cur++;
			}
		}
	}
	return 1ll * str.size() * cur * cur;
}

inline void dfs(int x) {
	if(x > 6) return ;
	if(x) ans = std::max(ans, get(tmp));
	for(int j = 0; j < 3; ++j) {
		tmp.push_back('a' + j);
		dfs(x + 1);
		tmp = tmp.substr(0, tmp.size() - 1);
	}
}

int main() {
	int t = read();
	while(t--) {
		n = read();
		ans = 0;
		tmp = "";
		std::cin>>a;
		dfs(0);
		printf("%lld\n", ans);
	}
	return 0;
}