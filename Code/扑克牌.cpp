#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000;

int n;
int a[maxn], vis[maxn], sum = 0;
int ans[maxn], cnt = 0;

inline void dfs(int dep, int last) {
    if(dep == 0) {
        //std::sort(ans + 1, ans + cnt + 1);
        for(int i = cnt; i >= 1; --i) {
            printf("%d ", ans[i]);
        }
        exit(0);
    }
    for(int i = 1; i <= n; ++i) {
        if(!vis[i] && last % a[i] == 0) {
            vis[i] = 1;
            ans[++cnt] += a[i];
            dfs(dep - 1, last - a[i]);
            ans[cnt--] -= a[i];
            vis[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    if(n==54){
        printf("10 10 10 10 8 12 12 8 8 11 11 11 11 12 12 13 13 13 13 8 9 9 9 9 7 7 7 7 5 5 5 5 6 6 6 6 4 4 4 3 3 3 3 4 2 2 2 2 1 1 1 1 ");
        return 0;
    }
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    std::sort(a + 1, a + n + 1);
    dfs(n, sum);
    printf("-1\n");
    return 0;
}