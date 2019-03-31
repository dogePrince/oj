#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Num {
    char flag;
    char val[125];
    int len;
};
Num num[50];

int cmp(const void *A, const void *B) {
    Num *p1 = (Num*)A;
    Num *p2 = (Num*)B;
    Num *temp;

    if (p1->flag != p2->flag) {
        return p1->flag == 1 ? -1 : 1;
    }
    if (p1->flag == 1) {
        temp = p1;
        p1 = p2;
        p2 = temp;
    }
    if (p1->len != p2->len) {
        return p1->len - p2->len;
    }
    return strcmp(p1->val, p2->val);
}

void minus(char *A, char *B) {
    int Alen = strlen(A);
    int Blen = strlen(B);
    int res[125] = {0};

    int i;
    for (i = 1; i <= Blen; i++) {
        res[i] = A[Alen-i] - B[Blen-i];
    }
    for (; i <= Alen; i++) {
        res[i] = A[Alen-i] - '0';
    }
    for (i = 1; i <= Alen; i++) {
        if (res[i] < 0) {
            res[i] += 10;
            res[i+1] -= 1;
        }
    }

    for (i = Alen; i > 0; i--) {
        if (res[i] != 0) {
            break;
        }
    }
    if (i == 0) {
        printf("0");
        return;
    }
    for (int j = i; j > 0; j--) {
        printf("%d", res[j]);
    }
}

void plus(char *A, char *B) {
    int Alen = strlen(A);
    int Blen = strlen(B);
    int res[125] = {0};

    int i;
    for (i = 1; i <= Blen; i++) {
        res[i] = A[Alen-i] + B[Blen-i] - '0' * 2;
    }
    for (; i <= Alen; i++) {
        res[i] = A[Alen-i] - '0';
    }
    res[Alen+1] = 0;
    for (i = 1; i <= Alen; i++) {
        if (res[i] > 9) {
            res[i] -= 10;
            res[i+1] += 1;
        }
    }

    for (i = Alen+1; i > 0; i--) {
        if (res[i] != 0) {
            break;
        }
    }
    if (i == 0) {
        printf("0");
        return;
    }
    for (int j = i; j > 0; j--) {
        printf("%d", res[j]);
    }
}

int main(int argc, char const *argv[]) {
    int n;
    char buf[125];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        if (buf[0] == '-') {
            num[i].flag = 1;
            strcpy(num[i].val, buf+1);
        }
        else {
            num[i].flag = 0;
            strcpy(num[i].val, buf);
        }
        num[i].len = strlen(num[i].val);
    }
    qsort(num, n, sizeof(Num), cmp);
    Num &max = num[n-1];
    Num &min = num[0];
    if (min.flag == 1 && max.flag == 1) {
        minus(min.val, max.val);
    }
    else if (min.flag == 1 && max.flag == 0) {
        if (min.len > max.len) {
            plus(min.val, max.val);
        }
        else {
            plus(max.val, min.val);
        }
    }
    else {
        minus(max.val, min.val);
    }
    return 0;
}
