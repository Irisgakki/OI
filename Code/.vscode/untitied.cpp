#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define lson o << 1
#define rson o << 1 | 1

typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e6 + 7;
const ll arr = 1010;
const ll INF = 1e18;
const ll mod = 11111597780929;

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

int n;
long double x[maxn], y[maxn], z[maxn], w[maxn];
long double ansx, ansy, ansz, ans;

inline long double dist(long double x, long double xx, long double y, long double yy, long double z, long double zz) {
    return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy)+(z-zz)*(z-zz));
}

inline long double cal(long double nowx, long double nowy, long double nowz) {
    long double res = 0;
    rep(i,1,n) {
        res += dist(nowx, x[i], nowy, y[i], nowz, z[i]) * w[i];
    }
    if(res < ans) ansx = nowx, ansy = nowy, ansz = nowz, ans = res;
    return res;
}

inline void sa() {
    long double T = 10000;
    long double nx = ansx, ny = ansy, nz = ansz;
    while(T > 1e-14) {
        long double nxx = nx + (2 * rand() - RAND_MAX) * T;
        long double nyy = ny + (2 * rand() - RAND_MAX) * T;
        long double nzz = nz + (2 * rand() - RAND_MAX) * T;
        long double nans = cal(nxx, nyy, nzz);
        long double delta = nans - ans; 
        if(delta < 0 || exp(-delta / T) > (long double)rand() / RAND_MAX) nx = nxx, ny = nyy, nz = nzz;
        T *= 0.995;
    }
}

int main() {
    srand(19260817);
    n = getint();
    rep(i,1,n) {
        scanf("%Lf %Lf %Lf %Lf", &x[i], &y[i], &z[i], &w[i]);
        ansx += x[i], ansy += y[i], ansz += z[i];
    }
    ansx /= (long double)n, ansy /= (long double)n, ansz /= (long double)n;
    ans = cal(ansx, ansy, ansz);
    sa();
    printf("%.2Lf\n%.2Lf\n%.2Lf\n%.2Lf", ansx, ansy, ansz, ans);
    return 0;
}