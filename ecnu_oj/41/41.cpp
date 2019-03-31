#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Word {
    char val[20];
    Word *next;
};

void insert(Word *head, char *buf) {
    Word *p = head;
    int cmp_res;
    while (p->next != NULL) {
        cmp_res = strcmp(p->next->val, buf);
        if (cmp_res == 0) {
            return;
        }
        else if (cmp_res > 0) {
            break;
        }
        else {
            p = p->next;
        }
    }
    Word *q = new Word();
    strcpy(q->val, buf);
    q->next = p->next;
    p->next = q;
}

void print (Word *head, char type) {
    Word *p = head;
    while (p->next != NULL) {
        printf("%c:%s\n", type, p->next->val);
        p = p->next;
    }
}

int main(int argc, char const *argv[]) {
    Word *head[26];
    char buf[20];
    for (int i = 0; i < 26; i++) {
        head[i] = new Word();
        head[i]->next = NULL;
    }
    int k;
    while (scanf("%s", buf) != EOF) {
        if (buf[0] >= 'a' && buf[0] <= 'z') {
            buf[0] = buf[0] - 'a' + 'A';
        }
        k = buf[0] - 'A';
        insert(head[k], buf);
    }
    for (int i = 0; i < 26; i++) {
        print(head[i], 'A'+i);
    }
    return 0;
}
