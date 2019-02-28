#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int a[21];

int d_cmp(const void *a, const void *b) {
    int *p1 = (int*)a;
    int *p2 = (int*)b;

    int k = abs(*p2) - abs(*p1);

    if (k == 0) {
        return *p1 - *p2;
    }
    else {
        return k;
    }
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, n, sizeof(int), d_cmp);
    for (int i = 0; i < n-1; i++) {
        printf("%d,", a[i]);
    }
    printf("%d", a[n-1]);
    return 0;
}
