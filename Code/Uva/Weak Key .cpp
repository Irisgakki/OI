#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<climits>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<numeric>
#include<iomanip>
#include<bitset>
#include<sstream>
#include<fstream>
#define debug puts("-----")
#define rg register
#define pts puts("")
#define pii pair<int, int>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
template <class T> T chkmax(T a, T b) {return a > b ? a : b;}
template <class T> T chkmin(T a, T b) {return a > b ? b : a;}
const int maxn = 1e5 + 7;
const int INF = 0x3f3f3f3f;
const int mod = 19260817;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (x * 10) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int T, n;
int a[maxn], b[maxn];

struct ST_table{
    int st[maxn][31];
    inline int query(int l, int r) {
        int k = log2(r - l + 1);
        return max(st[l][k], st[r - (1 << k) + 1][k]);
    }
    inline void init(const int &n, int *a) {
        for(int i = 1; i <= n; ++i) st[i][0] = a[i];
        for(int j = 1; j <= 30; ++j) {
            for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
            }
        }
    }
    inline bool check(const int &n, int *a) {
        vector<int> v[maxn];
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                if(a[i] < a[j]) v[i].push_back(a[j]);
            }
            std::sort(v[i].begin(), v[i].end());
        }
        for(int i = 1; i <= n; ++i) {
            for(int j = i + 2; j <= n; ++j) {
                if(a[i] <= a[j]) continue;
                int q = query(i, j - 1);
                if(q <= a[j]) continue;
                vector<int>::iterator it = lower_bound(v[j].begin(), v[j].end(), a[i]);
                if(it == v[j].end()) continue;
                if(*it < q) return 1;
            }
        }
        return 0;
    }
} ans[3];

int main() {
    T = read();
    while(T--) {
        n = read();
        for(int i = 1; i <= n; ++i) a[i] = read(), b[n - i + 1] = a[i];
        ans[1].init(n, a), ans[2].init(n, b);
        if(ans[1].check(n, a) || ans[2].check(n, b)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
