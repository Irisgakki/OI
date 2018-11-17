#include <bits/stdc++.h>
#define rr register
typedef long long ll;
const int maxn = 2e5+7;
const int inf = 0x7f7f7f7f;
const int mod = 1e9+7;

inline int read() {
    rr char ch;
    while(!isdigit(ch=getchar()));
    rr int x = ch ^ '0';
    while(isdigit(ch=getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x;
}

int n, m, k;
ll ans = 1;
struct point{
    int x, y;
    friend bool operator < (const point &a, const point &b) {
        return a.x + a.y < b.x + b.y;
    }
}p[maxn];

ll fac[maxn], inv[maxn];

inline ll qpow(ll a, ll n) {
    ll res = 1;
    while(n) {
        if(n & 1) res = (a * res) % mod;
        n >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

inline void init() {
    fac[0] = 1, inv[0] = 1;
    for(rr int i = 1; i <= maxn; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i], mod - 2) % mod;
    }
}

inline ll C(int m, int n) {
    if(n > m) return 0;
    return fac[m] * inv[n] % mod * inv[m - n] % mod;
}

int main() {
	init(); 
    n = read(), m = read(), k = read();
    for(rr int i = 2; i <= k + 1; ++i) {
        p[i].x = read();
        p[i].y = read();
    }
    p[1] = (point){1, 1};
    p[k + 2] = (point){n, m};
    std::sort(p + 1, p + k + 2);
    for(rr int i = 2; i <= k + 2; ++i) {
        int x = p[i].x - p[i - 1].x + 1;
        int y = p[i].y - p[i - 1].y + 1;
        if(x < 0 || y < 0) {
            printf("0\n");
            return 0;
        }
        ans = (ans * C(x + y - 2, x - 1)) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}
