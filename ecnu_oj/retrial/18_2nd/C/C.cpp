#include<stdio.h>
#include<string.h>

int main(){
    int count = 0;
    char c;
    do {
        c = getchar();
        if (c>='0'&&c<='9') {
            count++;
        }
    } while(c!='\n' && c!=EOF);

    printf("%d", count);
    return 0;
}
