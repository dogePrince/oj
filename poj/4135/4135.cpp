#include<stdio.h>
#include<stdlib.h>

int num[1000];
int n, m;

int check(int cost) {
    int sum = 0;
    int count = 1;
    for (int i = 0; i < n; i++) {
        sum += num[i];
        if (sum > cost) {
            count++;
            if (count > m) {
                return 0;
            }
            sum = num[i];
        }
    }
    return 1;
}

int main(int argc, char const *argv[]) {
    scanf("%d %d", &n, &m);
    int sum = 0;
    int max = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", num+i);
        sum += num[i];
        if (num[i] > max) {
            max = num[i];
        }
    }

    int start = max;
    int end = sum;
    int mid;
    int res;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if(check(mid)) {
            res = mid;
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    printf("%d\n", res);

    return 0;
}
