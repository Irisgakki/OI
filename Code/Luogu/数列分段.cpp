#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<climits>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<numeric>
#include<iomanip>
#include<bitset>
#include<sstream>
#include<fstream>
#define debug puts("-----")
#define rep(i,l,r) for(register int i=l;i<=r;++i)
#define dep(i,r,l) for(register int i=r;i>=l;--i)
#define INLINE __attribute__((optimize("O3"))) inline

typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int Maxn = 1e6 + 7;
const int INF = 2147483647;
const int mod = 19260817;

INLINE int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
	return x * g;	
}

INLINE void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');	
}

int n, m, a[Maxn];

INLINE bool check(int mid) {
	int tmp = 0, now = 1;
	rep(i,1,n) {
		if(tmp + a[i] > mid) {
			tmp = 0;
			now++;
		}
		tmp += a[i];
	}
	return now <= m;
}

int main() {
	//freopen("testdata.in","r",stdin);
	n = read(), m = read();
	int l = 0, r = 0, ans = 0;
	rep(i,1,n) a[i] = read(), l = chkmax(l, a[i]), r += a[i];
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	print(ans);
	return 0;
} 
