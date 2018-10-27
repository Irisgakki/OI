#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 3020;
const int inf = 0x3f3f3f3f;
const int mod = 9901;
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
int a[1500100];
int bl[150010][510], blo;

int main(){
	//printf("%d\n", sizeof(bl) / 1024 / 1024);
	n = read(), m = read();
	int blo = sqrt(n);
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		for(int j = 1; j <= blo; ++j){
			bl[j][i % j] += a[i];
		}
	}
	while(m--){
		char opt[3];
		scanf("%s", opt);
		int x = read(), y = read();
		if(opt[0] == 'A'){
			if(x < blo){
				printf("%d\n", bl[x][y % x]);
			} else{
				int ans = 0;
				for(int i = y; i <= n; i += x)
					ans += a[i];
				printf("%d\n", ans);
			}
		} else{
			for(int i = 1; i <= blo; ++i)
				bl[i][x % i] += y - a[x];
			a[x] = y;
		}
	}
	return 0;
}
