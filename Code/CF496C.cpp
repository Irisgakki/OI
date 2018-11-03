#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 200;
const int inf = 0x3f3f3f3f;
#define Debug printf("Passing [%s] in LINE %d\n", __FUNCTIOIN__,__LINE__)

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

int n, m;
int vis[maxn], b[maxn];
char s[maxn][maxn];

int main(){
	n = read(), m = read();
	for(int i = 0; i < n; ++i) scanf("%s", s[i]);
	for(int j = 0; j < m; ++j) {
		bool ok = 0;
		for(int i = 0; i < n - 1; ++i) {
			if(b[i] == 1) continue;
			if(s[i + 1][j] < s[i][j]) {
				ok = 1;
				break;
			}
		}
		if(ok == 1) vis[j] = 1;
		else {
			for(int i = 0; i < n - 1; ++i) {
				if(s[i + 1][j] > s[i][j])
					b[i] = 1;
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < m; ++i)
		if(vis[i] == 1) ans++;
	printf("%d\n", ans);
	return 0;
}