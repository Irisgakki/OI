#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <vector>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)


inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, q, sum;

struct node{
    int l,r;
    mutable int v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator < (const node& o) const {
        return l<o.l;
    }
};

std::set<node> s;
#define IT std::set<node>::iterator

inline IT split(int pos) {
	IT it = s.lower_bound(node(pos));
	if(it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r;
	int V = it->v;
	s.erase(it);
	s.insert(node(L, pos - 1, V ? pos - L : 0));
	return s.insert(node(pos, R, V ? R - pos + 1 : 0)).first;
}

inline void assign(int l, int r, int val) {
	IT itr = split(r + 1), itl = split(l);//注意拆分顺序
	for(IT it = itl; it != itr; ++it) 
		sum -= it->v;
	s.erase(itl, itr);
	s.insert(node(l, r, val * (r - l + 1)));
	sum += val * (r - l + 1);
}

int main() {
	scanf("%d %d", &n, &q);
	s.insert(node(1, n, 1));
	sum = n;
	while(q--) {
		int l, r, opt;
		scanf("%d %d %d", &l, &r, &opt);
		if(opt == 1) assign(l, r, 0);
		else assign(l, r, 1);
		printf("%d\n", sum);
	}
	return 0;
}