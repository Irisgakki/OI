#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 1e7 + 10;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int n, m, k, T;
int blo, a[maxn], cnt[maxn], ans;
int res[maxn];

struct Mo{
    int l, r;
    int id;
    friend bool operator < (Mo a, Mo b) {
        return (a.l / blo) ^ (b.l / blo) ? a.l < b.l : (((a.l / blo) & 1) ? a.r < b.r : a.r > b.r);
    }
} mo[maxn];

inline void add(int i) {
	if(cnt[a[i]] == T) ans--;
	cnt[a[i]]++;
	if(cnt[a[i]] == T) ans++;
}

inline void del(int i) {
	if(cnt[a[i]] == T) ans--;
	cnt[a[i]]--;
	if(cnt[a[i]] == T) ans++;
}

inline void solve() {
	int l = 0, r = 0;
	for(int i = 1; i <= m; ++i) {
		int ql = mo[i].l, qr = mo[i].r;
		while(l < ql) del(l++);
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(r > qr) del(r--);
		res[mo[i].id] = ans;
	}
}

int main() {
	n = read(), m = read(), k = read(), T = read();
	blo = sqrt(n/log(n));
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
	}
	for(int i = 1; i <= m; ++i) {
		mo[i].l = read(), mo[i].r = read();
		mo[i].id = i;
	}
	std::sort(mo + 1, mo + 1 + m);
	solve();
	for(int i = 1; i <= m; ++i) {
		print(res[i]), puts("");
	}
	return 0;
}
