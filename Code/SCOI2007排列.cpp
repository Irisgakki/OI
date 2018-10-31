#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 1000010;
const int inf = 0x3f3f3f3f;

int n, x, a[11];
char s[11];
LL ans = 0;

int main(){
	scanf("%d", &n);
	while(n--) {
		ans = 0;
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		for(int i = 1; i <= len; ++i)
			a[i] = s[i] - '0';
		std::sort(a + 1, a + len + 1);
		scanf("%d", &x);
		do{
			LL now = 0;
			for(int i = 1; i <= len; ++i)
				now = now * 10 + a[i];
			if(now % x == 0) ans++;
		} while(std::next_permutation(a + 1, a + len + 1));
		printf("%lld\n", ans);
	}
	return 0;
}