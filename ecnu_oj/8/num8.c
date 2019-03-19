#include<stdio.h>
#include<string.h>

char buf[1050];

int main(){
    int n;
    scanf("%d", &n);
    unsigned long long i = 1, j = 1;
    unsigned long long k;
    buf[0] = '1';
    buf[1] = '1';
    buf[2] = '\0';
    int len = strlen(buf);
    while (len < n) {
        k = i + j;
        i = j;
        j = k;
        sprintf(buf+len, "%llu", k);
        len = strlen(buf);
    }
    buf[n] = '\0';
    printf("%s", buf);
}
