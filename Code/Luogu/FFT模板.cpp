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

typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int Maxn = 2e6 + 7;
const int INF = 2147483647;
const int mod = 19260817;
const double pi = acos(-1.0);

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = x * 10 + (ch ^ '0');
	return x * g;	
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');	
}

struct Complex{
    double a, b;
    Complex() {}
    Complex(double _a, double _b) : a(_a), b(_b) {}
    Complex(double _a) : a(_a), b(0.0) {}
    inline Complex operator + (const Complex &z) const {
        return Complex(a + z.a, b + z.b);
    }
    inline Complex operator - (const Complex &z) const {
        return Complex(a - z.a, b - z.b);	
    }
    inline Complex operator * (const Complex &z) const {
        return Complex(a * z.a - b * z.b, a * z.b + b * z.a);
    }
    inline Complex operator / (const Complex &z) const {
        double m = z.a * z.a + z.b * z.b;
        return Complex((a * z.a + b * z.b) / m, (b * z.a - a * z.b) / m);	
    }
};

Complex a[Maxn], b[Maxn];
int alen, blen, len, L, n, rev[Maxn], ans[Maxn];
int _a[Maxn], _b[Maxn];

inline void FFT(Complex c[], int n, int f) {
    Complex wn, w, x, y;
    for(int i = 0; i < n; ++i)
        if(i < rev[i]) std::swap(c[i], c[rev[i]]);
    for(int i = 1; i < n; i <<= 1) {
        wn = Complex(cos(pi / i), sin(pi / i) * f);
        for(int p = i << 1, j = 0; j < n; j += p) {
            w = Complex(1, 0);
            for(int k = 0; k < i; ++k, w = w * wn) {
                x = c[j + k]; y = w * c[j + k + i];
                c[j + k] = x + y; c[j + k + i] = x - y;
            }
        }
    }
    if(!~f) for(int i = 0; i < n; ++i) c[i].a /= (double)n;
    return ;
}

int main() {
    alen = read(), blen = read(), len = alen + blen;
    for(n = 1; n <= len; n <<= 1, L++);
    for(int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	for(int i = 0; i <= alen; ++i) a[i].a = read();
    for(int i = 0; i <= blen; ++i) b[i].a = read();
    FFT(a, n, 1); FFT(b, n, 1);
    for(int i = 0; i <= n; ++i) a[i] = a[i] * b[i];
    FFT(a, n, -1);
    for(int i = 0; i <= len; ++i) ans[i] = (int)(a[i].a + 0.5);
	for(int i = 0; i <= len; ++i) printf("%d ", ans[i]);
	return 0;
} 
