#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10000010;
const int inf = 0x3f3f3f3f;

LL t, k, p;
LL F[maxn], dp[maxn];

std::queue<LL> q;
inline LL find(LL x) { return x == F[x] ? x : F[x] = find(F[x]); }

int main() {
	scanf("%lld %lld %lld", &t, &k, &p);
	for(int i = 1; i <= p + 1; ++i) F[i] = i;
	q.push(1);
	memset(dp, -1, sizeof(dp));
	dp[1] = 1;
	F[1] = 2;
	while(!q.empty()) {
		LL now = q.front(); q.pop();
		for(LL nxt = find(now + 1); nxt <= std::min(now + t, p); nxt = find(nxt)) {
			dp[nxt] = dp[now] + 1;
			q.push(nxt);
			F[nxt] = nxt + 1;
		}
		if(now * k <= p && F[now * k] == now * k) {
			dp[now * k] = dp[now] + 1;
			q.push(now * k);
			F[now * k] = now * k + 1;
		}
	}
	printf("%d", dp[p]);
	return 0;
}