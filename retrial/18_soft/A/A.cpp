#include<stdio.h>

int main(int argc, char const *argv[]) {
    int n, m, value;
    int sum = 0;
    int max;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        max = 0;
        for (int j = 0; j < m; j++) {
            scanf("%d", &value);
            if (value > max) {
                max = value;
            }
        }
        sum += max;
    }
    printf("%d", sum);
    return 0;
}
