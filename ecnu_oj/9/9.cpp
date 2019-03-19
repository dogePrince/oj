#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[]) {
    int n, m;
    int count = 1;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            printf("%d ", count++);
        }
        printf("%d\n", count++);
    }
    return 0;
}
