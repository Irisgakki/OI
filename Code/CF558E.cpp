#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

char s[1000001];     
int n,m,sum[27][400001],lazy[27][400001];

inline int rd(){
    register int x=0,y=1;
    register char c=getchar();
    while(c>'9' or c<'0'){
        if(c=='-'){
            y=-1;
        }
        c=getchar();
    }
    while(c>='0' and c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*y;
}

inline void pushup(int o,int rt){
    sum[rt][o]=sum[rt][o<<1]+sum[rt][o<<1|1];
}

inline void pushdown(int o,int l,int r,int rt){
    if(lazy[rt][o]!=-1){
        int mid=(l+r)>>1;
        sum[rt][o]=lazy[rt][o]*(r-l+1);
        sum[rt][o<<1]=lazy[rt][o]*(mid-l+1);
        sum[rt][o<<1|1]=lazy[rt][o]*(r-mid);
        lazy[rt][o<<1]=lazy[rt][o<<1|1]=lazy[rt][o];
        lazy[rt][o]=-1;
    }
}

void build(int o,int l,int r){
    if(l==r){
        sum[s[l]-'a'+1][o]=1;
        return;
    }
    int mid=(l+r)>>1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    for(int i=1;i<=26;i++)pushup(o,i);
}

inline int query(int o,int l,int r,int x,int y,int rt){
    if(x<=l and y>=r){
        return sum[rt][o];
    }
    pushdown(o,l,r,rt);
    int mid=(l+r)>>1,ret=0;
    if(x<=mid)ret+=query(o<<1,l,mid,x,y,rt);
    if(y>mid)ret+=query(o<<1|1,mid+1,r,x,y,rt);
    return ret;
}

inline void update(int o,int l,int r,int x,int y,int rt,int v){
    if(x<=l and y>=r){
        lazy[rt][o]=v;
        sum[rt][o]=v*(r-l+1);
        return;
    }
    pushdown(o,l,r,rt);
    int mid=(l+r)>>1;
    if(x<=mid)update(o<<1,l,mid,x,y,rt,v);
    if(y>mid)update(o<<1|1,mid+1,r,x,y,rt,v);
    pushup(o,rt);
}

void output(int o,int l,int r){
    if(l==r){
        for(int i=1;i<=26;i++){
            if(sum[i][o]){
                s[l]='a'+i-1;
                break;
            }
        }
        return;
    }
    for(int i=1;i<=26;i++)pushdown(o,l,r,i);
    int mid=(l+r)>>1;
    output(o<<1,l,mid);
    output(o<<1|1,mid+1,r);
}

int main(){
    for(int i=1;i<=26;i++)memset(lazy[i],-1,sizeof(lazy[i]));
    n=rd(),m=rd();
    scanf("%s",s+1);
    build(1,1,n);
    while(m--){
        int x=rd(),y=rd();
        if(rd()){
            int tmp=x-1;
            for(int i=1;i<=26;i++){
                int cas=query(1,1,n,x,y,i);
                if(!cas)continue;
                update(1,1,n,x,y,i,0);
                update(1,1,n,tmp+1,tmp+cas,i,1);tmp=tmp+cas;
            }
        }else {
            int tmp=x-1;
            for(int i=26;i>=1;i--){
                int cas=query(1,1,n,x,y,i);
                if(!cas)continue;
                update(1,1,n,x,y,i,0);
                update(1,1,n,tmp+1,tmp+cas,i,1);tmp=tmp+cas;
            }
        }
    }
    output(1,1,n);
    printf("%s\n",s+1);
    return 0;
}