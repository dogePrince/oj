// not the best answer
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char num[25];
char res[25] = {0};
int m;
int len;

void print() {
    bool flag = false;
    for (int i = 0; i < len; i++) {
        if (flag) {
            printf("%d", res[i]);
        }
        else {
            if (res[i] != 0) {
                flag = true;
                printf("%d", res[i]);
            }
        }
    }
    printf("\n");
}

bool fill(int deep, bool lock, bool start, int count) {
    if (deep == len) {
        if (count == m) {
            return true;
        }
        return false;
    }
    if (m - count > len - deep) {
        return false;
    }
    if (lock) {
        if (num[deep] == 0) {
            res[deep] = 0;
            return fill(deep + 1, true, start, count + 1); // string has no prefix with '0'
        }
        if (num[deep] == 1) {
            res[deep] = 1;
            if (fill(deep + 1, true, true, count + 1)) {
                return true;
            }
            res[deep] = 0;
            if (start) {
                return fill(deep + 1, false, start, count + 1);
            }
            else {
                return fill(deep + 1, false, start, count);
            }
        }
        if (num[deep] == 2) {
            res[deep] = 2;
            if (fill(deep + 1, true, true, count)) {
                return true;
            }
            res[deep] = 1;
            if (fill(deep + 1, false, true, count + 1)) {
                return true;
            }
            res[deep] = 0;
            if (start) {
                return fill(deep + 1, false, start, count + 1);
            }
            else {
                return fill(deep + 1, false, start, count);
            }
        }
        res[deep] = num[deep];
        if (fill(deep + 1, true, true, count)) {
            return true;
        }
        res[deep] = num[deep] - 1;
        if (fill(deep + 1, false, true, count)) {
            return true;
        }
        res[deep] = 1;
        if (fill(deep + 1, false, true, count + 1)) {
            return true;
        }
        res[deep] = 0;
        if (start) {
            return fill(deep + 1, false, start, count + 1);
        }
        else {
            return fill(deep + 1, false, start, count);
        }
    }
    else {
        res[deep] = 9;
        if (fill(deep + 1, false, true, count)) {
            return true;
        }
        res[deep] = 1;
        if (fill(deep + 1, false, true, count + 1)) {
            return true;
        }
        res[deep] = 0;
        if (start) {
            return fill(deep + 1, false, start, count + 1);
        }
        else {
            return fill(deep + 1, false, start, count);
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    scanf("%s %d", num, &m);
    len = strlen(num);
    for (int i = 0; i < len; i++) {
        num[i] -= '0';
    }
    fill (0, true, false, 0);
    print();
    return 0;
}
