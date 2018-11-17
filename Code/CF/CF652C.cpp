#include <bits/stdc++.h>
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define INLINE __attribute__((optimize("O3"))) inline
#define lson o << 1
#define rson o << 1 | 1
#define int long long

const int maxn = 1e6 + 7;
const int arr = 1010;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;

INLINE char gc(){
    static char buf[100000], *p1 = buf, *p2 = buf;
    if(p1 == p2){
        p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
        if(p1 == p2) return EOF;
    }
    return *p1++;
}

INLINE int getint() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

INLINE void write(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int n, m, a[maxn];
int sum, pos[maxn], dp[maxn];

main() {
	n = getint(), m = getint();
	rep(i, 1, n) a[i] = getint(), pos[a[i]] = i, dp[i] = n + 1;
	rep(i, 1, m) {
		int l = getint(), r = getint();
		if(pos[l] > pos[r]) std::swap(l, r);
		dp[pos[l]] = std::min(dp[pos[l]], pos[r]);	
	}
	dep(i, n - 1, 1) dp[i] = std::min(dp[i], dp[i + 1]);
	rep(i, 1, n) sum += dp[i] - i;
    write(sum);
	return 0;	
}
