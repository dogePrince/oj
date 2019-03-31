#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[100000];
char prefix[3] = "0x";

int to_int(char a) {
    if (a >= '0' && a <= '9') {
        return a - '0';
    }
    if (a >= 'a' && a <= 'f') {
        return a - 'a' + 10;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    scanf("%s", buf);
    char *p = strstr(buf, prefix);
    bool flag = false;
    int i, tmp;
    long long sum;

    while (p != NULL) {
        p += 2;
        if (to_int(p[0]) != -1) {
            i = 0;
            sum = 0;
            while ((tmp = to_int(p[i++])) != -1) {
                sum = sum * 16 + tmp;
            }
            printf("%lld ", sum);
            p += i;
            flag = true;
        }
        p = strstr(p, prefix);
    }
    if (!flag) {
        printf("-1");
    }
    return 0;
}
