#include<stdio.h>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 7; i >= 0; i--) {
        if (n&(1<<i)) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    return 0;
}
