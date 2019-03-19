#include<stdlib.h>
#include<stdio.h>

int time[100];
int stack[100];

unsigned long long sub(int n, int i){
    unsigned long long sum = 0;
    unsigned long long sr;
    int k = i;
    stack[0] = -2;
    while (stack[0] == -2) {
        for (int j=i-k; j < i; j++) {
            stack[j+1] = stack[j]+2;
        }
        sr = 1;
        for (int j = 1; j <= i; j++) {
            sr *= time[stack[j]];
        }
        sum += sr;
        stack[i]++;
        k = 0;
        while (stack[i-k] > n-1-k*2 && i-k > 0) {
            stack[i-(++k)]++;
        }
    }
    return sum;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        time[i] = (i+1)*(i+1);
    }
    unsigned long long sum = 0;
    for (int i = 1; i <= (n+1)/2; i++) {
        sum += sub(n, i);
    }
    printf("%llu", sum);
    return 0;
}
