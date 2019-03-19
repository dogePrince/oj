#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int dir;  // 0 means face to center
    char *name;
}Hero;

char buf[20];  // store input data

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    Hero heros[n];
    // Hero *heros = (Hero *)malloc(sizeof(Hero)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d %s", &heros[i].dir, buf);
        heros[i].name = (char *)malloc(sizeof(char)*(strlen(buf)+1));
        strcpy(heros[i].name, buf);
    }

    int index = 0;
    int dir, step;
    int abs;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &dir, &step);
        abs = heros[index].dir==dir?-1:1;
        index += step * abs;
        index %= n;
        if (index < 0) {
            index += n;
        }
    }

    printf("%s\n", heros[index].name);
}
