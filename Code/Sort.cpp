#include<cstdio>
#include<cctype>
#include<climits>
#include<algorithm>
inline int getint() {
    register char ch;
    while(!isdigit(ch=getchar()));
    register int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
const int N=5e4+1;
int a[N];
inline bool check(const int &b,const int &e) {
    for(register int i=b;i<e;i++) {
        if(a[i]>a[i+1]) return false;
    }
    return true;
}
void solve(const int &b,const int &e,const int &x) {
    if(b==e) return;
    const int mid=(b+e)>>1;
    solve(b,mid,x);
    solve(mid+1,e,x);
    int p=b,q=e;
    while(p<=mid&&a[p]<=x) p++;
    while(q>mid&&a[q]>x) q--;
    if(p<=mid&&q>mid) {
        printf("%d %d\n",p,q);
        std::reverse(&a[p],&a[q]+1);
    }
}
void solve(const int &b,const int &e) {
    if(b>=e) return;
    if(check(b,e)) return;
    const int x=a[b+rand()%(e-b+1)];
    solve(b,e,x);
    for(register int i=b;i<=e;i++) {
        if(a[i]>x) {
            solve(b,i-1);
            solve(i,e);
            return;
        }
    }
    solve(b,e);
}
int main() {
    srand(998244353);
    const int n=getint();
    for(register int i=1;i<=n;i++) a[i]=getint();
    solve(1,n);
    puts("-1 -1");
    return 0;
}
