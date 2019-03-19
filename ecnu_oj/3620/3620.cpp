#include<stdio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;

#define LSIZE 1000005

typedef struct {
    int w;
    int a;
    long long cur_sum;
    long long pre_sum;
}Expand;

bool operator < (const Expand A, const Expand B) {
    return A.w < B.w;
}

Expand expand[LSIZE];

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int tw, ta;
    int n1 = 1;
    int n2 = 1;
    Expand *p;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &tw, &ta);
        if (ta < 0) {
            p = &expand[LSIZE - n2];
            n2++;
        }
        else {
            p = &expand[n1];
            n1++;
        }
        p->w = tw;
        p->a = ta;
    }

    expand[0].w = 0;
    expand[0].a = 0;
    expand[0].cur_sum = 0;
    expand[0].pre_sum = 0;

    int max = 0;
    int tmp = 0;
    sort(expand+1, expand+n1);
    for (int i = 1; i < n1; i++) {
        if (expand[i].w == expand[i-1].w) {
            expand[i].cur_sum = expand[i-1].cur_sum + expand[i].a;
            expand[i].pre_sum = expand[i-1].pre_sum;
        }
        else {
            expand[i].pre_sum = expand[i-1].pre_sum + expand[i-1].cur_sum;
            expand[i].cur_sum = expand[i].a;
            tmp = expand[i].w - expand[i].pre_sum;
            if (tmp > max) {
                max = tmp;
            }
        }
    }

    double expand_result = max + expand[n1-1].pre_sum + expand[n1-1].cur_sum;
    int sum_shrink = 0;
    int max_shrink = 0;
    for (int i = 1; i < n2; i++) {
        tmp = expand[LSIZE - i].w + expand[LSIZE - i].a;
        if (tmp > max_shrink) {
            max_shrink = tmp;
        }
        sum_shrink += expand[LSIZE - i].a;
    }
    double judge =  max_shrink - sum_shrink - expand_result;
    if (judge > 0) {
        max += judge;
    }
    printf("%d\n", max);

    return 0;
}
