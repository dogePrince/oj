#include <stdio.h>

long long FractionSum(int aaaabbbb, int ccccdddd) {
    long long z1, m1, z2, m2, tmp;
    z1 = aaaabbbb / 10000;
    m1 = aaaabbbb % 10000;
    z2 = ccccdddd / 10000;
    m2 = ccccdddd % 10000;
    z1 = z1 * m2 + z2 * m1;
    m1 = m1 * m2;
    z2 = z1;
    m2 = m1;
    while ((tmp = z2 % m2)) {
        z2 = m2;
        m2 = tmp;
    }
    tmp = z1 / m2 * 100000000 + m1 / m2;
    return tmp;
}

int main() {
    int a, b, c, d;
    long long r;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    r = FractionSum(a * 10000 + b, c * 10000 + d);

    printf("%d/%d+%d/%d=%lld/%lld.\n", a, b, c, d,
           r / 100000000, r % 100000000);
    return 0;
}
