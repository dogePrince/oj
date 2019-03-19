#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int a[21];

int d_cmp(const void *a, const void *b) {
    int *p1 = (int*)a;
    int *p2 = (int*)b;

    return *p1 - *p2;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), d_cmp);
    int min = int(((unsigned int)(~0))>>1);
    int temp;
    for (int i = 0; i < n-1; i++) {
        temp = abs(a[i] - a[i+1]);
        if (temp < min) {
            min = temp;
        }
    }
    printf("%d", min);
    return 0;
}
