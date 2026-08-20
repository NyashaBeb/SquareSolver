#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

enum flags {
    INFSOL = 999999,
    NOSOL = 999990,
    ONESOL = 999991,
    TWOSOL = 999992
};

int BinomialSolver (double a, double b, double c, double* x1, double* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (a == 0) {
        printf("No Binomial");
        exit(EXIT_FAILURE);
    }

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
/*Print Solver's Results*/
void PrintSolver(FILE* stream, int Flag, double x1, double x2)
{
    switch (Flag) {
        case INFSOL:
            fprintf(stream, "InfinitySolves\n");
            break;
        case NOSOL:
            fprintf(stream, "NoSolves\n");
            break;
        case ONESOL:
            fprintf(stream, "x = %lf\n", x1);
            break;
        case TWOSOL:
            fprintf(stream, "x1 = %lf\tx2 = %lf\n", x1, x2);
            break;
    }
    return;
}
