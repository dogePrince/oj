#include<stdio.h>
#include<stack>
#include<queue>

using namespace std;

queue<int> num;
queue<char> ope;

stack<int> num_s;
stack<char> ope_s;

int ope_to_num(char c) {
    if (c == '*' || c == '/') {
        return 2;
    }
    if (c == '+' || c == '-') {
        return 1;
    }
    return 0;
}

int ope_cmp(char c1, char c2) {
    if (ope_to_num(c1) >= ope_to_num(c2)) {
        return 1;
    }
    return 0;
}

int calculate(){
    int temp_num;
    char temp_ope;

    num_s.push(num.front());
    num.pop();

    ope_s.push('#');

    temp_ope = ope.front();
    ope.pop();
    temp_num = num.front();
    num.pop();

    while (!ope_s.empty()) {
        if (ope_cmp(ope_s.top(), temp_ope)) {
            if (ope_s.top() == '#') {
                break;
            }
            int num_t2 = num_s.top();
            num_s.pop();
            int num_t1 = num_s.top();
            num_s.pop();

            if (ope_s.top() == '*') {
                num_s.push(num_t1 * num_t2);
            }
            else if (ope_s.top() == '/') {
                num_s.push(num_t1 / num_t2);
            }
            else if (ope_s.top() == '+') {
                num_s.push(num_t1 + num_t2);
            }
            else if (ope_s.top() == '-') {
                num_s.push(num_t1 - num_t2);
            }
            else{
                exit(1);
            }
            ope_s.pop();
        }
        else {
            num_s.push(temp_num);
            ope_s.push(temp_ope);

            temp_ope = ope.front();
            ope.pop();
            temp_num = num.front();
            num.pop();
        }
    }

    return num_s.top();
}

int main() {
    int k = 0;
    int flag = 0;
    char c;
    while ((c = getchar()) != '\n') {
        if ('0' <= c && c <= '9'){
            if (flag) {
                k = k * 10 + c - '0';
            }
            else {
                flag = 1;
                k = c - '0';
            }
        }
        else {
            num.push(k);
            k = 0;
            flag = 0;
            ope.push(c);
        }
    }
    num.push(k);

    ope.push('#');
    int r = calculate();
    printf("%d\n", r);

    return 0;
}
