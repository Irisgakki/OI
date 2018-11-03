#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 2e5 + 10;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n;
int a[maxn], tr[maxn];
std::vector<int> vec[maxn];

inline int lowbit(int x){
	return x & -x;
}

inline void add(int x, int v) {
	for(int i = x; i <= n; i += lowbit(i))
		tr[i] += v;
}

inline int query(int x){
	int ans = 0;
	for(int i = x; i > 0; i -= lowbit(i))
		ans += tr[i];
	return ans;
}

LL ans = 0;

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		a[i] = std::min(a[i], n);
		vec[std::min(i - 1, a[i])].push_back(i);
	}
	memset(tr, 0, sizeof(tr));
	for(int i = 1; i <= n; ++i) {
		add(a[i], 1);
		for(int j = 0; j < vec[i].size(); ++j)
			ans += query(n) - query(vec[i][j] - 1);
	}
	printf("%I64d\n", ans);
	return 0;
}