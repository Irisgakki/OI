#include <bits/stdc++.h>
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define INLINE __attribute__((optimize("O3"))) inline
#define lson o << 1
#define rson o << 1 | 1

typedef long long LL;
typedef unsigned long long ull;
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

int n, m;
double a[maxn];
struct Segment{
    int l, r, sz;
    double sum, sqr, sumtag;
} seg[maxn << 2];

INLINE void push_up(int o) {
    seg[o].sum = seg[lson].sum + seg[rson].sum;
    seg[o].sqr = seg[lson].sqr + seg[rson].sqr;
}

INLINE void push_down(int o) {
    if(seg[o].sumtag) {
        seg[lson].sqr += 2 * seg[o].sumtag * seg[lson].sum + seg[lson].sz * seg[o].sumtag * seg[o].sumtag;
        seg[rson].sqr += 2 * seg[o].sumtag * seg[rson].sum + seg[rson].sz * seg[o].sumtag * seg[o].sumtag;
        seg[lson].sum += seg[lson].sz * seg[o].sumtag;
        seg[rson].sum += seg[rson].sz * seg[o].sumtag;
        seg[lson].sumtag += seg[o].sumtag;
        seg[rson].sumtag += seg[o].sumtag;
        seg[o].sumtag = 0;
    }
}

INLINE void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r, seg[o].sz = r - l + 1;
    if(l == r) {
        seg[o].sum = a[l];
        seg[o].sqr = a[l] * a[l];
        return ;
    }
    int mid = l + r >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
    push_up(o);
}

INLINE void modify(int o, int l, int r, double v) {
    if(l <= seg[o].l && seg[o].r <= r) {
        seg[o].sqr += 2 * v * seg[o].sum + v * v * seg[o].sz;
        seg[o].sum += v * seg[o].sz;
        seg[o].sumtag += v;
        return ;
    }
    push_down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    if(l <= mid) modify(lson, l, r, v);
    if(r > mid) modify(rson, l, r, v);
    push_up(o);
}

INLINE double query_sum(int o, int l, int r) {
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].sum;
    push_down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    double ans = 0;
    if(l <= mid) ans += query_sum(lson, l, r);
    if(r > mid) ans += query_sum(rson, l, r);
    return ans;
}

INLINE double query_sqr(int o, int l, int r) {
    if(l <= seg[o].l && seg[o].r <= r) return seg[o].sqr;
    push_down(o);
    int mid = seg[o].l + seg[o].r >> 1;
    double ans = 0;
    if(l <= mid) ans += query_sqr(lson, l, r);
    if(r > mid) ans += query_sqr(rson, l, r);
    return ans;
}

int main() {
    n = getint(), m = getint();
    rep(i, 1, n) scanf("%lf", &a[i]);
    build(1, 1, n);
    while(m--) {
        int opt = getint(), x, y;
        double k;
        if(opt == 1) {
            x = getint(), y = getint();
            scanf("%lf", &k);
            modify(1, x, y, k);
        }
        if(opt == 2) {
            x = getint(), y = getint();
            printf("%.4lf\n", query_sum(1, x, y) / (y - x + 1));
        }
        if(opt == 3) {
            x = getint(), y = getint();
            double sum1 = query_sqr(1, x, y) / (y - x + 1);
            double sum2 = query_sum(1, x, y) / (y - x + 1);
            // printf("%lf %lf\n", sum1, sum2);
            double ans = sum1 - sum2 * sum2;
            printf("%.4lf\n", ans);
        }
    }
    return 0;
}
