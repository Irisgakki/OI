#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long LL;
const int maxn = 10010;
const int inf = 0x3f3f3f3f;

inline LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

int T, cas = 0;
LL n, m, x;
LL fac[maxn], top = 0;
int num[maxn], vis[maxn];

int main() {
	scanf("%d", &T);
	while(T--) {
		top = 0;
		memset(vis, 0, sizeof(vis));
		memset(num, 0, sizeof(num));
		memset(fac, 0, sizeof(fac));
		scanf("%lld %lld", &n, &m);
		for(int i = 1; i * i <= m; ++i) {
			if(m % i == 0) {
				fac[top++] = i;
				if(i * i != m) fac[top++] = m / i;
			}
		}
		std::sort(fac, fac + top);
		for(int i = 0; i < n; ++i) {
			scanf("%lld", &x);
			LL tmp = gcd(x, m);
			for(int j = 0; j < top; ++j) {
				if(fac[j] % tmp == 0) {
					vis[j] = 1;
				}
			}
		}
		vis[top - 1] = 0;
		LL ans = 0;
		for(int i = 0; i < top; ++i) {
			if(vis[i] != num[i]) {
				LL tmp = (m - 1) / fac[i];
				ans += tmp * (tmp + 1) / 2 * fac[i] * (vis[i] - num[i]);
				tmp = vis[i] - num[i];
				for(int j = i; j < top; ++j) {
					if(fac[j] % fac[i] == 0) {
						num[j] += tmp;
					}
				}
			}
		}
		printf("Case #%d: %lld\n", ++cas, ans);
	}
	return 0;
}