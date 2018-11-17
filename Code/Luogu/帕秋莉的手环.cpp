#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

typedef long long LL;
const int maxn = 1e7 + 10;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline LL read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register LL x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void print(LL x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int T;
LL n;

struct mat{
    LL m[3][3];
} t, unit;

inline mat mul(mat a, mat b) {
    mat c;
    for(int i = 1; i <= 2; ++i)
        for(int j = 1; j <= 2; ++j)
            c.m[i][j] = 0;
    for(int i = 1; i <= 2; ++i)
        for(int j = 1; j <= 2; ++j)
            for(int k = 1; k <= 2; ++k)
                c.m[i][j] = (c.m[i][j] % mod + a.m[i][k] * b.m[k][j] % mod);
    return c;
}

inline mat fpow(mat a, LL n) {
    mat res = unit;
    while(n) {
        if(n & 1) res = mul(res, a);
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

int main() {
    T = read();
    while(T--) {
        n = read();
        unit.m[1][1] = unit.m[2][2] = 1;
        unit.m[1][2] = unit.m[2][1] = 0;
        t.m[1][1] = t.m[1][2] = t.m[2][1] = 1; t.m[2][2] = 0;
        mat res = fpow(t, n - 1);
        print((res.m[1][1] + res.m[1][2] * 2) % mod);
        puts("");
    }
    return 0;
}