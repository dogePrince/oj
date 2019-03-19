#include<stdio.h>
#include<stdlib.h>

int T;
int n;
int sum, temp;

int main(int argc, char const *argv[]) {
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        scanf("%d", &n);
        sum = 0;
        for (size_t i = 0; i < n; i++) {
            scanf("%d", &temp);
            sum += temp;
        }
        sum = sum << (n-1);
        printf("%d\n", sum);
    }
    return 0;
}
