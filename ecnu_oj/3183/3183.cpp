#include <stdio.h>
#include <stdlib.h>
#include<algorithm>
#define N 100

using namespace std;
typedef struct {
    int x,y;
    int abs_x;
    int dis;
    int locate;
} Point;

bool operator < (const Point A, const Point B) {
    if (A.dis != B.dis) {
        return A.dis < B.dis;
    }
    if (A.locate != B.locate) {
        return A.locate < B.locate;
    }
    return A.abs_x < B.abs_x;
}

void SortPoints(Point *p, int n)
{
    int x, y;
    for (int i = 0; i < n; i++) {
        x = p[i].x;
        y = p[i].y;
        p[i].abs_x = abs(x);
        p[i].dis = x*x + y*y;
        if (x >= 0 && y >= 0) {
            p[i].locate = 1;
        }
        else if (x < 0 && y >= 0) {
            p[i].locate = 2;
        }
        else if (x <= 0 && y < 0) {
            p[i].locate = 3;
        }
        else {
            p[i].locate = 4;
        }
    }
    sort(p, p+n);
}
/***************************************************************/
int main()
{
    Point a[N];
    int n,i,t,cas;
    scanf("%d", &cas);
    for(t=0; t<cas; t++)
    {
        scanf("%d", &n);
        for (i=0; i<n; i++) scanf("%d%d", &a[i].x, &a[i].y);
        /***** function SortPoints is called here *****/
        SortPoints(a,n);
        /****************************************/
        printf("case #%d:\n",t);
        for (i=0; i<n; i++) printf("(%d,%d)%c",a[i].x,a[i].y,i<n-1?' ':'\n');
    }
    return 0;
}
