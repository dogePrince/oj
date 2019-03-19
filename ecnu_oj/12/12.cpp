#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack>

#define LSIZE 1005
using namespace std;

bool map[LSIZE][LSIZE];
bool change[LSIZE];
int n;

bool check(bool status) {
    change[0] = status;
    for (int i = 1; i < n; i++) {
        change[i] = (map[0][i] == status);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(map[i][j] ^ change[i] ^ change[j])) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    int K;
    scanf("%d", &K);

    int m, c1, c2;
    bool flag;
    for (int i = 0; i < K; i++) {
        memset(map, false, sizeof(map));
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &c1, &c2);
            c1 -= 1;
            c2 -= 1;
            map[c1][c2] = true;
            map[c2][c1] = true;
        }
        for (int i = 0; i < n; i++) {
            map[i][i] = true;
        }
        if (check(false) || check(true)) {
            printf("Case %d: YES\n", i+1);
            continue;
        }
        printf("Case %d: NO\n", i+1);
    }
    return 0;
}
