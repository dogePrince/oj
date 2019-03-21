#include <stdio.h>
#include<string.h>

#define N 80

void replace(char s[], char x[], char y[]) { //TODO: your function definition
    char tmp[3 * N + 1];
    char *ps = s;
    char *pt = tmp;
    char *v;
    int len_s = strlen(s);
    int len_x = strlen(x);
    int len_y = strlen(y);

    while (ps < s + len_s) {
        v = strstr(ps, x);
        if (v == NULL) {
            int i;
            for (i = 0; ps + i < s + len_s; i++) {
                pt[i] = ps[i];
            }
            pt += i;
            break;
        }
        for (int i = 0; ps + i < v; i++) {
            pt[i] = ps[i];
        }
        pt += v - ps;
        strcpy(pt, y);
        pt += len_y;
        ps = v + len_x;
    }
    *pt = '\0';
    strcpy(s, tmp);
}

int main() {
    char s[3 * N + 1], x[N + 1], y[N + 1];
    scanf("%s%s%s", s, x, y);
    replace(s, x, y);
    printf("%s\n", s);
    return 0;
}
