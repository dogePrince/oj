#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double func(double x) {
    double xx = x*x;
    return xx*xx*x - 15*xx*xx + 85*xx*x - 225*xx + 274*x - 121;
}

double binarySearch(double (*func)(double), double left, double right) {
    double start = left;
    double end = right;
    double mid;
    double func_value;
    while (end-start > pow(10.0, -7)) {
        mid = start + (end - start) / 2;
        func_value = func(mid);
        if (func_value > 0) {
            start = mid;
        }
        else {
            end = mid;
        }
    }
    return mid;
}

int main(int argc, char const *argv[]) {
    double res = binarySearch(func, 1.5, 2.4);
    printf("%lf\n", res);
    // printf("%lf\n", func(res));
    return 0;
}
