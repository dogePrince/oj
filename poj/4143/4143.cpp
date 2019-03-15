#include<stdio.h>
#include<stdlib.h>

int num[1000];
int n, T, mid;

int binarySearch (int val, int left, int right) {
    int start = left;
    int end = right-1;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if (val + num[mid] == T) {
            return 0;
        }
        else if(val + num[mid] < T) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    if (mid == start){
        return 1;
    }
    return 2;
}

int cmp(const void *A, const void *B) {
    return *(int*)A - *(int*)B;
}

int main(int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", num+i);
    }
    scanf("%d", &T);

    qsort(num, n, sizeof(int), cmp);

    int last = n;
    for (int i = 0; i < last; i++) {
        int status = binarySearch(num[i], i+1, last);
        if (status == 0) {
            printf("%d %d\n", num[i], T-num[i]);
            return 0;
        }
        else if (status == 1) {
            last = mid;
        }
        else {
            last = mid + 1;
        }
    }

    printf("nil\n");
    return 0;
}
