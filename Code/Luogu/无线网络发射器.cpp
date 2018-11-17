#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;
const int mod = 10007;

inline int read() {
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int d, n, sum = 0, tot = 0, ans = 0;
struct Point{
	int x, y, k;
} p[maxn];

int main(){
	d = read();
	n = read();
	for(int i = 1; i <= n; ++i) {
		p[i].x = read(), p[i].y = read(), p[i].k = read();
	}
	for(int i = 0; i <= 128; ++i) {
		for(int j = 0; j <= 128; ++j) {
			int left = std::max(0, j - d);
			int right = std::min(j + d, 128);
			int up = std::max(0, i - d);
			int down = std::min(i + d, 128);
			sum = 0;
			for(int l = 1; l <= n; ++l) {
				if(left <= p[l].x && p[l].x <= right && up <= p[l].y && p[l].y <= down)
					sum += p[l].k;
			}
			ans = std::max(ans, sum);
		}
	}
	for(int i = 0; i <= 128; ++i) {
		for(int j = 0; j <= 128; ++j) {
			int left = std::max(0, j - d);
			int right = std::min(j + d, 128);
			int up = std::max(0, i - d);
			int down = std::min(i + d, 128);
			sum = 0;
			for(int l = 1; l <= n; ++l){
				if(left <= p[l].x && p[l].x <= right && up <= p[l].y && p[l].y <= down)
					sum += p[l].k;
			}
			if(sum == ans) tot++;
		}
	}
	printf("%d %d", tot, ans);
	return 0;
}