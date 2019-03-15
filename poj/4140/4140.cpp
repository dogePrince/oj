#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double precious;

double myfunc(double x){
    return x*x*x - 5*x*x + 10*x -80;
}

double binarySearch(double start, double end, double (*func)(double)) {
    double mid = start + (end - start) / 2.0;
    double mid_value = func(mid);
    if (fabs(mid_value) < precious) {
        return mid;
    }
    else {
        if (mid_value < 0) {
            return binarySearch(mid, end, func);
        }
        else {
            return binarySearch(start, mid, func);
        }
    }
}


int main(int argc, char const *argv[]) {
    precious = pow(10.0, -10);
    double result = binarySearch(0, 10, myfunc);
    printf("%.9lf\n", result);
    return 0;
}
