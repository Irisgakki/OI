#include<bits/stdc++.h>
#define Mod 998244353
#define LL long long
using namespace std;
LL Opt[21],C[21][21],Ans;
int n,m;
void Init(){
    C[0][0]=1;
    for(int i=1;i<=20;++i)
        C[i][0]=1;
    for(int i=1;i<=20;++i)
        for(int j=1;j<=20;++j)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
    Opt[0]=1;
    for(int i=1;i<=20;++i)
        for(int j=1;j<=i;++j)
            Opt[i]=(Opt[i]+Opt[i-j]*C[i][j])%Mod;
}
void Doit(){
    char c;
    int Flag;
    LL Count,A;
    scanf("%d%d",&n,&m);
    while(m--){
        Count=0;
        Flag=0;
        while(Flag<n){
            while((c=getchar())<'0'||c>'1');
            if(c=='1')
                ++Count;
            ++Flag;
        }
        scanf("%lld",&A);
        Ans=(Ans+A*Opt[Count]%Mod*Opt[n-Count]%Mod)%Mod;
    }
    printf("%lld\n",Ans);
}
int main(){
    Init();
    Doit();
    return 0;
}