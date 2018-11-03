#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

LL n, q;
LL a[maxn];
LL k, sum;

int main(){
	scanf("%lld %lld", &n, &q);
	for(int i = 0; i <= n - 1; ++i) {
		scanf("%lld", &a[i]);
		(sum += a[i] * i) %= (n - 1);
	}
	if(sum) a[sum]--;
	for(int i = 0; i <= n - 1; ++i)
		a[i] += a[i - 1];
	while(q--) {
		scanf("%lld", &k);
		if(k >= a[n - 1]) puts("-1");
		else printf("%lld\n", (std::upper_bound(a, a + n, k) - a));
	}
	return 0;
}