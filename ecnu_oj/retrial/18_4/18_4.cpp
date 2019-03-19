#include<stdio.h>
#include<stdlib.h>

typedef struct Person {
    struct Person *firstChild;
    struct Person *nextBro;
    int val;
}PersonNode;

void insert(PersonNode* &child1, PersonNode* child2) {
    if (child1 == NULL) {
        child1 = child2;
    }
    else {
        insert(child1->nextBro, child2);
    }
}

int traversal(PersonNode *root) {
    int sum = 1;
    for (PersonNode *p = root->firstChild; p != NULL; p = p->nextBro) {
        sum += traversal(p);
    }
    root->val = sum;
    return sum;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    PersonNode *p = (PersonNode*)malloc(sizeof(PersonNode)*(n+1));
    for (int i = 0; i < n; i++) {
        p[i].firstChild = NULL;
        p[i].nextBro = NULL;
        p[i].val = 0;
    }

    int index;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &index);
        insert(p[index].firstChild, p+i);
    }

    traversal(p);
    for (int i = 1; i <= n; i++) {
        printf("%d ", p[i].val);
    }

    return 0;
}
