#include<stdio.h>
#include<stdlib.h>
#include<string.h>

bool map[240][240] = {false};
char move[120];

struct Point {
    int x;
    int y;
};

Point direction[4] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
Point routine[120] = {{0, 0}};

Point operator + (Point A, Point B) {
    Point C;
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    return C;
}

Point operator - (Point A, Point B) {
    Point C;
    C.x = A.x - B.x;
    C.y = A.y - B.y;
    return C;
}

int valid(int a, int b) {
    if (b == 0) {
        if (a == 0) {
            return 3;
        }
        return 0;
    }
    if (a == 0) {
        return 2;
    }
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
        return 1;
    }
    return 0;
}

int operator % (Point A, Point B) {
    int s1, s2;
    s1 = valid(A.x, B.x);
    s2 = valid(A.y, B.y);
    if ((s1 == 2 || s1 == 3) && (s2 == 2 || s2 == 3)) {
        return 0;
    }
    if (s1 == 0 || s2 == 0 || s1 == 2 || s2 == 2) {
        return 1;
    }
    if (s1 == 1 && s2 == 3) {
        if (A.x % B.x == 0) {
            return 0;
        }
        return 1;
    }
    if (s1 == 3 && s2 == 1) {
        if (A.y % B.y == 0) {
            return 0;
        }
        return 1;
    }
    if (A.x % B.x == 0 && A.y % B.y == 0 && A.x / B.x == A.y / B.y) {
        return 0;
    }
    return 1;
}

bool check(Point Q) {
    int m_len = strlen(move);
    if (routine[m_len].x == 0 && routine[m_len].y == 0) {
        Point C;
        for (size_t i = 0; i < m_len; i++) {
            C = Q - routine[i];
            if (C.x == 0 && C.y == 0) {
                return true;
            }
        }
    }
    else {
        for (size_t i = 0; i < m_len; i++) {
            if ((Q - routine[i]) % routine[m_len] == 0) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    scanf("%s", move);
    char *m = move;
    int i = 0;
    while (*m != '\0') {
        if (*m == 'L') {
            routine[i+1] = routine[i] + direction[0];
        }
        else if (*m == 'R') {
            routine[i+1] = routine[i] + direction[1];
        }
        else if (*m == 'U') {
            routine[i+1] = routine[i] + direction[2];
        }
        else {
            routine[i+1] = routine[i] + direction[3];
        }
        i++;
        m++;
    }
    int n;
    scanf("%d", &n);
    Point T;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &T.x, &T.y);
        if (check(T)) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }
    return 0;
}
