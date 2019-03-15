#include<stdio.h>
#include<stack>

using namespace std;

void hano(char start, char mid, char end, int n){
    if (n == 1) {
        printf("%c %c\n", start, end);
    }
    else {
        hano(start, end, mid, n-1);
        hano(start, mid, end, 1);
        hano(mid, start, end, n-1);
    }
}

typedef struct {
    char start;
    char mid;
    char end;
    int num;
}HanoNode;

void hano_by_stack(char start, char mid, char end, int n) {
    HanoNode HN = {start, mid, end, n};
    stack<HanoNode> hano_stack;
    hano_stack.push(HN);
    while (!hano_stack.empty()) {
        HN = hano_stack.top();
        hano_stack.pop();
        if (HN.num == 1) {
            printf("%c %c\n", HN.start, HN.end);
        }
        else {
            HanoNode HN_step1 = {HN.start, HN.end, HN.mid, HN.num-1};
            HanoNode HN_step2 = {HN.start, HN.mid, HN.end, 1};
            HanoNode HN_step3 = {HN.mid, HN.start, HN.end, HN.num-1};
            hano_stack.push(HN_step3);
            hano_stack.push(HN_step2);
            hano_stack.push(HN_step1);
        }
    }
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    // hano('A', 'B', 'C', n);
    hano_by_stack('A', 'B', 'C', n);
    return 0;
}
