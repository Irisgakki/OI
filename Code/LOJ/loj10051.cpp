#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 1e7;
const int inf = 0x3f3f3f3f;

int n;
int a[maxn];

int trie[maxn][2], tot = 1;
int l[maxn], r[maxn];

inline void insert(int x) {
    int p = 1;
    for (int i = 31; i >= 0; --i) {
        int ch = (x >> i) & 1;
        if (!trie[p][ch])
            trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
}

inline int search(int x) {
    int p = 1, ans = 0;
    for (int i = 31; i >= 0; --i) {
        int ch1 = (x >> i) & 1;
        int ch2 = ch1 ^ 1;
        if (trie[p][ch2])
            p = trie[p][ch2], ans = ans << 1 | 1;
        else
            p = trie[p][ch1], ans = ans << 1;
    }
    return ans;
}

inline void solve() {
    int tmp = 0;
    insert(0);
    for (int i = 1; i <= n; ++i) {
        tmp ^= a[i];
        if (i != 0)
            l[i] = max(l[i - 1], search(tmp));
        insert(tmp);
    }
    tmp = 0, tot = 1;
    memset(trie, 0, sizeof(trie));
    insert(0);
    for (int i = n; i >= 1; --i) {
        tmp ^= a[i];
        if (i != n)
            r[i] = max(r[i + 1], search(tmp));
        insert(tmp);
    }
    int ans = 0;
    for (int i = 1; i <= n - 1; ++i) ans = max(ans, l[i] + r[i + 1]);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    solve();
    return 0;
}
