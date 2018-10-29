#include <bits/stdc++.h>
#define int long long
const int maxn = 1000010;
const int inf = 1e18;
const int mod = 998244353;

inline int read(){
	register int x = 0, g = 1; register char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') g = - 1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (((x << 2) + x) << 1) + (ch ^ '0'); ch = getchar(); }
	return x * g;
}

int n, a[maxn];
std::vector<int> vec;

inline bool check(int x){
	for(int i = 0; i < n; ++i){
		if(a[i] != a[i % x])
			return 0;
	}
	return 1;
}

signed main(){
	n = read();
	for(int i = 0; i < n; ++i)
		a[i] = read();
	for(int i = n - 1; i >= 1; --i)
		a[i] -= a[i - 1];
	for(int i = 1; i <= n; ++i)
		if(check(i)) vec.push_back(i);
	printf("%d\n", vec.size());
	for(int i = 0; i < vec.size(); ++i)
		printf("%I64d ", vec[i]);
	return 0;
}