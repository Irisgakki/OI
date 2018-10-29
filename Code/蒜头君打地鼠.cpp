#include <bits/stdc++.h>
const int maxn = 4010;
const int inf = 0x3f3f3f3f;
const int mod = 998244353;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, k, x;
int mp[maxn][maxn], vis[maxn][maxn], sum[maxn][maxn];

inline bool check(int i, int j) {
	return (j <= i + x - 1) && (j >= i - x + 1) && (j >= -i + x - 1) && (j <= -i + (3 * x - 3));
}

int main(){
	memset(sum, 0, sizeof(sum));
    memset(vis, 0, sizeof(vis));
	n = read(), k = read(); x = n;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			mp[i + j][n - 1 + j - i] = read();
			vis[i + j][n - 1 + j - i] = 1;
		}
	}
	n = (n << 1) - 1;
	k = (k << 1) - 1;
	// for(int i = 0; i < n; ++i)
	// 	for(int j = 0; j < n; ++j)
	// 		printf("%lld%c", mp[i][j], j < n - 1 ? ' ' : '\n');
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(i > 0) sum[i][j] += sum[i - 1][j];
			if(j > 0) sum[i][j] += sum[i][j - 1];
			if(i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
			sum[i][j] += mp[i][j];
		}
	}
	int maxx = -inf;
	for(int i = 0; i < n && i + k - 1 < n; ++i) {
		for(int j = 0; j < n && j + k - 1 < n; ++j) {
			if(!check(i, j) && !check(i + k - 1, j) && !check(i, j + k - 1) && !check(i + k - 1, j + k - 1))
				continue;
			if(!vis[i][j]) continue;
			int now = sum[i + k - 1][j + k - 1];
			if(i > 0) now -= sum[i - 1][j + k - 1];
			if(j > 0) now -= sum[i + k - 1][j - 1];
			if(i > 0 && j > 0) now += sum[i - 1][j - 1];
			maxx = std::max(maxx, now); 
		}
	}
	printf("%d\n", maxx);
	return 0;
}