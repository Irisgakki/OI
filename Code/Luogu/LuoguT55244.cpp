#include <bits/stdc++.h>

typedef long long LL;
const int maxn = 500;
const int inf = 0x7f7f7f7f;

inline int read(){
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

int n, m, q, sum = 0, r, k;
int row[3000], flag = 0, roww;
char a[maxn][maxn];

inline int assign(int r, int k) {
	flag = 0;
    if(row[r] >= k) {
        int tot = 0, maxx = 0;
        for(int i = 1; i <= m; ++i) {
            if(a[r][i] == '-') {
            	tot++;
				if(a[r][i + 1] == '#' || i == m) {
					if(tot > maxx) maxx = tot;
					if(maxx >= k) return 1;
					tot = 0;
					continue;
				}
            }
        }
        if(maxx < k) flag = 1;
        return 1;
    } else {
        for(int i = 1; i <= n; ++i) {
        	int tot = 0, maxx = 0;
        	if(row[i] < k) continue;
			else {
				for(int j = 1; j <= m; ++j) {
					if(a[i][j] == '-') {
						tot++;
						if(a[i][j + 1] == '#' || j == m) {
							if(tot > maxx) maxx = tot;
							if(maxx >= k) {
								roww = i;
								return 2;	
							}
							tot = 0;
							continue;	
						}
					}
				}
				if(maxx >= k) {
					roww = i;
					return 2;
				}
			}
        }
        return 3;
    }
}

int main() {
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) {
        int tmp = 0;
        for(int j = 1; j <= m; ++j) {
            scanf(" %c", &a[i][j]);
            if(a[i][j] == '-') sum++, tmp++; 
        }
        row[i] = tmp;
    }
    q = read();
    while(q--) {
        r = read(), k = read();
        int b;
        if(r > n) printf("Theater only contains %d rows\n", n);
        else if(k > sum) printf("Sold out\n");
        else if(b = assign(r, k)) {
            if(b == 1) {
                if(flag == 0) {
                    int tot = 0, pos, maxx = 0;
                	for(int i = 1; i <= m; ++i) {
            			if(a[r][i] == '-') {
            				tot++;
							if(a[r][i + 1] == '#' || i == m) {
								if(tot > maxx) maxx = tot, pos = i + 1;
								if(maxx >= k) break;
								tot = 0;
								continue;
							}
            			}
        			}
        			int tt = 0;
        			for(int i = pos - maxx; i <= m && tt < k; ++i) {
        				if(a[r][i] == '#') continue;
						sum--;
						tt++;
						a[r][i] = '#';
						row[r]--;
						printf("%d%c ", r, (char)(i + 'A' - 1));	
        			}
        			puts("");
                } else {
                	int tot = 0;
                    for(int i = 1; i <= m && tot < k; ++i) {
                        if(a[r][i] == '#') continue;
                        sum--;
                        tot++;
                        a[r][i] = '#';
                        row[r]--;
                        printf("%d%c ", r, (char)(i + 'A' - 1));
                    }
                    puts("");
                }
            } else if(b == 2) {
                int tot = 0, maxx = 0, pos = 0;
                for(int i = 1; i <= m; ++i) {
                	if(a[roww][i] == '-') {
                		tot++;
						if(a[roww][i + 1] == '#' || i == m) {
							if(tot > maxx) maxx = tot;
							if(maxx >= k) {
								pos = i + 1;
								break;	
							}
							tot = 0;
							continue;
						}
                	}
                }
                int tt = 0;
                for(int i = pos - tot; i <= m && tt < k; ++i) {
                	if(a[roww][i] == '#') continue;
					sum--;
					tt++;
					a[roww][i] = '#';
					row[roww]--;
					printf("%d%c ", roww, (char)(i + 'A' - 1));	
                }
                puts("");
            } else if(b == 3) {
                printf("Please contact our staff to buy tickets\n");
            }
        }
    }
    return 0;
}