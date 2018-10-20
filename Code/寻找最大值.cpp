#include <bits/stdc++.h>
typedef int mainint;
#define int long long
const int maxn = 1000100;
const int inf = 1 << 30;

int T, n;
int a[maxn], ans = -inf;

mainint main() {
        ans = -inf;
        scanf("%lld", &n);
        for(register int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
        std::sort(a + 1, a + 1 + n);
        for(register int i = n; i >= 1; --i) {
            if(1ll * a[i] * a[n] * a[n] <= ans) continue;
            for(register int j = i + 1; j <= n; ++j) {
                ans = std::max(ans, 1ll * a[i] * a[j] * (a[i] & a[j]));
            }
        }
        printf("%lld\n", ans);
    return 0;
}