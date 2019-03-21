#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    int n, cur, max, min;
    while (scanf("%d", &n) != EOF) {
        max = 0, min = 40;
        for (int i = 0; i < n; i++) {
            scanf("%d", &cur);
            if (cur > max ) {
                max = cur;
            }
            if (cur < min) {
                min = cur;
            }
        }
        if (min >= 10 && max <= 30 && max - min <= 3) {
            printf("Is SBT\n");
            continue;
        }
        printf("Is not SBT\n");
    }
    return 0;
}
