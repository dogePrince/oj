#include<stdio.h>
#include<string.h>

char flag[120];
int value[120];

int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d %d", &n, &m);
    memset(flag, 1, sizeof(flag));
    int index;
    for (int i = 0; i < m; i++) {
        scanf("%d", &index);
        flag[index] = 0;
    }
    value[n] = 1;
    value[n+1] = 0;
    value[n+2] = 0;
    while (n-->=0){
        if (flag[n]) {
            value[n] = value[n+1] + value[n+2] + value[n+3];
        }
        else{
            value[n] = 0;
        }
    }
    printf("%d\n", value[0]);
    return 0;
}
