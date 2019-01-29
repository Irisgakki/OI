#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int inf = 0x3f3f3f3f;

int n;
char g[maxn][maxn];
int ans = 0;

int main() {
//	freopen("bigsq.in","r",stdin);
//	freopen("bigsq.out","w",stdout);	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", g[i] + 1);	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			for(int k = i + 1; k <= n; ++k) {
				for(int l = 1; l <= j; ++l) {
					int x = k - i, y = j - l;
					int p1x = i, p1y = j, p2x = k, p2y = l;
					int p3x = p1x + y, p3y = p1y + x;
					int p4x = p2x + y, p4y = p2y + x;
					if(g[p1x][p1y] == 'B' || g[p2x][p2y] == 'B' || g[p3x][p3y] == 'B' || g[p4x][p4y] == 'B') continue;
					if(p3x < 1 || p3x > n || p3y < 1 || p3y > n || p4x < 1 || p4x > n || p4y < 1 || p4y > n) continue;
					if((g[p1x][p1y] == 'J') + (g[p2x][p2y] == 'J') + (g[p3x][p3y] == 'J') + (g[p4x][p4y] == 'J') >= 3) ans = max(ans, x * x + y * y); 
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
} 
