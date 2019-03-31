#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    int n;
    int W, w, s, d, o;
    int c;
    scanf("%d\n", &n);
    for (int i = 0; i < n; i++) {
        printf("case #%d:\n", i);
        W = 0;
        w = 0;
        s = 0;
        d = 0;
        o = 0;
        c = getchar();
        while (c != '\n') {
            if (c >= 'A' && c <= 'Z') W++;
            else if (c >= 'a' && c <= 'z') w++;
            else if (c == ' ') s++;
            else if (c >= '0' && c <= '9') d++;
            else o++;
            c = getchar();
        }
        printf("%d %d %d %d %d\n", W, w, s, d, o);
    }
    return 0;
}
