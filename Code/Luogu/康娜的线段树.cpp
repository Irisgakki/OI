#include <bits/stdc++.h>
#define re register
typedef int mainint;
#define int long long
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
    return X*w;
}

int n,m,qwq;
int ans=0,maxdep;
int s[1000010];

inline void build(int l,int r,int dep) { //并不用建树，只是求出s和初始化ans
    if (l==r) {
        s[l]=maxdep/dep*((dep<<1)-1);
        ans+=read()*s[l];
        s[l]+=s[l-1];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,dep<<1); build(mid+1,r,dep<<1);
}

mainint main() {
    n=read(),m=read(),qwq=read();
    for (maxdep=1;maxdep<n;maxdep<<=1); //找到最大的深度
    build(1,n,1);
    int d=__gcd(maxdep,qwq); qwq/=d,maxdep/=d; //约个分
    while (m--) {
        int x=read(),y=read(),z=read();
        ans+=(s[y]-s[x-1])*z;
        printf("%lld\n",ans*qwq/maxdep);
    }    
    return 0;
}