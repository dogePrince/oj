#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

int n, k;
int R[1000], C[1000];
double Y[1000];

int check(double v) {
    for (int i = 0; i < n; i++) {
        Y[i] = R[i] - v * C[i];
    }
    double sum = 0;
    sort(Y, Y + n);
    for (int i = k; i < n; i++) {
        sum += Y[i];
    }
    if (sum >= 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    scanf("%d %d", &n, &k);
    while (n != 0 && k != 0) {
        for (int i = 0; i < n; i++) {
            scanf("%d", R+i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", C+i);
        }

        double start = 0;
        double end = 1;
        double mid;
        while (end - start > 1e-4) {
            mid = (end + start) / 2;
            if (check(mid)) {
                start = mid;
            }
            else {
                end = mid;
            }
        }
        printf("%.0lf\n", mid*100);

        scanf("%d %d", &n, &k);
    }
    return 0;
}
