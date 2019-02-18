#include <bits/stdc++.h>
#define rep(i,l,r) for(int i = (l); i <= (r); ++i)
#define dep(i,r,l) for(int i = (r); i >= (l); --i)
#define pts puts("")
using namespace std;
typedef long long ll;

struct InputOutputStream {
    enum { SIZE = 1024 * 1024 };
    char ibuf[SIZE], *s, *t, obuf[SIZE], *oh;
    InputOutputStream() : s(), t(), oh(obuf) {}
    ~InputOutputStream() { fwrite(obuf, 1, oh - obuf, stdout); }
    inline char read() {
        if (s == t) t = (s = ibuf) + fread(ibuf, 1, SIZE, stdin);
        return s == t ? -1 : *s++;
    }
    template <typename T>
    inline InputOutputStream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) return *this;
            iosig |= c == '-';
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        if (iosig) x = -x;
        return *this;
    }
    inline void print(char c) {
        if (oh == obuf + SIZE) {
            fwrite(obuf, 1, SIZE, stdout);
            oh = obuf;
        }
        *oh++ = c;
    }
    template <typename T>
    inline void print(T x) {
        static int buf[21], cnt;
        if (x != 0) {
            if (x < 0) {
                print('-');
                x = -x;
            }
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
            while (cnt) print((char)buf[cnt--]);
        } else {
            print('0');
        }
    }
    template <typename T>
    inline InputOutputStream &operator<<(const T &x) {
        print(x);
        return *this;
    }
} io;

namespace Hash_Table{
    const int base = 1000007;
    struct Node{
        ll val;
        int next;
    } node[1000005];
    int head[1000005], cur = 0;
    void initHash() {
        memset(head, -1, sizeof(head));
        cur = 0;
    }
    void insertHash(ll val) {
        int num = (int)(val % base + base) % base;
        node[cur].val = val;
        node[cur].next = head[num];
        head[num] = cur++;
    }
    bool searchHash(ll val) {
        int num = (int)(val % base + base) % base;
        for(int i = head[num]; i != -1; i = node[i].next)
            if(node[i].val == val) return true;
        return false;
    }
};

int n, k;
int a[1000010];
ll sum[1000010];

int main() {
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    //using namespace Hash_Table;
    int T;
    io >> T;
    rep(cas, 1, T) {
        io >> n >> k;
        rep(i,1,n) io >> a[i];
        rep(i,1,n) {
            if(i & 1) sum[i] = sum[i - 1] + a[i];
            else sum[i] = sum[i - 1] - a[i];
        }
        initHash();
        insertHash(sum[n]);
        bool flag = 0;
        dep(i,n,1) {
            if((i & 1) && searchHash(sum[i - 1] + k)) {
                flag = 1; break;
            }
            if(!(i & 1) && searchHash(sum[i - 1] - k)) {
                flag = 1; break;
            }
            insertHash(sum[i]);
        }
        if(flag) printf("Case #%d: Yes.\n", cas);
        else printf("Case #%d: No.\n", cas);
    }
    return 0;
}