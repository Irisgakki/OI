#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 1e6 + 7;
const int arr = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

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

int T;
int n, h, r;
int vis[maxn];
bool flag = 0;
struct Point{
    double x, y, z;
} p[maxn];

inline double cal_dist(Point a, Point b) {
    double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
    return dist;
}

inline void dfs(int now, int height) {
    if(height + r >= h) {
    	flag = 1;
		return ;	
    }
    vis[now] = 1;
    for(int i = 1; i <= n; ++i) {
    	if(flag) return ;
        if(!vis[i] && cal_dist(p[now], p[i]) <= 2.0 * r)
			dfs(i, p[i].z); 
    }
}

int main() {
    T = getint();
    while(T--) {
        flag = 0;
        n = getint(), h = getint(), r = getint();
        for(int i = 1; i <= n; ++i) {
           	scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
        }
        for(int i = 1; i <= n; ++i) {
            if(p[i].z - r <= 0) {
                memset(vis, 0, sizeof(vis));
                dfs(i, p[i].z);
            }
        }
        if(flag) puts("Yes");
        else puts("No");
    }
    return 0;
}
