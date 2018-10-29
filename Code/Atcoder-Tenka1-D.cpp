#include <bits/stdc++.h>
#define int long long
const int maxn = 100010;
const int inf = 1e18;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

static int n, m;
std::vector<int> vec[maxn];

signed main(){
	n = read();
	while(m * (m - 1) / 2 < n) ++m;
	if(m * (m - 1) / 2 > n) return printf("No\n"), 0;
	for(int i = 1, k = 0; i <= m; ++i){
		for(int j = i + 1; j <= m; ++j){
			vec[i].push_back(++k);
			vec[j].push_back(k);
		}
	}
	printf("Yes\n");
	printf("%lld\n", m);
	for(int i = 1; i <= m; ++i){
		printf("%lld ", m - 1);
		for(int j = 0; j < vec[i].size(); ++j)
			printf("%lld ", vec[i][j]);
		printf("\n");
	}
	return 0;
}