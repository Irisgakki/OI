#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int getint() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);	
	putchar(x % 10 + '0');
}

double x, y;
int n;

inline double dfs(double x, double y, int depth) {
	if(depth == 1) return std::max(x / y, y / x);
	double ans = 1e20;
	for(int i = 1; i <= depth / 2; ++i) {
		double nx = x * i / depth, ny = y * i / depth;
		ans = std::min(ans, std::max(dfs(nx, y, i), dfs(x - nx, y, depth - i)));
		ans = std::min(ans, std::max(dfs(x, ny, i), dfs(x, y - ny, depth - i))); 
	}
	return ans;
}

int main() {
	scanf("%lf %lf", &x, &y);
	n = getint();
	printf("%.6lf", dfs(x, y, n));
	return 0;	
}
