#include <bits/stdc++.h>
#define int long long

const int maxn = 2010;
const int maxv = 500;
const int inf = 0x3f3f3f3f;

inline int read() {
    register int g = 1; register char ch;
    while(!isdigit(ch = getchar())) if(ch == '-') g = -1;
    register int x = ch ^ '0';
    while(isdigit(ch = getchar())) x = (((x << 2) + x) << 1) + (ch ^ '0');
    return x * g;
}

inline void print(int x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int T;
char col[maxn], peo[maxn];

signed main() {
    T = read();
    while(T--) {
        scanf("%s %s", col + 1, peo + 1);
        int len1 = strlen(col + 1);
        int len2 = strlen(peo + 1);
        int r = 0, b = 0, c1 = 0, c2 = 0;
        for(int i = 1; i <= len1;) {
            if(col[i] == 'R') {
                r++;
                while(col[i] == 'R') i++;
            }else if(col[i] == 'B') {
                b++;
                while(col[i] == 'B') i++;
            }
        }
        if(peo[1] == 'F') c1++;
        else c2++;
        for(int i = 2; i <= len2; ++i) {
            if(peo[i] == 'F') {
                c1++;
                if(c2 != 0) c2++;
            } else if(peo[i] == 'L') {
                c2++;
                if(c1 != 0) c1++;
            }
        }
        if(c1 >= r && c2 >= b) puts("Yes");
        else puts("No");
    }
    return 0;
}