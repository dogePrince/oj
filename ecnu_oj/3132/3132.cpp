#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int map[6][6];
char visited[6][6];
int routine[25];
int size;

void init() {
    memset(visited, 0, 36);
    size = 0;
}

int visit(int val) {
    int x = val / 10;
    int y = val % 10;
    if (visited[x][y] == 1) {
        return -1;
    }
    visited[x][y] = 1;
    return map[x][y];
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int k = 0; k < n; k++) {
        init();
        for (int i = 1; i <= 5; i++) {
            for (int j = 1; j <= 5; j++) {
                scanf("%d", &map[i][j]);
            }
        }
        int cur = 11, next;
        while (1) {
            next = visit(cur);
            if (next == cur) {
                printf("case #%d:\n", k);
                for (int i = 0; i < size; i++) {
                    printf("%d ", routine[i]);
                }
                printf("%d\n", cur);
                break;
            }
            if (next == -1) {
                printf("case #%d:\n", k);
                printf("-1\n");
                break;
            }
            routine[size++] = next;
            cur = next;
        }
    }
    return 0;
}
