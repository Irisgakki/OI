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
const int maxn = 4300;
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

int n;
int a[maxn], b[maxn], c[maxn], d[maxn];
int tmp1[maxn * maxn], tmp2[maxn * maxn];
int top1 = 0;

int main() {
    n = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read();
        b[i] = read();
        c[i] = read();
        d[i] = read();
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            tmp1[++top1] = a[i] + b[j];
            tmp2[top1] = c[i] + d[j];
        }
    }
    int res = 0;
    sort(tmp2 + 1, tmp2 + top1 + 1);
    for(int i = 1; i <= top1; ++i) {
        int now = -tmp1[i];
        res += upper_bound(tmp2 + 1, tmp2 + top1 + 1, now) - lower_bound(tmp2 + 1, tmp2 + top1 + 1, now);
    }
    print(res);
    return 0;
}