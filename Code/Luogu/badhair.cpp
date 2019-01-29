#include <bits/stdc++.h>

using namespace std;

const int maxn = 80007;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
	register int x = ch ^ '0';
	while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
	return x * g;
}

inline void write(long long x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');	
}

int n;
int top = 0;
long long h[maxn], c[maxn];
long long s[maxn];
long long ans = 0;

int main() {
	freopen("badhair.in","r",stdin);
	freopen("badhair.out","w",stdout);
	n = read();
	for(int i = 1; i <= n; ++i) h[i] = read();
	s[++top] = h[1];
	for(int i = 2; i <= n; ++i) {
		while(top && s[top] <= h[i]) top--;
		ans += top;
		s[++top] = h[i];
	}
	write(ans);
	return 0;
}