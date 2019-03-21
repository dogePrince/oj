#include <stdio.h>
#include <string.h>

char *Filter(char *s, char *x)
{
    char tmp[81];
    char *ps = s;
    char *pt = tmp;
    int s_len = strlen(s);
    int x_len = strlen(x);
    char *s_tail = s + s_len;
    char *v;
    while (ps < s_tail) {
        v = strstr(ps, x);
        if (v == NULL) {
            strcpy(pt, ps);
            pt += s + s_len - ps;
            break;
        }
        int i;
        int nn = v - ps;
        for (i = 0; i < nn; i++) {
            pt[i] = ps[i];
        }
        pt += nn;
        ps += nn + x_len;
    }
    *pt = '\0';
    strcpy(s, tmp);
    return s;
}

int main() {
    char s[81], x[81];
    scanf("%s%s", s, x);
    printf("%s\n", Filter(s, x));
    return 0;
}
