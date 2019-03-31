#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

int n, m;
int lib[100005];

int fun(int val) {
    int start = 0;
    int end = m - 1;
    int mid;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if (lib[mid] == val) {
            return 0;
        }
        else if (lib[mid] < val) {
            start = mid + 1;
        }
        else {
            end = mid - 1;
        }
    }
    if (start == 0 && end == -1) {
        return lib[0] - val;
    }
    if (start == m && end == m - 1) {
        return val - lib[m - 1];
    }
    int res1 = lib[start] - val;
    int res2 = val - lib[end];
    return res1 < res2 ? res1 : res2;
}

int main(int argc, char const *argv[]) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &lib[i]);
    }
    sort(lib, lib+m);
    int q, c;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &c);
        if (m == 0) {
            printf("nil\n");
        }
        else {
            printf("%d\n", fun(c));
        }
    }
    return 0;
}
