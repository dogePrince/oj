#include<stdio.h>
#include<stdlib.h>

int n;
int num_set[1000];

int check(int val) {
    int start = 0;
    int end = n-1;
    int mid = 0;
    int diff;

    while (start <= end) {
        mid = start + (end - start) / 2;
        diff = num_set[mid] - val;
        if (diff == 0) {
            return num_set[mid];
        }
        else if (diff < 0) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    if (mid == start && mid > 0) {
        int left = val - num_set[mid-1];
        int right = num_set[mid] - val;
        return left < right ? num_set[mid-1] : num_set[mid];
    }
    else if (mid == end && mid < n-1) {
        int left = val - num_set[mid];
        int right = num_set[mid+1] - val;
        return left < right ? num_set[mid] : num_set[mid+1];
    }
    return num_set[mid];
}

int main(int argc, char const *argv[]) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", num_set+i);
    }

    int c;
    scanf("%d", &c);
    int input;
    for (int i = 0; i < c; i++) {
        scanf("%d", &input);
        printf("%d\n", check(input));
    }
    return 0;
}
