#include<stdio.h>

int main(int argc, char const *argv[]) {
    int n, temp;
    scanf("%d", &n);
    int max = 1 << 31;
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        if (max < temp) {
            max = temp;
        }
    }
    printf("%d", max);
    return 0;
}
