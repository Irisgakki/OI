#include <bits/stdc++.h>
#define int long long

const int maxn = 1e5 + 7;
const int inf = 0x3f3f3f3f;

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

int n, W;
int a[maxn], b[maxn];


signed main() {
    n = read(), W = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    for(int i = 1; i <= n; ++i) b[i] = read();
    std::sort(a + 1, a + n + 1, std::greater<int>());
    std::sort(b + 1, b + n + 1, std::greater<int>());
    for(int i = 1; i <= n; ++i) a[i] += a[i - 1];
    for(int i = 1; i <= n; ++i) b[i] += b[i - 1];
	int ans = 0;
    for(int i = 0; i <= n; ++i) {
        int j = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
        if(j <= n) ans = std::max(ans, a[i] - (i + j) * W);
    }
    for(int i = 0; i <= n; ++i) {
        int j = std::lower_bound(a + 1, a + n + 1, b[i]) - a;
        if(j <= n) ans = std::max(ans, b[i] - (i + j) * W);
    }
    print(ans);
    return 0;
}

