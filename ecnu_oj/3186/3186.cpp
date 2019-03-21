#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int val[2];
int fla;
int count = 0;

void init() {
    val[0] = 0;
    val[1] = 0;
    fla = 0;
}

int to_int(char *p) {
    if (p[0] == 't') {
        if (p[1] == 'w') return 2;
        if (p[1] == 'h') return 3;
    }
    if (p[0] == 'f') {
        if (p[1] == 'o') return 4;
        if (p[1] == 'i') return 5;
    }
    if (p[0] == 's') {
        if (p[1] == 'i') return 6;
        if (p[1] == 'e') return 7;
    }
    if (p[0] == 'z') return 0;
    if (p[0] == 'o') return 1;
    if (p[0] == 'e') return 8;
    if (p[0] == 'n') return 9;
}

void translate(char *p) {
    if (strcmp(p, "+") == 0) {
        fla += 1;
    }
    else if (strcmp(p, "=") == 0) {
        printf("case #%d:\n%d\n", count, val[0] + val[1]);
        count++;
        init();
    }
    else {
        val[fla] = val[fla] * 10 + to_int(p);
    }
}

int main(int argc, char const *argv[]) {
    char buf[20];
    scanf("%d");
    init();
    while (scanf("%s", buf) != EOF) {
        translate(buf);
    }
    return 0;
}
