#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, m;
int a[maxn][maxn];
int vis[1 << 10];

struct node{
	int sta, ans;
};

inline int bfs(){
	std::queue<node> q;
	q.push((node){(1 << n) - 1, 0});
	vis[(1 << n) - 1] = 1;
	while(!q.empty()) {
		node now = q.front(); q.pop();
		if(now.sta == 0) return now.ans;
		else {
			rep(i, 1, m) {
				int now_sta = now.sta;
				rep(j, 1, n) {
					if(a[i][j] == 1 && (now_sta & (1 << (j - 1)))) now_sta ^= 1 << (j - 1);
					if(a[i][j] == -1 && !(now_sta & (1 << (j - 1)))) now_sta |= 1 << (j - 1);
				}
				if(!vis[now_sta]){
					vis[now_sta] = 1;
					q.push((node){now_sta, now.ans + 1});
				}
			}
		}
	}
	return -1;
}

int main(){
	n = read(), m = read();
	rep(i, 1, m)
		rep(j, 1, n)
			a[i][j] = read();
	printf("%d\n", bfs());
	return 0;
}