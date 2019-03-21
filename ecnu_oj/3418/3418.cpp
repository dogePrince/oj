#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    char c = 0;
    int count = 0;
    while (c != '\n') {
        c = getchar();
        if (c >= '0' && c <= '9') {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
