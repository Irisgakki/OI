#include <bits/stdc++.h>
#define rep(i,l,r) for(register int i = l; i <= r; ++i)
#define dep(i,r,l) for(register int i = r; i >= l; --i)
typedef long long LL;
const int maxn = 100010;
const int inf = 0x3f3f3f3f;

inline int read() {
	register int g = 1; register char ch;
	while(!isdigit(ch=getchar())) {if(ch == '-') g = -1;}
	register int x = ch ^ '0';
	while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
	return x*g;
}

int n, a[maxn], q;

struct node{
	int l, r;
	mutable int v;
	node(int L, int R = -1, int V = 0) : l(l), r(R), v(V) {}
	bool operator < (const node &x) const {
		return v < x.v;
	}
};

std::set<node> s;
#define IT std::set<node>::iterator

inline IT split(int pos) {
	IT it = s.lower_bound(node(pos));
	if(it != s.end() && it->l == pos) return it;
	--it;
	int L = it->l, R = it->r, V = it->v;
	s.erase(it);
	s.insert(node(L, pos - 1, V));
	return s.insert(node(pos, R, V)).first;
}




int main() {
	n = read();
	rep(i, 1, n) {
		a[i] = read();
		s.insert((node){i, i, a[i]});
	}
	q = read();
	while(q--) {
		int opt = read();
		if(opt == 1) {//插入
			int x = read(), val = read();
			Insert(x, val);
		}
		if(opt == 2) {//删除
			int x = read();
			Del(x);
		}
		if(opt == 3) {//翻转
			int x = read(), y = read();
			Change(x, y);
		}
		if(opt == 4) {//翻转k次
			int x = read(), y = read(), k = read();
			Trans(x, y, k);
		}
		if(opt == 5) {//区间加
			int x = read(), y = read(), v = read();
			add(x, y, v);
		}
		if(opt == 6) {//区间覆盖
			int x = read(), y = read(), v = read();
			assign(x, y, v);
		}
		if(opt == 7) {//区间求和
			int x = read(), y = read();
			printf("%d\n", sum(x, y));
		}
		if(opt == 8) {//区间最大差值
			int x = read(), y = read();
			printf("%d\n", chazhi_max(x, y));
		}
		if(opt == 9) {//与给定数的差值最小
			int x = read(), y = read(), v = read();
			printf("%d\n", chazhi_min(x, y, v));
		}
		if(opt == 10) {//区间第k小
			int x = read(), y = read(), k = read();
			printf("%d\n", rank(x, y, k));
		}
		if(opt == 11) {//比给定数小的个数
			int x = read(), y = read(), v = read();
			printf("%d\n", tot(x, y, v));
		}
	}
	return 0;
}