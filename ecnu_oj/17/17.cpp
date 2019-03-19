#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define LSIZE 1005
double rank[LSIZE];

double possibility(double x, double y) {
    return 1.0/(1.0 + pow(10.0, (y-x)/400));
}

double getK(double x) {
    if (x >= 2400) {
        return 16.0;
    }
    if (x < 2100) {
        return 32.0;
    }
    return 24.0;
}

void judge(int status, double &Rx, double &Ry) {
    double Px = possibility(Rx, Ry);
    double Py = possibility(Ry, Rx);
    double Pxy = 1 - Px - Py;
    double Ex = Px + Pxy / 2;
    double Ey = Py + Pxy / 2;
    double Kx = getK(Rx);
    double Ky = getK(Ry);
    double Sx, Sy;
    if (status == 1) {
        Sx = 1.0;
        Sy = 0;
    }
    else {
        Sx = 0.5;
        Sy = 0.5;
    }
    double Rx_new = Rx + Kx * (Sx - Ex);
    double Ry_new = Ry + Ky * (Sy - Ey);
    Rx = Rx_new;
    Ry = Ry_new;
}

int main(int argc, char const *argv[]) {
    for (int i = 0; i < LSIZE; i++) {
        rank[i] = 1500.0;
    }
    int n, status, x, y;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &status);
        if (status == 3) {
            scanf("%d", &x);
            printf("%.6lf\n", rank[x]);
        }
        else {
            scanf("%d %d", &x, &y);
            judge(status, rank[x], rank[y]);
        }
    }
    return 0;
}
