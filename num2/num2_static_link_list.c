#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct pNode{
    int coe;
    int exp;
    int next;
}node;

char buf[MAX_SIZE];

node stack[MAX_SIZE];

void Init_stack(){
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        stack[i].next = i + 1;
    }
    stack[MAX_SIZE - 1].next = 0;
}

int Malloc(){
    int p;
    if (stack[0].next == 0) {
        exit(1);
    }
    else{
        p = stack[0].next;
        stack[0].next = stack[p].next;
    }
    return p;
}

void Free(int p){
    // there should add a check to make sure that free p is valid.
    stack[p].next = stack[0].next;
    stack[0].next = p;
}

int create_poly(char A[]){
    int index;
    int i = 0;
    char temp = A[i++];
    int head = Malloc();
    int tail = head;
    stack[head].next = -1;
    while(temp != '\0'){
        int p = Malloc();
        stack[p].next = stack[tail].next;
        stack[tail].next = p;
        tail = p;

        index = 0;
        if (temp == '+' || temp == '-') {
            if (temp == '-') {
                buf[index++] = temp;
            }
            temp = A[i++];
        }
        if (temp == 'x') {
            stack[p].coe = index == 1?-1:1;
        }
        else{
            while (temp >= '0' && temp <= '9') {
                buf[index++] = temp;
                temp = A[i++];
            }
            buf[index] = '\0';
            sscanf(buf, "%d", &(stack[p].coe));
        }

        if (temp != 'x') {  // if x not exist, exp == 0
            stack[p].exp = 0;
        }
        else{
            temp = A[i++];
            if (temp != '^') {
                stack[p].exp = 1;
            }
            else{
                temp = A[i++];
                index = 0;
                if (temp == '+' || temp == '-') {
                    if (temp == '-') {
                        buf[index++] = temp;
                    }
                    temp = A[i++];
                }
                while (temp >= '0' && temp <= '9') {
                    buf[index++] = temp;
                    temp = A[i++];
                }
                buf[index] = '\0';
                sscanf(buf, "%d", &(stack[p].exp));
            }
        }
    }
    return head;
}

void insert(int head, int coe, int exp){
    int p = head;
    while (stack[p].next != -1 && stack[stack[p].next].exp > exp) {
        p = stack[p].next;
    }
    if (stack[p].next != -1 && stack[stack[p].next].exp == exp) {
        stack[stack[p].next].coe += coe;
    }
    else{
        int q = Malloc();
        stack[q].coe = coe;
        stack[q].exp = exp;
        stack[q].next = stack[p].next;
        stack[p].next = q;
    }
}

int time(int A, int B){
    int C = Malloc();
    stack[C].next = -1;

    for (int p1 = A; stack[p1].next != -1; p1 = stack[p1].next) {
        for (int p2 = B; stack[p2].next != -1; p2 = stack[p2].next) {
            insert(C, stack[stack[p1].next].coe * stack[stack[p2].next].coe, stack[stack[p1].next].exp + stack[stack[p2].next].exp);
        }
    }
    return C;
}

void print(int A){
    int p = A;
    while (stack[p].next != -1) {
        if (stack[stack[p].next].coe != 0) {
            printf("%d ", stack[stack[p].next].coe);
        }
        p = stack[p].next;
    }
    printf("\n");
}

int main(){
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];
    while ((scanf("%s %s",s1,s2))!=EOF){
        Init_stack();
        int A = create_poly(s1);
        int B = create_poly(s2);
        print(time(A, B));
    }
}
