#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

int n, k;

int main(){
	scanf("%d %d", &n, &k);
	if(k > n / 2) k = n - k + 1;
	printf("%d", n == 1 ? 1 : 2 * k);
	return 0;
}