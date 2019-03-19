#include<stdio.h>
#include<stdlib.h>

int g_left;
int g_right;

void find(int n) {
    if (n == 1) {
        g_left = 1;
        g_right = 1;
        return;
    }
    find(n >> 1);
    int l_left;
    int l_right;
    if (n % 2) {
        l_left = g_left + g_right;
        l_right = g_right;
    }
    else {
        l_left = g_left;
        l_right = g_left + g_right;
    }
    g_left = l_left;
    g_right = l_right;
}

int main(int argc, char const *argv[]) {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &m);
        find(m);
        printf("Case %d: %d/%d\n", i+1, g_left, g_right);
    }
    return 0;
}
