#include <bits/stdc++.h>
typedef int mainint;
#define int long long
const int maxn = 100010;
const int inf = 1 << 30;

int n, x, y;
int hp;

int main() {
    scanf("%lld %lld %lld", &n, &x, &y);
    for(register int i = 1; i <= n; ++i) {
        scanf("%lld", &hp);
        int l = 1, r = inf;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(x / mid + y / mid >= hp) r = mid - 1;
            else l = mid + 1;
        }
        if(!(r % x) && !(r % y)) printf("Both\n");
        else if(!(r % x)) printf("Yuan\n");
        else if(!(r % y)) printf("Fang\n");
    }

    return 0;
}