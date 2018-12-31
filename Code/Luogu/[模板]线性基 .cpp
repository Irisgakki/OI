#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 7;
const int inf = 0x3f3f3f3f;
const int maxl = 55;

int n;
ll a[maxl];
ll b[maxl];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) {
        for(int j = maxl; j >= 0; --j) {
            if(a[i] >> j & 1) {
                if(b[j]) a[i] ^= b[j];
                else {
                    b[j] = a[i];
                    for(int k = j - 1; k >= 0; --k) if(b[k] && (b[j] >> k & 1)) b[j] ^= b[k];
                    for(int k = j + 1; k <= maxl; ++k) if(b[k] >> j & 1) b[k] ^= b[j];
                    break;
                }
            }
        }
    }
    ll res = 0;
    for(int i = 0; i <= maxl; ++i) res ^= b[i];
    cout << res;
    return 0;
}
