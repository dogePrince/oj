#include<stdio.h>
#include<stdlib.h>

int house[1000];
int n, c;

int cmp(const void *A, const void *B) {
    return *(int*)A - *(int*)B;
}

int check(int distance) {
    int temp = house[0];
    int count = 0;
    for (int i = 1; i < n; i++) {
        if (house[i] - temp >= distance) {
            count++;
            if (count+1 >= c) {
                return 1;
            }
            temp = house[i];
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    scanf("%d %d", &n, &c);
    for (int i = 0; i < n; i++) {
        scanf("%d", house+i);
    }
    qsort(house, n, sizeof(int), cmp);

    int start = 0;
    int end = house[n-1] - house[0];
    int mid;
    int res = 1;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if (check(mid)) {
            res = mid;
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }

    printf("%d\n", res);
    return 0;
}
