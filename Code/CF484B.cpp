#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
typedef int mainint;
#define int long long
#define rr register
const int maxn = 1000010;
const int inf = 1 << 30;

int n, a[maxn], ans = 0, max = 0;

inline int cal(int x) {
    int ans = 0;
    int tmp = x;
    while(tmp < max) {
        tmp += x;
        int pos = std::lower_bound(a + 1, a + n + 1, tmp) - a;
        if(pos == 0) continue;
        else pos--;
        if(a[pos] <= x) continue;
        ans = std::max(ans, a[pos] % x);
    }
    return ans;
}

mainint main() {
    scanf("%lld", &n);
    for(rr int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        max = std::max(max, a[i]);
    }
    std::sort(a + 1, a + n + 1);
    for(rr int i = n; i >= 1; --i) {
        if(ans >= a[i] - 1) break;
        if(i + 1 <= n && a[i] == a[i + 1]) continue;
        ans = std::max(ans, cal(a[i]));
    }
    printf("%lld\n", ans);
    return 0;
}