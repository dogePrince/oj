#include<stdio.h>
#include<stdlib.h>

void set_base_down(unsigned long long base[], unsigned long long down[], unsigned long long pre_sum[], unsigned long long n) {
    for (int i = 0; i < (n+1)/2 + 1; i++) {
        base[i] = (n-i)*4*i+1;
    }

    for (int i = 0; i < (n+1)/2; i++) {
        down[i] = base[i+1]+base[i]+n-2*i-1;
    }

    pre_sum[0] = 0;
    for (int i = 0; i < (n+1)/2 - 1; i++) {
        pre_sum[i+1] = pre_sum[i] + down[i];
    }
}

unsigned long long plus(int i, int n, unsigned long long base[], unsigned long long down[], unsigned long long pre_sum[]) {
    unsigned long long sum = 0;
    int j = 0;
    int r_i = i < (n+1)/2?i:n-i-1;

    sum = pre_sum[r_i];

    if (i < (n+1)/2) {
        sum += (base[i]*2 + n - 1 - 2*i) * (n-2*i)/2;
    }
    else {
        sum += down[r_i]  * (n-2*r_i)/ 2;
    }

    return sum;
}

int main(){
    int n;
    scanf("%d", &n);
    unsigned long long *base = (unsigned long long *)malloc(sizeof(unsigned long long)*((n+1)/2+1));
    unsigned long long *down = (unsigned long long *)malloc(sizeof(unsigned long long)*(n+1)/2);
    unsigned long long *pre_sum = (unsigned long long *)malloc(sizeof(unsigned long long)*(n+1)/2);
    set_base_down(base, down, pre_sum, n);

    for (int i = 0; i < n; i++) {
        fprintf(stdout, "%llu\n", plus(i, n, base, down, pre_sum));
    }

    return 0;
}

// int main(int argc, char *argv[]){
//     int n,i;
//     sscanf(argv[1], "%d", &n);
//     sscanf(argv[2], "%d", &i);
//     unsigned long long *base = (unsigned long long *)malloc(sizeof(unsigned long long)*((n+1)/2+1));
//     unsigned long long *down = (unsigned long long *)malloc(sizeof(unsigned long long)*(n+1)/2);
//     unsigned long long *pre_sum = (unsigned long long *)malloc(sizeof(unsigned long long)*(n+1)/2);
//     set_base_down(base, down, pre_sum, n);
//
//     fprintf(stdout, "%llu\n", plus(i, n, base, down, pre_sum));
//
//     return 0;
// }
