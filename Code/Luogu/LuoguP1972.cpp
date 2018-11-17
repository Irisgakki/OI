#include <bits/stdc++.h>
#define INLINE __attribute__((optimize("O3"))) inline
#define rep(i, l, r) for(register int i = l; i <= r; ++i)
#define dep(i, r, l) for(register int i = r; i >= l; --i)
#define lson o << 1
#define rson o << 1 | 1

typedef long long ll;
typedef unsigned long long ull;
const int maxn = 1e6 + 7;
const int arr = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;
const int base = 31;

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

int n, a[maxn], ans[maxn], qq;
int tree[maxn], vis[maxn], pre = 0;
struct query{
	int l, r, id;
	friend bool operator < (query a, query b) {
		return a.r < b.r;
	}
} q[maxn];
INLINE int lowbit(int x) { return x & -x; }
INLINE void insert(int x, int v) { for(int i = x; i <= n; i += lowbit(i)) tree[i] += v; }
INLINE int sum(int x) { int ans = 0; for(int i = x; i > 0; i -= lowbit(i)) ans += tree[i]; return ans; } 

int main() {
	n = getint();
	rep(i,1,n) a[i] = getint();
	qq = getint();
	rep(i,1,qq) {
		q[i].l = getint(), q[i].r = getint();
		q[i].id = i;
	}
	std::sort(q + 1, q + qq + 1);
	pre = 1;
	rep(i,1,qq) {
		rep(j,pre,q[i].r) {
			if(vis[a[j]]) insert(vis[a[j]], -1);
			insert(j, 1);
			vis[a[j]] = j;
		}
		pre = q[i].r + 1;
		ans[q[i].id] = sum(q[i].r) - sum(q[i].l - 1);
	}
	rep(i,1,qq) write(ans[i]), puts("");
	return 0;	
}
