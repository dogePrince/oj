#include<stdio.h>
#include<stdlib.h>

bool check(int l, int r, int n) {
    int start = 1;
    int end = n;
    int mid;
    while (true) {
        if (start == l && r == mid) {
            return true;
        }
        if (start <= l && r <= mid) {
            end = mid;
        }
        else if (mid + 1 <= l && r <= end) {
            start = mid + 1;
        }
        else {
            return false;
        }
    }
}

int main(int argc, char const *argv[]) {
    int n, l, r;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &l, &n);
        printf("%d\n", check(l, r, n));
    }
    return 0;
}
