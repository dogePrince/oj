#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

#define LSIZE 200005

int n;
long long sum, tmp;
int a[LSIZE], b[LSIZE];

bool cmp1(const int v1, const int v2) {
    return v1 < v2;
}

bool cmp2(const int v1, const int v2) {
    return v1 > v2;
}

int main(int argc, char const *argv[]) {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", a+i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", b+i);
        }
        sort(a, a+n, cmp1);
        sort(b, b+n, cmp2);
        sum = 0;
        for (int i = 0; i < n; i++) {
            tmp = (long long)a[i] + b[i];
            sum += tmp * tmp;
        }
        printf("%lld\n", sum);
    }
    return 0;
}
