#include<stdio.h>

int main(int argc, char const *argv[]) {
    int A_now = 0;
    int B_now = 0;

    int n, A, B;
    scanf("%d %d %d", &A, &B, &n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", A_now + 1, B_now + 1);
        A_now = (A_now + 1) % A;
        B_now = (B_now + 1) % B;
    }

    return 0;
}
