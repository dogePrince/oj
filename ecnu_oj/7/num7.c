#include<stdio.h>

#define BALL 13
#define FLOOR 1050
int A[BALL][FLOOR] = {0};
int B[BALL][FLOOR];
int LEN[BALL];

void init(){
    for (int i = 1; i < BALL; i++) {
        int summary = 1;
        A[i][0] = 1;
        int j = 0;
        B[i-1][0] = 0;
        B[i-1][1] = 1;
        while (summary < FLOOR) {
            A[i][j+1] = A[i-1][j]+A[i][j];
            j++;
            summary += A[i][j];
            B[i-1][j+1] = summary;
        }
        LEN[i-1] = j+2;
    }
}

int search(int n, int *li, int i, int j){
    if (i == j) return i;
    int mid = (i + j)/2;
    if (li[mid-1] < n && n <= li[mid])
        return mid;
    else if (n < li[mid])
        j = mid - 1;
    else
        i = mid + 1;
    return search(n, li, i, j);
}

int main(int argc, char const *argv[]) {
    int t;
    scanf("%d", &t);
    init();

    int c, b, n;
    for (int i = 0; i < t; i++) {
        scanf("%d%d%d", &c, &b, &n);
        if (b >= BALL) {
            b = BALL-1;
        }
        b--;
        if (b == 0) {
            printf("%d %d\n", c, n);
            continue;
        }
        int r = search(n, B[b], 0, LEN[b]);
        printf("%d %d\n", c, r);
    }
    return 0;
}
