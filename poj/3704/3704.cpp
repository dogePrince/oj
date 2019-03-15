#include<stdio.h>
#include<string.h>
#include<stack>

using namespace std;

char buf[1000];
char res[1000];

typedef struct {
    char value;
    int index;
}Record;

void print_result(char buf[]){
    stack<Record> record_stack;
    int length = strlen(buf);

    memset(res, ' ', sizeof(char)*1000);

    for (int i = 0; i < length; i++) {
        if (buf[i] == '(') {
            Record record = {'(', i};
            record_stack.push(record);
        }
        else if (buf[i] == ')') {
            if (!record_stack.empty() && record_stack.top().value == '(') {
                record_stack.pop();
            }
            else {
                Record record = {')', i};
                record_stack.push(record);
            }
        }
    }
    Record record;
    if (!record_stack.empty()) {
        res[record_stack.top().index + 1] = '\0';
        while (!record_stack.empty()) {
            record = record_stack.top();
            if (record.value == '(') {
                res[record.index] = '$';
            }
            else {
                res[record.index] = '?';
            }
            record_stack.pop();
        }
    }
    else {
        res[0] = '\0';
    }

    printf("%s\n", buf);
    printf("%s\n", res);
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        print_result(buf);
    }
    return 0;
}
