#include<stdio.h>
#include<math.h>

char buf[100];

void draw(int level) {

    if (level == 0) {
        printf("%s", buf);
    }
    else {
        draw(level-1);
        printf("LD 60\n");
        draw(level-1);
        printf("LD 240\n");
        draw(level-1);
        printf("LD 60\n");
        draw(level-1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    sprintf(buf, "FD 1/%d\n", (int)pow(3.0, n));
    draw(n);
    return 0;
}
