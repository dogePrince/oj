#include<stdio.h>
#include<math.h>

const char *yes = "yes";
const char *no = "no";

int flag = 0;

void check24(double *a, int n) {
    if (n == 1) {
        if (fabs(fabs(a[0])-24) < 0.000001) {
            flag = 1;
        }
    }
    else {
        double b[4];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }
                int count = 0;
                for (int k = 0; k < n; k++) {
                    if (k!=i && k!=j) {
                        b[count] = a[k];
                        count++;
                    }
                }
                b[n-2] = a[i]+a[j];
                check24(b, n-1);
                b[n-2] = a[i]-a[j];
                check24(b, n-1);
                b[n-2] = a[i]*a[j];
                check24(b, n-1);
                b[n-2] = a[i]/a[j];
                check24(b, n-1);
            }
        }

    }
}

int main(int argc, char const *argv[]) {
    double a[4];

    scanf("%lf%lf%lf%lf", a, a+1, a+2, a+3);
    while ((a[0]+a[1]+a[2]+a[3]) != 0) {
        flag = 0;
        check24(a, 4);
        if (flag) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
        scanf("%lf%lf%lf%lf", a, a+1, a+2, a+3);
    }
    return 0;
}
