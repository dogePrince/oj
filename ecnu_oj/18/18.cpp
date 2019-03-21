#include<stdio.h>
#include<stdlib.h>

typedef unsigned long long LL;
struct Candy {
    LL p;
    LL a;
    LL v;
};

LL check(LL &gold, Candy A) {
    if (gold < A.p) {
        return 0;
    }
    LL res = (gold - A.p)/A.v + 1;
    gold -= res * A.v;
    return res;
}

int main(int argc, char const *argv[]) {
    LL gold;
    Candy A, B;
    Candy H, L;
    while(scanf("%llu%llu%llu%llu%llu", &gold, &A.p, &A.a, &B.p, &B.a) != EOF) {
        A.v = A.p-A.a;
        B.v = B.p-B.a;
        if (A.v < B.v) {
            H = A;
            L = B;
        }
        else {
            H = B;
            L = A;
        }
        LL count = 0;
        count += check(gold, H);
        count += check(gold, L);
        printf("%llu\n", count);
    }
    return 0;
}
