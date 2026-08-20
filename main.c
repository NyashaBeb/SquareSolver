#include <stdio.h>
#include <math.h>
#include <assert.h>

#define NOLL -9999999
#define INFAN -9999998

int BinarySolver(double, double, double, double*, double*);
int LinearSolver(double, double, double*);

int main()
{
    printf("SquareSolver2008\t 2026 (c) Nyasha\n");
    printf("Insert a b c:\n");

    double a = 0, b = 0, c = 0;
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0){
        double x = 0;
        int Flag = LinearSolver(b, c, &x);
        switch (Flag){
            case INFAN:
                printf("InfinitySolves\n");
                break;
            case NOLL:
                printf("NoSolves\n");
                break;
            default:
                printf("x = %lf\n", x);
                break;
        }
    }
    else {
        double x1 = 0, x2 = 0;
        int Flag = BinarySolver(a, b, c, &x1, &x2);
        switch(Flag){
            case 0:
                printf("NoSolves\n");
                break;
            case 1:
                printf("x = %lf\n", x1);
                break;
            case 2:
                printf("x1 = %lf\tx2 = %lf\n", x1, x2);
                break;
        }
    }
    return 0;
}

int BinarySolver (double a, double b, double c, double* x1, double* x2)
{
    double disk = b * b - 4 * a * c;

    if (disk < 0) {
        *x1 = -1;
        *x2 = -1;
        return 0;
    }
    else if (disk == 0) {
        *x1 = -b / (2 * a);
        *x2 = -1;
        return 1;
    }
    else {
        *x1 = (-b + sqrt(disk)) / (2 * a);
        *x2 = (-b - sqrt(disk)) / (2 * a);
        return 2;
    }
}

int LinearSolver(double b, double c, double* x)
{
    if (b == 0){
        *x = -1;
        return (c == 0)? INFAN : NOLL;
    }
    else if (c == 0){
        *x = 0;
        return 0;
    }
    else {
        *x = -c / b;
        return 0;
    }
}
