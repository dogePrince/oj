#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char english[50];
    char other[50];
} Trans;

char unfound[3] = "eh";

int compare(const void *A, const void *B) {
    Trans *p1 = (Trans*)A;
    Trans *p2 = (Trans*)B;
    return strcmp(p1->other, p2->other);
}

char* binarySearch(Trans trans[], int start, int end, char dest[]) {
    int mid = start + (end - start) / 2;
    int compare_result = strcmp(trans[mid].other, dest);
    if (start <= end) {
        if (compare_result < 0) {
            return binarySearch(trans, mid+1, end, dest);
        }
        else if (compare_result > 0) {
            return binarySearch(trans, start, mid-1, dest);
        }
        else {
            return trans[mid].english;
        }
    }
    else {
        return unfound;
    }
}

int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d", &n);
    Trans *trans = (Trans*)malloc(sizeof(Trans)*n);
    for (int i = 0; i < n; i++) {
        scanf("%s %s", trans[i].english, trans[i].other);
    }
    qsort(trans, n, sizeof(Trans), compare);

    scanf("%d", &m);
    char buf[50];
    for (int i = 0; i < m; i++) {
        scanf("%s", buf);
        printf("%s\n", binarySearch(trans, 0, n-1, buf));
    }
    return 0;
}
