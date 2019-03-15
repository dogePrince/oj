#include<stdio.h>
#include<stdlib.h>

int res[92][8];
int temp[8];
int count = 0;

void queen(int i){
    if (i == 8) {
        for (int j = 0; j < 8; j++) {
            res[count][j] = temp[j];
        }
        count++;
        return;
    }
    for (int j = 0; j < 8; j++) {
        int k;
        for (k = 0; k < i; k++) {
            if (temp[k] == j || abs(k-i) == abs(temp[k]-j)) {
                break;
            }
        }
        if (k == i) {
            temp[i] = j;
            queen(i+1);
        }
    }
}

int main(int argc, char const *argv[]) {
    queen(0);
    int n, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &k);
        for (int j = 0; j < 8; j++) {
            printf("%d", res[k-1][j]+1);
        }
        printf("\n");
    }
    return 0;
}
