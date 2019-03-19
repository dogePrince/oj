#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_SIZE 100

int step[MAX_SIZE * 2];

double min(int num, int precision){
    double min = 2.0;
    double len;

    for (int i = 0; i < num - 1; i++){
        for (int j = i + 1; j < num; j++) {
            double x1 = ((double)step[i*2]) / ((double) precision);
            double y1 = ((double)step[i*2+1]) / ((double) precision);
            double x2 = ((double)step[j*2]) / ((double) precision);
            double y2 = ((double)step[j*2+1]) / ((double) precision);

            len = sqrt(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0));
            if (len < min){
                min = len;
            }
            if (min == 0.0){
                return min;
            }
        }
    }
    return min;
}

double expect(double (*f)(int num, int pre),int p, int precision){
    double sum = 0;
    int i=0;
    while (step[2*p-1]<precision) {
        sum += min(p, precision);

        step[0]++;
        while (step[i]==precision && i != 2*p-1) {
            step[i] = 0;
            step[i+1]++;
        }
    }
    return sum / pow((double) precision, (double) (2*p));
}

int main(){
    double result = expect(min, 2, 100);
    printf("%.10f\n", result);
}
