#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[100000];
char x[100], y[100];

int main(int argc, char const *argv[]) {
    char t;
    int ii = 0;
    t = getchar();
    while (t != '\n') {
        buf[ii++] = t;
        t = getchar();
    }
    buf[ii] = '\0';
    scanf("%s %s", x, y);
    char *p = buf;
    char *v;
    char *tail = p + strlen(buf);
    int x_len = strlen(x);
    while (p < tail) {
        v = strstr(p, x);
        if (v != NULL) {
            for (char *i = p; i < v; i++) {
                printf("%c", *i);
            }
            printf("%s", y);
            p = v + x_len;
        }
        else {
            printf("%s", p);
            break;
        }
    }
    return 0;
}
