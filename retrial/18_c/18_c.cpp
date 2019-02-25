#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* num_set[20];

int base_cmp(char *p1, char *p2){

    int i = 0;
    while (p1[i] == p2[i]) {
        i++;
    }
    if (p1[i] == '\0' || p2[i] == '\0') {
        if (p1[i] == '\0' && p2[i] == '\0') {
            return 0;
        }
        else if (p1[i] == '\0') {
            return base_cmp(p1, p2+i);
        }
        else {
            return base_cmp(p1+i, p2);
        }
    }
    else {
        return p2[i] - p1[i];
    }
}

int d_cmp(const void *a, const void *b){
    char *p1 = *(char**)a;
    char *p2 = *(char**)b;
    return base_cmp(p1, p2);
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d\n", &n);
    int i = 0;
    int j = 0;
    char t;
    char *p = (char*)malloc(sizeof(char)*60);
    while (i < n) {
        t = getchar();
        if (t >= '0' && t <= '9') {
            p[j++] = t;
        }
        else {
            p[j] = '\0';
            num_set[i++] = p;
            p = (char*)malloc(sizeof(char)*60);
            j = 0;
        }
    }
    qsort(num_set, n, sizeof(char*), d_cmp);
    for (int i = 0; i < n; i++) {
        printf("%s ", num_set[i]);
    }
    return 0;
}
