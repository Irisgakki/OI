#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 1 << 30;

int n, p;
char ch[maxn];
int sum = 0;


int main() {
    scanf("%d %d %s", &n, &p, ch + 1);
    int first = 0, last = 0, flag = 1;
    for(int i = 1; i <= n / 2; ++i) {
        int tmp = abs(ch[i] - ch[n - i + 1]);
        if(tmp) {
            if(flag) {
                first = i;
                flag = 0;
            }
            last = i;
            sum += std::min(tmp, 26 - tmp);
        }
    }
    p > n / 2 ? p = n + 1 - p : p;
    int ans = 0;
    if(sum == 0) {
        printf("0\n");
        return 0;
    }
    if(p <= first)
        ans += sum + last - p;
    else if(p >= last)
        ans += sum + p - first;
    else
        ans += std::min(2 * (p - first) + last - p, 2 * (last - p) + p - first) + sum;
    printf("%d\n", ans);
    return 0;
}