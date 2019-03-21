#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define W_LEN 100005
#define LEN 21

char s1[W_LEN][LEN];
char s2[W_LEN][LEN];

char delta = 'a' - 'A';

void to_lowercase(char *ss) {
    for (char *p = ss; *p != '\0'; p++) {
        if (*p >= 'A' && *p <= 'Z') {
            *p = *p + delta;
        }
    }
}

int cmp(const void *A, const void *B) {
    return strcmp((char*)A, (char*)B);
}

int main(int argc, char const *argv[]) {
    int k, ll1, ll2;
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &ll1);
        for (int j = 0; j < ll1; j++) {
            scanf("%s", s1[j]);
            to_lowercase(s1[j]);
        }
        scanf("%d", &ll2);
        for (int j = 0; j < ll2; j++) {
            scanf("%s", s2[j]);
            to_lowercase(s2[j]);
        }
        if (ll1 != ll2) {
            printf("Case %d: NO\n", i);
            continue;
        }
        qsort(s1, ll1, sizeof(char)*LEN, cmp);
        qsort(s2, ll2, sizeof(char)*LEN, cmp);
        int j;
        for (j = 0; j < ll1; j++) {
            if (strcmp(s1[j], s2[j]) != 0) {
                break;
            }
        }
        if (j == ll1) {
            printf("Case %d: YES\n", i);
            continue;
        }
        printf("Case %d: NO\n", i);
    }
    return 0;
}
