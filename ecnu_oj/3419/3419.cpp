#include<stdio.h>
#include<stdlib.h>

int res[10];

int to_flower(int i) {
    int sum = 0;
    while (i != 0) {
        sum += res[i%10];
        i /= 10;
    }
    return sum;
}

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 10; i++) {
        res[i] = i*i*i*i;
    }
    for (int i = 0; i < 10000; i++) {
        if (i == to_flower(i)) {
            printf("%d\n", i);
        }
    }
    return 0;
}
