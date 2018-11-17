#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 60;
const int inf = 0x3f3f3f3f;
const int mod = 1e9;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

inline int read(){
	register int x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, m;
char mp[maxn][maxn];

static int cnt = 0;
static int num[maxn][maxn];
static int dis[maxn][maxn], road[maxn][maxn];


struct node{
	int x, y;
};

inline void bfs(int x, int y){
	std::queue<node> q;
	q.push((node){x, y});
	memset(dis, 0x3f, sizeof(dis));
	dis[x][y] = 1;
	while(!q.empty()){
		node now = q.front(); q.pop();
		for(int i = 0; i < 4; ++i){
			int nx = now.x + dx[i];
			int ny = now.y + dy[i];
			if(nx < 1 || nx > n || ny < 1 || ny > m || mp[nx][ny] == '.') continue;
			int tmp = dis[now.x][now.y];
			if(tmp > dis[nx][ny]) continue;
			if(mp[nx][ny] == 'X'){
				if(tmp < dis[nx][ny]){
					dis[nx][ny] = tmp;
					road[num[nx][ny]][num[x][y]] = std::min(road[num[nx][ny]][num[x][y]], dis[nx][ny] - 1);
					road[num[x][y]][num[nx][ny]] = road[num[nx][ny]][num[x][y]];
					q.push((node){nx, ny});
				}
			} else {
				tmp++;
				if(tmp < dis[nx][ny]){
					dis[nx][ny] = tmp;
					q.push((node){nx, ny});
				}
			}
		}
	}
}

inline void dfs(int x, int y, int cnt){
	for(int i = 0; i < 4; ++i){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx < 1 || nx > n || ny < 1 || ny > m || mp[nx][ny] != 'X' || num[nx][ny]) continue;
		num[nx][ny] = cnt;
		dfs(nx, ny, cnt);
	}
}

int ans = inf;
int dp[maxn][1 << 16];
inline void DP(){	
	memset(dp, 0x3f, sizeof(dp));
	int S = 1 << cnt;
	for(int i = 1; i <= cnt; ++i)
		dp[i][1 << (i - 1)] = 0;
	for(int i = 1; i < S; ++i){
		for(int j = 1; j <= cnt; ++j){
			if(!(i & (1 << (j - 1)))) continue;
			for(int k = 1; k <= cnt; ++k){
				if(i & (1 << (k - 1))) continue;
				dp[k][i | (1 << (k - 1))] = std::min(dp[k][i | (1 << (k - 1))], dp[j][i] + road[j][k]);
			}
		}
	}
	for(int i = 1; i <= cnt; ++i)
		ans = std::min(ans, dp[i][S - 1]);
}

int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j){
			scanf(" %c", &mp[i][j]);
		}
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			if(mp[i][j] == 'X' && !num[i][j]) {
				num[i][j] = ++cnt;
				dfs(i, j, cnt);
			}
		}
	}
	memset(road, 0x3f, sizeof(road));
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			if(num[i][j]) {
				bfs(i, j);
			}
		}
	}
	DP();
	printf("%d\n", ans);
	return 0;
}
