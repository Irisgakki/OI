#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1e6 + 7;
std::bitset<maxn> ans, tmp;

int n, l, r;

int main(){
	scanf("%d", &n);
	ans[0] = 1;
	for(int i = 1; i <= n; ++i) {
		tmp.reset();
		scanf("%d %d", &l, &r);
		for(int j = l; j <= r; ++j) {
			tmp |= ans << (j * j);
		}
		ans = tmp;
	}
	printf("%d\n", ans.count());
	return 0;
}