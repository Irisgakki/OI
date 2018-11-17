#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
typedef long long ll;

const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline char gc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	if(p1 == p2) {
		p2 = (p1 = buf) + fread(buf, 1, 100000, stdin);
		if(p1 == p2) return EOF;
	}
	return *p1++;
}

inline ll getint(){
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register ll x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
	return x * g;
}

inline void print(ll x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

ll a, b, x, y, p;

inline ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

inline ll mul(ll a, ll b, ll p) {
	ll res = 0;
	while(b) {
		if(b & 1) res = (res + a) % p;
		b >>= 1;
		a = (a + a) % p;
	}
	return res;
}

inline ll fpow(ll a, ll n, ll p) {
	ll res = 1;
	while(n) {
		if(n & 1) res = mul(res, a, p);
		n >>= 1;
		a = mul(a, a, p);
	}
	return res;
}

int main() {
	x = getint(), y = getint(), a = getint(), b = getint(), p = getint();
	ll t = gcd(a, b);
	print((fpow(x, t, p) - fpow(y, t, p) + p) % p);
	return 0;
}