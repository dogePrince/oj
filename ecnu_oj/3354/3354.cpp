#include<stdio.h>
#include<stdlib.h>

bool win[100005] = {false};
int k, kk;

int n, m;

int main(int argc, char const *argv[]) {
    for (int i = 1; i < 100005; i++) {
        k = 1;
        kk = 1;
        while (kk <= i) {
            if (win[i-kk] == false) {
                win[i] = true;
                break;
            }
            k++;
            kk = k * k;
        }
    }

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        if (win[m]) {
            printf("JDG will get takeaways!\n");
        }
        else {
            printf("LJJ will get takeaways!\n");
        }
    }
    return 0;
}
