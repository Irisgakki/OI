#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<set>
#include<ctime>
#include<iostream>

using namespace std;
int n,m,s,T;

inline int random() {
    static int seed = s;
    return seed = (int)(seed*48271ll%2147483647);
}
set<int>to[100005];//去重

int main() {
    srand ( time ( NULL ) ) ;
    cin >> T;
    cout << T << endl;
    while(T--) {
        s = rand();
        n = 10;
        m = 20;
        printf("%d %d \n",n,m);
        for(int i = 1 ; i <= m ; i++) {
            int u = random() % n + 1;
            int v = random() % n + 1;
            while(to[u].find(v) != to[u].end() || u == v) {
                u = random() % n + 1;
                v = random() % n + 1;
            }
            printf("%d %d\n",u,v);
            to[u].insert(v);
        }
        printf("\n");
    }
    return 0;
}