#include<stdio.h>
#include<string.h>

typedef union{
    double d;
    unsigned long long int ull;
}U;

char tochar(unsigned long long int num){
    if (num<10) {
        return (char)('0'+num);
    }
    else {
        return (char)('A'+num-10);
    }
}

char buf[16];

int main(int argc, char const *argv[]) {
    /* code */
    U u;
    scanf("%lf", &u.d);
    unsigned long long int t = u.ull;
    for (int i = 0; i < 16; i++) {
        buf[15-i] = tochar(t%16);
        t /= 16;
    }
    for (int i = 0; i < 7; i++) {
        printf("%c%c-", buf[i*2], buf[i*2+1]);
    }
    printf("%c%c", buf[14], buf[15]);
    return 0;
}
