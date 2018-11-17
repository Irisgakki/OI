#include <bits/stdc++.h>
#define int long long

const int maxn = 2e5 + 10;
const int maxv = 500;
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

int n, s, ans = 0;
int a[maxn];

signed main() {
    n = read(), s = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    std::sort(a + 1, a + n + 1);
    int mid = n / 2 + 1;
    for(int i = 1; i <= mid; ++i) {
        if(a[i] > s) {
            ans += a[i] - s;
        }
    }
    for(int i = mid; i <= n; ++i) {
        if(a[i] < s) {
            ans += s - a[i];
        }
    }
    print(ans);
    return 0;
}