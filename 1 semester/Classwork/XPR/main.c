#include <math.h>
#include <stdio.h>
double my_sqrt(double a) {
    double t = a / 2;
    int i;
    for (i = 0; i <= 100; i++) {
        t = 0.5 * (t + a / t);
    }
    return t;
}
int main(void) {
    char c;
    double d1 = 0;
    double d2 = 0;
    double m = 4;
    double p = 1 / (3.14);
    double l = 1;
    const double pi = 3.14;
    printf("Enter the mass \n");
    scanf("%lf", &m);
    printf("Enter the density \n");
    scanf("%lf", &p);
    printf("Enter the length \n");
    scanf("%lf", &l);
    if (m >= 0 && p >= 0 && l >= 0) {
        d1 = 2 * my_sqrt(m / (pi * p * l));
        printf("d1 = %.21f \n", d1);
        d2 = 2 * sqrt(m / (pi * p * l));
        printf("d2 = %.21f", d2);
    }
    else {
        printf("Error");
    }
    return 0;
}
