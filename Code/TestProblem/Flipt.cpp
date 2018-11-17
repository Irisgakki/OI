#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long LL;
const int maxn = 30;
const int inf = 0x3f3f3f3f;
const int mod = 1e9;

inline int read(){
	register int x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m, a[maxn][maxn];

int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

static int ans, p, cnt;
static int tmp[maxn][maxn], G[maxn][maxn];

inline void flipt(int x, int y){
	cnt++;
	G[x][y] = 1;
	tmp[x][y] = !tmp[x][y];
	for(int i = 0; i < 4; ++i){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx > -1 && ny > -1){
			tmp[nx][ny] ^= 1;
		}
	}
}

inline bool check(int x){
	cnt = 0;
	memcpy(tmp, a, sizeof(tmp));
	for(int i = 0; i < m; ++i){
		if(x & (1 << (m - 1 - i)))
			flipt(0, i);
	}
	for(int i = 1; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(tmp[i - 1][j]) flipt(i, j);
		}
	}
	for(int i = 0; i < m; ++i)
		if(tmp[n - 1][i]) return false;
	return true;
}

int main(){
    while(~scanf("%d %d", &n, &m)) {
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			a[i][j] = read();
		}
	}
	ans = n * m + 1, p = -1;
	for(int i = 0; i < 1 << m; ++i)
		if(check(i) && cnt < ans)
			ans = cnt, p = i;
	memset(G, 0, sizeof(G));
	if(p >= 0){
		check(p);
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				printf("%d%c", G[i][j], j < m - 1 ? ' ' : '\n');
			}
		}
	} else printf("IMPOSSIBLE\n");
	}
	return 0;
}
