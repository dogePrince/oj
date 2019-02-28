#include<stdio.h>
#include<math.h>

int main(int argc, char const *argv[]) {
    int n, m, t;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        t = (int)pow((double)(m-1)*2.0, 0.5);
        t = (int)(((pow((double)t, 2.0)) + (double)t)/2.0) + 1;
        if (t == m) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }
    return 0;
}
