#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char light_set[1050];
char weight_set[1050];
char light_set_temp[1050];
char weight_set_temp[1050];
int temp[220];
char all_set[1050];

int main(int argc, char const *argv[]) {
    int n, k;
    scanf("%d %d", &n, &k);

    memset(light_set, 0, n);
    memset(weight_set, 0, n);
    memset(all_set, 1, n);

    int flag = 1;

    int num;
    char operate;
    for (int i = 0; i < k; i++) {
        scanf("%d", &num);
        for (int j = 0; j < num * 2; j++) {
            scanf("%d", &temp[j]);
        }
        operate = getchar();
        while(operate != '=' && operate != '<' && operate != '>') {
            operate = getchar();
        }
        if (operate == '=') {
            for (int j = 0; j < num * 2; j++) {
                all_set[temp[j]] = 0;
            }
        }
        else {
            int *ll;
            int *ww;
            if (operate == '<') {
                ll = temp;
                ww = temp+num;
            }
            else {
                ll = temp+num;
                ww = temp;
            }
            if (flag) {
                flag = 0;
                for (int j = 0; j < num; j++) {
                    light_set[ll[j]] = 1;
                    weight_set[ww[j]] = 1;
                }
            }
            else {
                for (int j = 0; j < num; j++) {
                    light_set_temp[ll[j]] = 1;
                    weight_set_temp[ww[j]] = 1;
                }
                for (int j = 0; j < n; j++) {
                    light_set[j] = light_set[j] & light_set_temp[j];
                    weight_set[j] = weight_set[j] & weight_set_temp[j];
                }
            }
        }
    }

    if (flag) {
        for (int j = 0; j < n; j++) {
            if (all_set[j]) {
                printf("%d", j);
                return 0;
            }
        }
    }
    else {
        for (int j = 0; j < n; j++) {
            light_set[j] = light_set[j] & all_set[j];
            weight_set[j] = weight_set[j] & all_set[j];
        }

        for (int j = 0; j < n; j++) {
            if (light_set[j] || weight_set[j]) {
                printf("%d", j);
                return 0;
            }
        }
    }
    return 0;
}
