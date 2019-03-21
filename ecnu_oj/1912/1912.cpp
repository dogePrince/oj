#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[1005];

int main(int argc, char const *argv[]) {
    int n, len, count, j;
    char cur;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        len = strlen(buf);
        cur = buf[0];
        count = 1;
        for (j = 1; j < len; j++) {
            if (buf[j] != cur) {
                printf("%d%c", count, cur);
                cur = buf[j];
                count = 1;
            }
            else {
                count++;
            }
        }
        printf("%d%c\n", count, cur);
    }
    return 0;
}
