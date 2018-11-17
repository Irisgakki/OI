#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10000100;
const int inf = 0x3f3f3f3f;
const int mod = 1e9;
const int dx[] = {0,1,0,-1};
const int dy[] = {1,0,-1,0};

inline LL read(){
	register LL x = 0, g = 1;
	register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

LL a, b;
LL que[maxn];
int tail, head, num = 0;

inline void dfs(LL x, LL y, LL l) {
	if(y > b) return ;
	if(x == 0){
		LL last = y / (l / 10);
		if(last == 0) return ;
		dfs(x, y + l * last, l * 10);
		if(a <= y && y <= b) ++num;
		if(l < b) que[tail++] = y;
		return ;
	}
	LL last = y / (l / 10), nxt = x % 10;
	x /= 10;
	if(last - nxt >= 0) dfs(x, y + l * (last - nxt), l * 10);
	if(nxt && last + nxt <= 9) dfs(x, y + l * (last + nxt), l * 10);
}

int main(){
	a = read(), b = read();
	tail = 0, head = 0, num = 0;
	que[tail++] = 7;
	if(a <= 7 && b >= 7) ++num;
	while(head < tail){
		for(int i = 0; i <= 9; ++i)
			dfs(que[head], i, 10);
		head++;
	}
	printf("%d\n", num);
	return 0;
}
