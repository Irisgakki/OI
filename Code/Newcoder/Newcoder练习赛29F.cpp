#include <bits/stdc++.h>
#define int long long
const int maxn = 3000010;
const int inf = 0x3f3f3f3f;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m, ans = 0;
int a[maxn], T[maxn], G[maxn], P[maxn];

signed main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		G[a[i]]++;
	}
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= m; ++i) {
		if(G[i]){
			for(int j = i; j <= m; j += i) {
				T[j] += G[i];
			}
		}
	}
	for(int i = 1; i <= m; ++i)
		T[i] += T[i - 1], G[i] += G[i - 1];
	for(int i = 1; i <= m; ++i){
		for(int j = i; j <= m; j += i){
			P[i] += (G[std::min(m, i + j - 1)]- G[j - 1]) * (j / i);
		}
	}
	for(int i = 1; i <= m; ++i)
		ans ^= (P[i] + T[i]);
	printf("%d\n", ans); 
	return 0;
}