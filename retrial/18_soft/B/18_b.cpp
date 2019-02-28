#include<stdio.h>

int a[20][20];

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                a[i][j] = 1;
            }
            else {
                a[i][j] = a[i-1][j-1] + a[i-1][j];
            }
            printf("%d", a[i][j]);
            if (j != i) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
