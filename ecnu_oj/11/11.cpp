#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int count[52] = {0};
char buf[52];

int main(int argc, char const *argv[]) {
    scanf("%s", buf);
    int length = strlen(buf);
    int max;
    count[0] = 1;
    for (int i = 1; i < length; i++) {
        max = 0;
        for (int j = 0; j < i; j++) {
            if (buf[j] < buf[i]) {
                if (max < count[j]) {
                    max = count[j];
                }
            }
        }
        count[i] = max+1;
    }

    max = 0;
    for (size_t i = 0; i < length; i++) {
        if (count[i] > max) {
            max = count[i];
        }
    }
    printf("%d\n", 26-max);

    return 0;
}
