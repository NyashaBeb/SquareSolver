#include <stdio.h>
#include <math.h>
#include <assert.h>

enum flags{
    INFSOL = 999999,
    NOSOL = 999990,
    ONESOL = 999991,
    TWOSOL = 999992
};

/*Using Functions*/
int BinomialSolver(double a, double b, double c, double* x1, double* x2);
int LinearSolver(double b, double c, double* x);

int main()
{
/*Program Start*/
    printf("SquareSolver2008\n2026 (c) Nyasha\n");
    printf("Insert a b c:\n");
/*Input*/
    double a = 0, b = 0, c = 0;
    if (scanf("%lf %lf %lf", &a, &b, &c) < 3){
        printf("Argument count error\n");
        return 0;
    }
/*Choose*/
    int Flag = 0;
    double x1 = 0, x2 = 0;

    if (a == 0){
        Flag = LinearSolver(b, c, &x1);
    }
    else {
        Flag = BinomialSolver(a, b, c, &x1, &x2);
    }
/*Printing*/
    switch (Flag){
        case INFSOL:
            printf("InfinitySolves\n");
            break;
        case NOSOL:
            printf("NoSolves\n");
            break;
        case ONESOL:
            printf("x = %lf\n", x1);
            break;
        case TWOSOL:
            printf("x1 = %lf\tx2 = %lf\n", x1, x2);
            break;
    }
    return 0;
}
/*Solves Binomials Arg: a, b, c Solves: x1, x2*/
int BinomialSolver (double a, double b, double c, double* x1, double* x2)
{
    double disk = b * b - 4 * a * c;

    if (disk < 0) {
        return 0;
    }
    else if (disk == 0) {
        *x1 = -b / (2 * a);
        return 1;
    }
    else {
        *x1 = (-b + sqrt(disk)) / (2 * a);
        *x2 = (-b - sqrt(disk)) / (2 * a);
        return 2;
    }
}
/*Solves Linears Arg: a, b Solve: x*/
int LinearSolver(double a, double b, double* x)
{
    if (a == 0) {
        return (b == 0)? INFSOL : NOSOL;
    }
    else {
        *x = -b / a;
        return ONESOL;
    }
}
