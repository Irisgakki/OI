#include <bits/stdc++.h>

using namespace std;

const int maxn = 110;
const int inf = 0x3f3f3f3f;
const int base = 31;
const int mod = 1e7;

int n, m, top = 0;
int nex[maxn];
int vis[mod + 1];
char vt[maxn][maxn * 3];
char bd[maxn][maxn * 3];

inline int hash(const char *a) {
	int ans = 0;
	int len = strlen(a + 1);
	for(int i = 1; i <= len; ++i) {
		ans = (ans * base + a[i]) % mod;
	}
	return ans % mod;
}

inline int kmp(const char *a, const char *b) {
	int len1 = strlen(a + 1), len2 = strlen(b + 1);
	int j = 0;
	for(int i = 2; i <= len2; ++i) {
		if(j && b[i] != b[j + 1]) j = nex[j];
		if(b[i] == b[j + 1]) ++j;
		nex[i] = j;
	}
	j = 0;
	for(int i = 1; i <= len1; ++i) {
		if(j && a[i] != b[j + 1]) j = nex[j];
		if(a[i] == b[j + 1]) ++j;
		if(j == len2) return 1;
	}
	return 0;
}

int main() {
	freopen("patch.in","r",stdin);
	freopen("patch.out","w",stdout);	
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", vt[i] + 1);
		int len = strlen(vt[i] + 1);
		for(int j = 1; j <= len; ++j)
			if(vt[i][j] >= 'A' && vt[i][j] <= 'Z')
				vt[i][j] = vt[i][j] - 'A' + 'a';
		vis[hash(vt[i])] = 0;
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%s", bd[i] + 1);
		int len = strlen(bd[i] + 1);
		for(int j = 1; j <= len; ++j)
			if(bd[i][j] >= 'A' && bd[i][j] <= 'Z')
				bd[i][j] = bd[i][j] - 'A' + 'a';
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		int len1 = strlen(vt[i] + 1);
		int hh = hash(vt[i]);
		for(int j = 1; j <= m; ++j) {
			int len2 = strlen(bd[j] + 1);
			int tmp;
			if(len1 > len2) {
				if(!vis[hh]) {
					tmp = kmp(vt[i], bd[j]);
					if(tmp) ans++, vis[hh] = 1;
				}
			} else {
				if(!vis[hh]) {
					tmp = kmp(bd[j], vt[i]);
					if(tmp) ans++, vis[hh] = 1;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
} 
