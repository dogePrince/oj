#include<stdio.h>

int a[50];

void NextPremutation(int n) {
    int i, j, k, temp;
    for (i = n-1; i > 0; i--) {
        if (a[i-1] < a[i]) {
            break;
        }
    }
    if (i > 0) {
        k = i;
        for (j = n-1; j >= i; j--) {
            if (a[j] > a[i-1] && a[j] < a[k]) {
                k = j;
            }
        }
        temp = a[k];
        a[k] = a[i-1];
        a[i-1] = temp;
    }
    j = n-1;
    while (i < j) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }
}

int main(int argc, char const *argv[]) {
    int n;
    int count = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        count *= i + 1;
    }
    for (int i = 0; i < count; i++) {
        NextPremutation(n);
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    return 0;
}
