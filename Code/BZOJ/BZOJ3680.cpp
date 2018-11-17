#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 100010;
const int inf = 0x7f7f7f7f;

int n;
int x[maxn], y[maxn], w[maxn];
double ansx, ansy, dis;

inline double Rand() { return (double)rand() / RAND_MAX; }

inline double cal(double nowx, double nowy) {
	double ans = 0;
	for(register int i = 1; i <= n; ++i) {
		double dx = x[i] - nowx, dy = y[i] - nowy;
		ans += sqrt(dx * dx + dy * dy) * w[i];
	}
	if(ans < dis) dis = ans, ansx = nowx, ansy = nowy;
	return ans;
}

inline void SimulateAnneal() {
	double T = 100000;
	double nowx = ansx, nowy = ansy;
	while(T > 0.001) {
		double dx = nowx + T * (2 * Rand() - 1);
		double dy = nowy + T * (2 * Rand() - 1);
		double delta = cal(dx, dy) - cal(nowx, nowy);
		if(exp(-delta / T) > Rand()) nowx = dx, nowy = dy;
		T *= 0.98;
	}
	for(register int i = 1; i <= 10000; ++i) {
		double dx = ansx + T * (2 * Rand() - 1);
		double dy = ansy + T * (2 * Rand() - 1);
		cal(dx, dy);
	}
}

int main() {
	srand(time(0));
	scanf("%d", &n);
	for(register int i = 1; i <= n; ++i) {
		scanf("%d %d %d", &x[i], &y[i], &w[i]);
		ansx += x[i], ansy += y[i];
	}
	ansx /= n, ansy /= n, dis = cal(ansx, ansy);
	SimulateAnneal();
	printf("%.3lf %.3lf", ansx, ansy);
	return 0;
}