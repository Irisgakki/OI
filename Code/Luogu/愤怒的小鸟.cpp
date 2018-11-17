#include <bits/stdc++.h>
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

inline double get(double &a, double &b, double x1, double y1, double x2, double y2) {
	a = (x2 * y1 - x1 * y2) / (x1 * x2 * (x1 - x2));
	b = (x1 * x1 * y2 - x2 * x2 * y1) / (x1 * x2 * (x1 - x2));
}

inline int check(double a, double b, double x, double y) {
	double abs = a * x * x + b * x - y;
	if(abs < 0) abs = -abs;
	return abs <= 1e-6;
}

int T, n, m;
double x[maxn], y[maxn];
int pig[maxn], count_ = 0, dp[1 << 18];

inline void init() {
	count_ = 0;
	for(int i = 0; i < n; ++i) {
		pig[count_++] = (1 << i);
		for(int j = i + 1, vis = 0; j < n; ++j) {
			if((vis >> j) & 1) continue;
			else {
				double a, b;
				get(a, b, x[i], y[i], x[j], y[j]);
				if(a >= 0) continue;
				pig[count_] = (1 << i);
				for(int k = j; k < n; ++k) {
					if(check(a, b, x[k], y[k])) {
						vis |= (1 << k);
						pig[count_] |= (1 << k);
					}
				}
				count_++;
			}
		}
	}
}

inline void DP() {
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	for(int i = 0; i < (1 << n); ++i) {
		for(int j = 0; j < count_; ++j) {
			dp[i | pig[j]] = std::min(dp[i | pig[j]], dp[i] + 1);
		}
	}
	printf("%d\n", dp[(1 << n) - 1]);
}

int main() {
	T = read();
	while(T--) {
		n = read(), m = read();
		for(int i = 0; i < n; ++i)
			scanf("%lf %lf", &x[i], &y[i]);
		init();
		DP();
	}
	return 0;
}