#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    if (n == 0) {
        printf("infiniteee\n");
        return 0;
    }
    n = n%11;
    if (n == 0 || n == 10) {
        printf("ultmaster\n");
    }
    else {
        printf("infiniteee\n");
    }
    return 0;
}
