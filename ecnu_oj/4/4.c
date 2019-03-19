#include<stdio.h>
#include<stdlib.h>

#define N 10
#define TOP 3

int top[TOP];

int main(){
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int count;
        scanf("%d", &count);
        int temp;

        for (int j = 0; j < TOP; j++) {
            scanf("%d", top+j);
        }
        for (int j = 1; j < TOP; j++) {
            if (top[j] < top[j-1]) {
                int k = j;
                temp = top[j];
                while (temp < top[k-1] && k > 0){
                    top[k] = top[k-1];
                    k--;
                }
                top[k] = temp;
            }
        }
        for (int j = TOP; j < N; j++) {
            scanf("%d", &temp);
            if (temp > top[0]) {
                int k = 1;
                while (k < TOP && temp > top[k]) {
                    top[k-1] = top[k];
                    k++;
                }
                top[--k] = temp;
            }
        }
        printf("%d %d\n", count, top[0]);
    }
}
