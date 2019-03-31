#include <stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void *A, const void *B) {
    char *p1 = (char*)A;
    char *p2 = (char*)B;
    if (p1[0] != p2[0]) {
        return p1[0] - p2[0];
    }
    return strcmp(p2, p1);
}

void sort(char (*p)[81], int n) {
    qsort(p, n, sizeof(char)*81, cmp);
}

int main() {
    char s[100][81];
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%s", s[i]);
    sort(s, n);
    for (i = 0; i < n; i++) printf("%s\n", s[i]);
    return 0;
}
