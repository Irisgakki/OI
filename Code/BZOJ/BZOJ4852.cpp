#include<bits/stdc++.h>
using namespace std;
const int MAXN = 15;
const int MAXM = 1005;
const double VALUE = 1e8;
const int INF = 1e9;
const int D = 50;
const int T = 100;
const double C = 0.99;
int n, m, R, ans, STEP;
int x[MAXN], y[MAXN], r[MAXN], p[MAXM], q[MAXM];
double dist(double px, double py, double qx, double qy) {
	return sqrt((px - qx) * (px - qx) + (py - qy) * (py - qy));
}
int get(int px, int py) {
	double pr = R;
	int i;
	for (i = 1; i <= n; i++)
		pr = min(pr, dist(px, py, x[i], y[i]) - r[i]);
	if (pr < 0) return 0;
	int tot = 0;
	for (i = 1; i <= m; i++)
		tot += dist(px, py, p[i], q[i]) <= pr;
	return tot;
}
void anneal() {
	double tx, px = rand() % (2 * R) - R;
	double ty, py = rand() % (2 * R) - R;
	double t = T;
	int now = get(px, py), tmp = now, step;
	while (t > 1e-2) {
		step = t * STEP / T + 1;
		tx = px + rand() % (2 * step) - step;
		ty = py + rand() % (2 * step) - step;
		tmp = get(tx, ty);
		if (tmp > now || exp(-VALUE * (now - tmp) / t) > (double) (rand() % 32767) / 32767) {
			now = tmp;
			px = tx, py = ty;
		}
		t *= C;
	}
	if (now > ans) ans = now;
}
int main() {
	scanf("%d%d%d",&n,&m,&R); STEP = R;
	int i;
	for (i = 1; i <= n; i++)
		scanf("%d%d%d", &x[i], &y[i], &r[i]);
	for (i = 1; i <= m; i++)
		scanf("%d%d", &p[i], &q[i]);
	ans = 1; srand(4018);
	for (i = 1; i <= D; i++)
		anneal();
	printf("%d\n", ans);
	return 0;
} 