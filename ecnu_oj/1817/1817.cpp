#include<stdio.h>
#include<stdlib.h>
#include<vector>

using namespace std;

#define LSIZE 605
int IBIG = 1<<30;

int weight[LSIZE][LSIZE];

int n;

int search (int start, int end){
    vector<int> visited;
    int min[LSIZE] = {IBIG};

    min[start] = 0;
    visited.push_back(start);

    for (int i = 1; i <= n; i++) {
        if (i == start) {
            continue;
        }

        int tmp = IBIG;
        for (vector<int>::iterator it = visited.begin(); it != visited.end(); it++) {
            if (tmp > min[*it] + weight[*it][i]) {
                tmp = min[*it] + weight[*it][i];
            }
        }
        min[i] = tmp;

        for (vector<int>::iterator it = visited.begin(); it != visited.end(); it++) {
            if (min[*it] > min[i] + weight[i][*it]) {
                min[*it] = min[i] + weight[i][*it];
            }
        }
        visited.push_back(i);
    }
    return min[end];
}

int main(int argc, char const *argv[]) {
    int m;
    scanf("%d %d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            weight[i][j] = IBIG;
        }
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        weight[u][v] = w;
    }
    int res = search(1, n);
    if (res >= IBIG) {
        res = -1;
    }
    printf("%d\n", res);
    return 0;
}
