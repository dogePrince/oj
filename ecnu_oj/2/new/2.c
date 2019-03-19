#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct pNode{
    int coe;
    int exp;
    struct pNode *next;
}node;

char stack[MAX_SIZE];

node *create_poly(char A[]){
    int index;
    int i = 0;
    int temp = A[i++];
    node *head = (node *)malloc(sizeof(node));
    node *tail = head;
    head->next = NULL;
    while(temp != '\0'){
        node *p = (node *)malloc(sizeof(node));
        p->next = tail->next;
        tail->next = p;
        tail = p;

        index = 0;
        if (temp == '+' || temp == '-') {
            if (temp == '-') {
                stack[index++] = temp;
            }
            temp = A[i++];
        }
        if (temp == 'x') {
            p->coe = index == 1?-1:1;
        }
        else{
            while (temp >= '0' && temp <= '9') {
                stack[index++] = temp;
                temp = A[i++];
            }
            stack[index] = '\0';
            sscanf(stack, "%d", &(p->coe));
        }

        if (temp != 'x') {  // if x not exist, exp == 0
            p->exp = 0;
        }
        else{
            temp = A[i++];
            if (temp != '^') {
                p->exp = 1;
            }
            else{
                temp = A[i++];
                index = 0;
                if (temp == '+' || temp == '-') {
                    if (temp == '-') {
                        stack[index++] = temp;
                    }
                    temp = A[i++];
                }
                while (temp >= '0' && temp <= '9') {
                    stack[index++] = temp;
                    temp = A[i++];
                }
                stack[index] = '\0';
                sscanf(stack, "%d", &(p->exp));
            }
        }
    }
    return head;
}

void insert(node *A, int coe, int exp){
    node *p = A;
    while (p->next != NULL && p->next->exp > exp) {
        p = p->next;
    }
    if (p->next != NULL && p->next->exp == exp) {
        p->next->coe += coe;
    }
    else{
        node *q = (node *)malloc(sizeof(node));
        q->coe = coe;
        q->exp = exp;
        q->next = p->next;
        p->next = q;
    }
}

node *time(node *A, node *B){
    node *C = (node *)malloc(sizeof(node));
    C->next = NULL;

    for (node *p1 = A; p1->next != NULL; p1 = p1->next) {
        for (node *p2 = B; p2->next != NULL; p2 = p2->next) {
            insert(C, p1->next->coe * p2->next->coe, p1->next->exp + p2->next->exp);
        }
    }
    return C;
}

void print(node *A){
    node *p = A;
    while (p->next != NULL) {
        if (p->next->coe != 0) {
            printf("%d ", p->next->coe);
        }
        p = p->next;
    }
    printf("\n");
}

void destroy(node *A) {
    node *p = A;
    node *temp;
    while (p != NULL) {
        temp = p;
        p = p->next;
        free(temp);
    }
}

int main(){
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];
    while ((scanf("%s %s",s1,s2))!=EOF){
        node *A = create_poly(s1);
        node *B = create_poly(s2);
        print(time(A, B));
        destroy(A);
        destroy(B);
    }
}
