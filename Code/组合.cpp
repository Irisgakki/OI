#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 10001000;
const int inf = 1 << 30;

inline LL read() {
    register char ch;
    while(!isdigit(ch = getchar()));
    register LL x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x;
}

LL T;
LL n, m, p;

inline LL qpow(LL a, LL n, LL mod) {
    if(n == 0) return 1;
    LL res = 1;
    while(n) {
        if(n & 1) res = (res * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

inline LL cal(LL n, LL m, LL p) {
    m = std::max(m, n - m);
    LL fac = 1, inv = 1;
    for(register int i = m + 1; i <= n; ++i) fac = fac * i % p;
    for(register int i = 1; i <= n - m; ++i) inv = inv * i % p;
    return fac * qpow(inv, p - 2, p) % p;
}

int main() {
    T = read();
    while(T--) {
        n = read(), m = read(), p = read();
        printf("%lld\n", cal(n, m, p));
    }

    return 0;
}