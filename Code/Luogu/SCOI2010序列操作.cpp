#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 1010;
const int inf = 0x3f3f3f3f;
const int mod = 1e9 + 7;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, m, a[maxn];

struct node{
    int l, r;
    mutable int v;
    node(int L, int R = -1, int V = 0): l(L), r(R), v(V) {}
    bool operator < (const node &o) const {
        return l < o.l;
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
	s.insert(node(L, pos - 1, V));
	return s.insert(node(pos, R, V)).first;
}

inline void assign(int l, int r, int v){
	IT itr = split(r + 1), itl = split(l);
	s.erase(itl, itr);
	s.insert(node(l, r, v));
}

inline void modify_rev(int l, int r){
	IT itr = split(r + 1), itl = split(l);
	for(; itl != itr; ++itl)
		if(itl->v == 1) itl->v = 0;
		else if(itl->v == 0) itl->v = 1;
}

inline int query(int l, int r) {
	int ans = 0;
	IT itr = split(r + 1), itl = split(l);
	//std::cerr<<itl->l<<" "<<itr->r;
	for(; itl != itr; ++itl)
		ans += itl->v == 1 ? itl->r - itl->l + 1 : 0; 
	return ans;
}

inline int query_one(int l, int r) {
	int maxx = 0, tot = 0;
	IT itr = split(r + 1), itl = split(l);
	for(; itl != itr; ++itl) {
		if(itl->v == 1) tot += itl->r - itl->l + 1;
		else if(itl->v == 0) {
			maxx = std::max(maxx, tot);
			tot = 0;
		}
	}
	return std::max(maxx, tot);
}

int main(){
	n = read(), m = read();
	rep(i, 1, n) {
		a[i] = read();
		s.insert(node(i, i, a[i]));
	}
	while(m--) {
		int opt = read(), l = read() + 1, r = read() + 1;
		if(opt == 0) assign(l, r, 0);
		if(opt == 1) assign(l, r, 1);
		if(opt == 2) modify_rev(l, r);
		if(opt == 3) printf("%d\n", query(l, r));
		if(opt == 4) printf("%d\n", query_one(l, r));
	}
	return 0;
}
