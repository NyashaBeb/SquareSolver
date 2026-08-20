#ifndef EQUATION
#define EQUATION 1
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

enum flags {
    INFSOL = 999999,
    NOSOL = 999990,
    ONESOL = 999991,
    TWOSOL = 999992,
    IMSOL = 999998
};

typedef struct {
    double RE;
    double IM;
} solve;

int BinomialSolver (double a, double b, double c, solve* x1, solve* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (a == 0) {
        printf("No Binomial");
        exit(EXIT_FAILURE);
    }

    double disk = b * b - 4 * a * c;

    if (disk < 0) {
        disk = -disk;
        x1->RE = x2->RE = -b / (2 * a);
        x1->IM = sqrt(disk) / (2 * a);
        x2->IM = sqrt(disk) / (-2 * a);
        return IMSOL;
    }
    else if (disk == 0) {
        x1->RE = -b / (2 * a);
        return ONESOL;
    }
    else {
        x1->RE = (-b + sqrt(disk)) / (2 * a);
        x2->RE = (-b - sqrt(disk)) / (2 * a);
        return TWOSOL;
    }
}
/*Solves Linears Arg: a, b Solve: x*/
int LinearSolver(double a, double b, solve* x)
{
    assert (x != NULL);
    if (a == 0) {
        return (b == 0)? INFSOL : NOSOL;
    }
    else {
        x->RE = -b / a;
        return ONESOL;
    }
}
/*Print Solver's Results*/
void PrintSolver(FILE* stream, int Flag, solve* x1, solve* x2)
{
    switch (Flag) {
        case INFSOL:
            fprintf(stream, "InfinitySolves\n");
            break;
        case NOSOL:
            fprintf(stream, "NoSolves\n");
            break;
        case ONESOL:
            fprintf(stream, "x = %lf\n", x1->RE);
            break;
        case TWOSOL:
            fprintf(stream, "x1 = %lf\tx2 = %lf\n", x1->RE, x2->RE);
            break;
        case IMSOL:
            fprintf(stream, "x1 = %lf + %lf\tx2 = %lf + %lf\n", x1->RE, x1->IM, x2->RE, x2->IM);
            break;
    }
    return;
}
#endif
