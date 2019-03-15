#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define NSUM 25
double rand_sum = 0;
double gaussrand(double mu, double segma)
{
    double x = 0;
    int i;
    for(i = 0; i < NSUM; i++)
    {
        x += (double)rand() / RAND_MAX;
    }
    x -= NSUM / 2.0;
    x /= sqrt(NSUM / 12.0);
    rand_sum += x;
    return mu + rand_sum*segma;
}

double sum = 0;
double histroy[2] = {0, 0};

double proportion(double error, double kp) {
    return error*kp;
}

double integral(double error, double ki) {
    sum += error;
    return sum*ki;
}

double differential(double error, double kd) {
    histroy[0] = histroy[1];
    histroy[1] = error;
    return (histroy[1] - histroy[0])*kd;
}

typedef struct{
    double now;
    double goal;
    double error_mu;
    double error_segma;
}Model;

double Kp = 0.8;
double Ki = 0.2;
double Kd = 0.1;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    Model M = {0, 10, 0.5, 0.005};
    int count = 0;
    double diff = M.goal - M.now;
    while (1) {
        printf("%lf\t%lf\t%d\n", M.now, diff/M.goal, count);
        M.now += proportion(diff, Kp) + integral(diff, Ki) + differential(diff, Kd) + gaussrand(M.error_mu, M.error_segma);
        diff = M.goal - M.now;
        count++;
        usleep(500000);
    }
    printf("%lf\n", M.now);
    printf("%d\n", count);
    return 0;
}
