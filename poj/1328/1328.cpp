#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<algorithm>

using namespace std;

int n, r;

typedef struct {
    double left;
    double right;
} Range;

Range range[1000];

bool operator < (const Range &a, const Range &b) {
    return a.left < b.left;
}

int Solve() {
    int i = 0;
    int right = range[0].right;
    int count = 1;

    for (int i = 1; i < n; i++) {
        if (range[i].left < right) {
            right = range[i].right < right ? range[i].right : right;
        }
        else {
            count++;
            right = range[i].right;
        }
    }
    return count;
}

int main(int argc, char const *argv[]) {
    scanf("%d %d", &n, &r);

    int x, y;
    bool flag;
    int count = 1;
    while (n != 0 && r != 0) {
        flag = true;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            if (flag) {
                if (y <= r) {
                    double rr = sqrt((double)(r * r - y * y));
                    range[i].left = x - rr;
                    range[i].right = x + rr;
                }
                else {
                    flag = false;
                }
            }
        }

        sort(range, range + n);
        if (flag) {
            printf("Case%d: %d\n", count, Solve());
        }
        else {
            printf("Case%d: -1\n", count);
        }

        count++;
        scanf("%d %d", &n, &r);
    }
    return 0;
}
