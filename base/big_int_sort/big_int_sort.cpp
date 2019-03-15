#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char flag;
    char num[52];
}bInt;

char buf[52];

int compare1(const void *A, const void *B) {
    bInt *p1 = (bInt*)A;
    bInt *p2 = (bInt*)B;
    if (p1->flag != p2->flag) {
        if (p1->flag == 0) {
            return 1; // A is bigger
        }
        return -1;
    }
    int len1 = strlen(p1->num);
    int len2 = strlen(p2->num);
    if (len1 != len2) {
        if (p1->flag == 1) {
            return len2 - len1;
        }
        return len1 - len2;
    }
    for (int i = 0; i < len1; i++) {
        if (p1->num[i] != p2->num[i]) {
            if (p1->flag == 1) {
                return p2->num[i] - p1->num[i];
            }
            return p1->num[i] - p2->num[i];
        }
    }
    return 0;
}

void sort1(){
    bInt nums[500];

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        if (buf[0] == '-') {
            nums[i].flag = 1;
            strcpy(nums[i].num, buf+1);
        }
        else {
            nums[i].flag = 0;
            strcpy(nums[i].num, buf);
        }
    }

    qsort(nums, n, sizeof(bInt), compare1);
    for (int i = 0; i < n; i++) {
        if (nums[i].flag) {
            printf("-");
        }
        printf("%s\n", nums[i].num);
    }
}

int compare2(const void *A, const void *B) {
    bInt *p1 = *(bInt**)A;
    bInt *p2 = *(bInt**)B;
    if (p1->flag != p2->flag) {
        if (p1->flag == 0) {
            return 1; // A is bigger
        }
        return -1;
    }
    int len1 = strlen(p1->num);
    int len2 = strlen(p2->num);
    if (len1 != len2) {
        if (p1->flag == 1) {
            return len2 - len1;
        }
        return len1 - len2;
    }
    for (int i = 0; i < len1; i++) {
        if (p1->num[i] != p2->num[i]) {
            if (p1->flag == 1) {
                return p2->num[i] - p1->num[i];
            }
            return p1->num[i] - p2->num[i];
        }
    }
    return 0;
}

void sort2() {
    bInt *nums[500];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        bInt *p = (bInt*) malloc(sizeof(bInt));
        if (buf[0] == '-') {
            p->flag = 1;
            strcpy(p->num, buf+1);
        }
        else {
            p->flag = 0;
            strcpy(p->num, buf);
        }
        nums[i] = p;
    }
    qsort(nums, n, sizeof(bInt*), compare2);
    for (int i = 0; i < n; i++) {
        if (nums[i]->flag) {
            printf("-");
        }
        printf("%s\n", nums[i]->num);
    }
}

int main(int argc, char const *argv[]) {
    printf("%lu %lu\n", sizeof(bInt*), sizeof(bInt));
    sort2();
    return 0;
}
