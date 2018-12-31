#include <bits/stdc++.h>
#define maxn 1000010
#define inf 0x3f3f3f3f
#define eps 1e-6
#define ll long long

using namespace std;

double ax, ay, bx, by, cx, cy, dx, dy;
double p, q, r;

inline double dist(double x, double y, double xx, double yy) {
    return sqrt((x - xx) * (x - xx) + (y - yy) * (y - yy));
}

inline double cal(double a, double b, double c, double d) {
    return dist(a, b, ax, ay) / p + dist(c, d, dx, dy) / q + dist(a, b, c, d) / r;
}

inline double in_sanfen(double x, double y) {
    double lx = cx, ly = cy, rx = dx, ry = dy;
    double mlx, mly, mrx, mry;
    while(dist(lx, ly, rx, ry) > eps) {
        mlx = lx + (rx - lx) / 3, mrx = rx - (rx - lx) / 3;
        mly = ly + (ry - ly) / 3, mry = ry - (ry - ly) / 3;
        if(cal(x, y, mlx, mly) < cal(x, y, mrx, mry)) {
            rx = mrx, ry = mry;
        } else lx = mlx, ly = mly;
    }
    return cal(x, y, mlx, mly);
}

inline double out_sanfen() {
    double lx = ax, ly = ay, rx = bx, ry = by;
    double mlx, mly, mrx, mry;
    while(dist(lx, ly, rx, ry) > eps) {
        mlx = lx + (rx - lx) / 3, mrx = rx - (rx - lx) / 3;
        mly = ly + (ry - ly) / 3, mry = ry - (ry - ly) / 3;
        if(in_sanfen(mlx, mly) < in_sanfen(mrx, mry)) {
            rx = mrx, ry = mry;
        } else lx = mlx, ly = mly;
    }
    return in_sanfen(mlx, mly);
}

int main() {
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy, &p, &q, &r);
    printf("%.2f", out_sanfen());
    return 0;
}
