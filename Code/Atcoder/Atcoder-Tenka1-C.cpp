    #include <bits/stdc++.h>
    typedef long long LL;
    const int maxn = 300010;
    const int inf = 0x3f3f3f3f;
     
    LL n, a[maxn];
    static LL ans1, ans2;
    static LL last1, last2;
    static int now1, now2;
     
    int main(){
    	scanf("%lld", &n);
    	for(int i = 1; i <= n; ++i)
    		scanf("%lld", &a[i]);
    	std::sort(a + 1,a + n + 1);
    	ans1 += abs(a[n] - a[1]) + abs(a[n - 1] - a[1]);
    	last1 = a[n], last2 = a[n - 1];
    	now1 = 2, now2 = n - 3;
    	while(now1 <= now2) {
    		int tmp1 = abs(a[now1] - last1);
    		int tmp2 = abs(a[now1] - last2);
    		int tmp3 = abs(a[now2] - last1);
    		int tmp4 = abs(a[now2] - last2);
    		if(tmp1 > tmp2) {
    			if(tmp3 > tmp4) {
    				if(tmp1 > tmp3) {
    					ans1 += tmp1;
    					last1 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans1 += tmp3;
    					last1 = a[now2];
    					now2--;
    					continue;
    				}
    			} else{
    				if(tmp1 > tmp4) {
    					ans1 += tmp1;
    					last1 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans1 += tmp4;
    					last2 = a[now2];
    					now2--;
    					continue;
    				}
    			}
    		} else{
    			if(tmp3 > tmp4) {
    				if(tmp2 > tmp3) {
    					ans1 += tmp2;
    					last2 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans1 += tmp3;
    					last1 = a[now2];
    					now2--;
    					continue;
    				}
    			} else{
    				if(tmp2 > tmp4) {
    					ans1 += tmp2;
    					last2 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans1 += tmp4;
    					last2 = a[now2];
    					now2--;
    					continue;
    				}
    			}
    		}
    	}
    	ans2 += abs(a[n] - a[1]) + abs(a[n] - a[2]);
    	last1 = a[1], last2 = a[2];
    	now1 = 3, now2 = n - 1;
    		while(now1 <= now2) {
    		int tmp1 = abs(a[now1] - last1);
    		int tmp2 = abs(a[now1] - last2);
    		int tmp3 = abs(a[now2] - last1);
    		int tmp4 = abs(a[now2] - last2);
    		if(tmp1 > tmp2) {
    			if(tmp3 > tmp4) {
    				if(tmp1 > tmp3) {
    					ans2 += tmp1;
    					last1 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans2 += tmp3;
    					last1 = a[now2];
    					now2--;
    					continue;
    				}
    			} else{
    				if(tmp1 > tmp4) {
    					ans2 += tmp1;
    					last1 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans2 += tmp4;
    					last2 = a[now2];
    					now2--;
    					continue;
    				}
    			}
    		} else{
    			if(tmp3 > tmp4) {
    				if(tmp2 > tmp3) {
    					ans2 += tmp2;
    					last2 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans2 += tmp3;
    					last1 = a[now2];
    					now2--;
    					continue;
    				}
    			} else{
    				if(tmp2 > tmp4) {
    					ans2 += tmp2;
    					last2 = a[now1];
    					now1++;
    					continue;
    				} else{
    					ans2 += tmp4;
    					last2 = a[now2];
    					now2--;
    					continue;
    				}
    			}
    		}
    	}
    	printf("%lld\n", std::max(ans1, ans2));
    	return 0;
    } 