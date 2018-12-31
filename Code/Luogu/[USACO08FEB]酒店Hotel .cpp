#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;
const int inf = 0x3f3f3f3f;

int n, m;

namespace Segment_Tree {
  #define lson o << 1
  #define rson o << 1 | 1
  struct Segment {
    int l, r, size, tag, sum;
    int lmax, rmax;
  };
  Segment seg[maxn << 2];
  inline void up(int o) {
    seg[o].lmax = (seg[lson].lmax == seg[lson].size) ? seg[lson].size + seg[rson].lmax : seg[lson].lmax;
    seg[o].rmax = (seg[rson].rmax == seg[rson].size) ? seg[rson].size + seg[lson].rmax : seg[rson].rmax;
    seg[o].sum = max(max(seg[lson].sum, seg[rson].sum), seg[lson].rmax + seg[rson].lmax);
  }
  inline void down(int o) {
    if(seg[o].tag) {
      seg[lson].tag = seg[rson].tag = seg[o].tag;
      seg[lson].sum = seg[lson].lmax = seg[lson].rmax = (seg[o].tag == 1) ? seg[lson].size : 0;
      seg[rson].sum = seg[rson].lmax = seg[rson].rmax = (seg[o].tag == 1) ? seg[rson].size : 0;
      seg[o].tag = 0;
    }
  }
  inline void build(int o, int l, int r) {
    seg[o].l = l, seg[o].r = r;
    seg[o].sum = seg[o].size = seg[o].lmax = seg[o].rmax = r - l + 1;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    build(lson, l, mid); build(rson, mid + 1, r);
  }
  inline void modify(int o, int l, int r, int type) {
    if(l <= seg[o].l && seg[o].r <= r) {
      if(type == 1) seg[o].sum = seg[o].lmax = seg[o].rmax = seg[o].size;
      if(type == 2) seg[o].sum = seg[o].lmax = seg[o].rmax = 0;
      seg[o].tag = type;
      return ;
    }
    down(o);
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(l <= mid) modify(lson, l, r, type);
    if(r > mid) modify(rson, l, r, type);
    up(o);
  }
  inline int query(int o, int len) {
    if(seg[o].l == seg[o].r) return seg[o].l;
    down(o);
    int mid = (seg[o].l + seg[o].r) >> 1;
    if(seg[lson].sum >= len) return query(lson, len);
    if(seg[lson].rmax + seg[rson].lmax >= len) return (mid - seg[lson].rmax + 1);
    return query(rson, len);
    up(o);
  }
};

int main() {
  using namespace Segment_Tree;
  ios::sync_with_stdio(false);
  cin >> n >> m;
  build(1, 1, n);
  for(int i = 1; i <= m; ++i) {
    int opt;
    cin >> opt;
    switch (opt) {
      case 1: {
        int x, last;
        cin >> x;
        if(seg[1].sum >= x) {
          last = query(1, x);
          cout << last << '\n';
          modify(1, last, last + x - 1, 2);
        } else cout << "0" << '\n';
        break;
      }
      case 2: {
        int x, y;
        cin >> x >> y;
        modify(1, x, x + y - 1, 1);
        break;
      }
    }
  }
  return 0;
}
