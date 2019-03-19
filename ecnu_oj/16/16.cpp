#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define LSIZE 1000005

int count[LSIZE];
int step[LSIZE];

bool isPrime(int num) {
    int k = (int)sqrt(num * 1.0);
    int i;

    for (i = 2; i <= k; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int value(long long k, int n) {
    if (step[n] <= k) {
        return 1;
    }
    int index = n;
    while (k > 0) {
        index = count[index];
        k--;
    }
    return index;
}

int main(int argc, char const *argv[]) {
    count[1] = 1;
    step[1] = 0;
    count[2] = 1;
    step[2] = 1;
    for (int i = 3; i < LSIZE; i++) {
        if (isPrime(i)) {
            count[i] = count[i-1] + 1;
            step[i] = step[count[i]] + 1;
        }
        else {
            count[i] = count[i-1];
            step[i] = step[i-1];
        }
    }
    long long k;
    int n;
    while (scanf("%lld %d", &k, &n) != EOF) {
        printf("%d\n", value(k, n));
    }
    return 0;
}
