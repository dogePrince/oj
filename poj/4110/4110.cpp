#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int value;
    int weight;
    double average;
}Bag;

Bag bag[100];
int n, max;

int cmp(const void*A, const void*B) {
    Bag *val1 = (Bag*)A;
    Bag *val2 = (Bag*)B;

    if (val1->average < val2->average) {
        return 1;
    }
    else if (val1->average > val2->average) {
        return -1;
    }
    else {
        return 0;
    }
}

int main(int argc, char const *argv[]) {
    scanf("%d %d", &n, &max);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &bag[i].value, &bag[i].weight);
        bag[i].average = 1.0 * bag[i].value / bag[i].weight;
    }

    qsort(bag, n, sizeof(Bag), cmp);

    double value_now = 0;
    int weight_now = 0;
    for (int i = 0; i < n; i++) {
        if (weight_now + bag[i].weight > max) {
            value_now += (max - weight_now) * bag[i].average;
            break;
        }
        weight_now += bag[i].weight;
        value_now += bag[i].value;
    }

    printf("%.1lf\n", value_now);
    return 0;
}
