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
int LinearSolver(double a, double b, double* x);

int main()
{
/*Program Start*/
    printf("SquareSolver2008\n2026 (c) Nyasha\n");
    printf("Insert a b c: (-100000/100000)\n");
/*Input*/
    double a = 0, b = 0, c = 0;
    int test = scanf("%lf %lf %lf", &a, &b, &c);
    if (test == EOF){
        printf("End Of File\n");
        return 0;
    }
    else if (test != 3) {
        printf("Argument count error\n");
        return 0;
    }
/*Choose*/
    int Flag = 0;
    double x1 = 0, x2 = 0;

    if (a == 0) {
        Flag = LinearSolver(b, c, &x1);
    }
    else {
        Flag = BinomialSolver(a, b, c, &x1, &x2);
    }
/*Printing*/
    switch (Flag) {
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
    assert (x1 != NULL);
    assert (x2 != NULL);
    double disk = b * b - 4 * a * c;

    if (disk < 0) {
        return NOSOL;
    }
    else if (disk == 0) {
        *x1 = -b / (2 * a);
        return ONESOL;
    }
    else {
        *x1 = (-b + sqrt(disk)) / (2 * a);
        *x2 = (-b - sqrt(disk)) / (2 * a);
        return TWOSOL;
    }
}
/*Solves Linears Arg: a, b Solve: x*/
int LinearSolver(double a, double b, double* x)
{
    assert (x != NULL);
    if (a == 0) {
        return (b == 0)? INFSOL : NOSOL;
    }
    else {
        *x = -b / a;
        return ONESOL;
    }
}
