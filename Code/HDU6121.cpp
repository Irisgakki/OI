#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define lson o << 1
#define rson o << 1 | 1
#define int long long

const int maxn = 1e7 + 7;
const int arr = 1010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline char gc(){
    static char buf[100000], *p1 = buf, *p2 = buf;
    if(p1 == p2){
        p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
        if(p1 == p2) return EOF;
    }
    return *p1++;
}

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

int T, n, k;
int num[500], ans;

inline int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res *= a;
		n >>= 1;
		a *= a;
	}
	return res;
}

inline void init(int k, int depth) {
	for(int i = 1; i <= depth; ++i) {
		num[i] = (fpow(k,i) - 1) / (k - 1);
	}
}

signed main() {
	T = getint();
	while(T--) {
		n = getint(), k = getint();
		if(k == 1) {
			int tmp = n % 4;
			if(tmp == 0) write(n), puts("");
			if(tmp == 1) putchar('1'), puts("");
			if(tmp == 2) write(n + 1), puts("");
			if(tmp == 3) putchar('0'), puts("");
			continue;	
		}
		int depth = 1;
		int tmp = n - 1;
		while(tmp) {
			tmp = (tmp - 1) / k;
			depth++;
		}
		init(k, depth);
		ans = n;
		ans ^= (n - num[depth - 1]) & 1;
		depth--;
		int pos = (n - 1 - 1) / k;
		int now = 2;
		while(depth > 1) {
			int l = num[depth - 1];
			int r = num[depth] - 1;
			int tmp1 = num[now];
			int tmp2 = num[now - 1];
			if((pos - l) & 1) ans ^= tmp1;
			if((r - pos) & 1) ans ^= tmp2;
			int cnt = pos;
			while(cnt <= (n - 1 - 1) / k) cnt = cnt * k + 1;
			ans ^= num[now - 1] + n - cnt;
			now++;
			depth--;
			pos = (pos - 1) / k;
		}
		write(ans); puts("");
	}
	return 0;	
}
