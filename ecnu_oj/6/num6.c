#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int is_edge(int a, int b, int n){
    int dis = abs(a - b);
    if (dis == n-1 || dis == 1) {
        return 1;
    }
    else{
        return 0;
    }
}

int edge_count(int a, int b, int c, int n){
    return is_edge(a, b, n) + is_edge(a, c, n) + is_edge(c, b, n);
}

int main(){
    int k;
    int n;
    int a, b, c;

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &n);
        scanf("%d %d %d", &a, &b, &c);
        if (edge_count(a, b, c, n) == 2 || n % 2 == 0) {
            printf("TAK\n");
        }else{
            printf("NIE\n");
        }
        for (int j = 1; j < n - 2; j++) {
            scanf("%d %d %d", &a, &b, &c);
        }
    }
}
