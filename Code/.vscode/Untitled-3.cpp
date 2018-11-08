#include <bits/stdc++.h>
#define INLINE __attribute__((optimize("O3"))) inline
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define lson o << 1
#define rson o << 1 | 1
#define int long long

typedef unsigned long long ull;
const int maxn = 2e5 + 7;
const int arr = 1010;
const int INF = 1e18;
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

int n, k, sum, mul, lef[maxn], a[maxn], ans = 0, now;

INLINE void solve() {
    int ss;
    rep(i, 1, n) {
        sum = mul = a[i], ans += (k == 1);
        for(int pre = i, now = lef[i]; ; pre = now, now = lef[now]) {
           ss = mul - 1ll * sum * k;
           if(ss > 0 && ss % k == 0 && ss / k < pre - now) ans++;
           if(!now || INF / a[now] < mul) break;
           mul *= a[now], sum += a[now] + pre - now - 1;
           ans += (mul == sum * k);
        }
    }
}

signed main() {
    n = getint(), k = getint();
    rep(i, 1, n) a[i] = getint();
    rep(i, 1, n) lef[i] = (a[i - 1] != 1 ? i - 1 : lef[i - 1]);
    solve();
    write(ans);
    return 0;
}