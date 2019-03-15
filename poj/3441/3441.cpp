#include<stdio.h>
#include<stdlib.h>

int num_set[100][4];
int sum1[10000];
int sum2[10000];
int up_floor;

int cmp(const void *A, const void *B) {
    int *p1 = (int*)A;
    int *p2 = (int*)B;
    return *p1-*p2;
}

int binarySearch(int val, int set[], int length) {
    int mid;
    int start = 0;
    int end = length - 1;
    int temp;
    while (start <= end) {
        mid = start + (end - start) / 2;
        temp = val + set[mid];
        if (temp == 0) {
            up_floor = mid;
            return 1;
        }
        else if (temp < 0) {
            start = mid + 1;
        }
        else {
            up_floor = mid;
            end = mid - 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", *(num_set+i), *(num_set+i)+1, *(num_set+i)+2, *(num_set+i)+3);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum1[i*n+j] = num_set[i][0] + num_set[j][1];
            sum2[i*n+j] = num_set[i][2] + num_set[j][3];
        }
    }
    qsort(sum1, n*n, sizeof(int), cmp);
    qsort(sum2, n*n, sizeof(int), cmp);

    int count = 0;
    up_floor = n*n;
    for (int i = 0; i < n*n; i++) {
        if (binarySearch(sum1[i], sum2, up_floor)) {
            count++;
        }
    }
    printf("%d\n", count);

    return 0;
}
