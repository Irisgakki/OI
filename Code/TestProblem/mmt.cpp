#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 7;
const int inf = 0x3f3f3f3f;

long long n;
int tot1 = 0;

int prime[maxn], phi = 1, top = 0;
bool not_prime[maxn];

inline long long fpow(long long a, long long n) {
    long long res = 1;
    for(; n; n >>= 1, a *= a)
        if(n & 1) res *= a;
    return res;
}

inline void sieve() {
    memset(not_prime, 0, sizeof(not_prime));
    not_prime[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        if(!not_prime[i]) prime[++top] = i;
        for(int j = 1; j <= top && i * prime[j] < maxn; ++j) {
            not_prime[i * prime[j]] = 1;
            if(!(i % prime[j])) break;
        }
    }
}

int main() {
    freopen("mmt.in","r",stdin);
    freopen("mmt.out","w",stdout);
    sieve();
    scanf("%lld", &n);
    tot1 = 0;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) tot1++;
    tot1 = (tot1 << 1) + 1;
    long long tmp = n;
    for(int i = 1; prime[i] * prime[i] <= n; ++i) {
        long long tot2 = 0;
        while(!(tmp % prime[i])) {
            tmp /= prime[i];
            tot2++;
        }
        if(tot2 > 0) {
            phi *= (prime[i] - 1) * fpow(prime[i], tot2 - 1);
        }
    }
    if(tmp > 1) phi *= (tmp - 1);
    // cerr << tot1 << endl;
    // cerr << phi << endl;
    printf("%lld\n", n - phi - tot1);
    return 0;
}