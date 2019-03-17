#include<stdio.h>
#include<stdlib.h>

int num[100][100];
int res[100][100];

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", &num[i][j]);
        }
    }

    int temp;
    res[0][0] = num[0][0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) {
                res[i][j] = num[i][j] + res[i-1][j];
            }
            else if (j == i) {
                res[i][j] = num[i][j] + res[i-1][j-1];
            }
            else {
                temp = res[i-1][j] > res[i-1][j-1] ? res[i-1][j] : res[i-1][j-1];
                res[i][j] = num[i][j] + temp;
            }
        }
    }

    temp = 0;
    for (int i = 0; i < n; i++) {
        if (res[n-1][i] > temp) {
            temp = res[n-1][i];
        }
    }
    printf("%d\n", temp);

    return 0;
}
