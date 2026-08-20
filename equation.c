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
} root;
/*Solves Binomial*/
int BinomialSolve(double a, double b, double c, root* x1, root* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (a == 0) {
        printf("No Binomial");
        exit(EXIT_FAILURE);
    }

    double disс = b * b - 4 * a * c;

    if (disс < 0) {
        disс = -disс;
        x1->RE = x2->RE = -b / (2 * a);
        x1->IM = sqrt(disс) / (2 * a);
        x2->IM = sqrt(disс) / (-2 * a);
        return IMSOL;
    }
    else if (disс == 0) {
        x1->RE = -b / (2 * a);
        return ONESOL;
    }
    else {
        x1->RE = (-b + sqrt(disс)) / (2 * a);
        x2->RE = (-b - sqrt(disс)) / (2 * a);
        return TWOSOL;
    }
}
/*Solves Linears*/
int LinearSolve(double a, double b, root* x)
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
void PrintSolve(FILE* stream, int F, root* x1, root* x2)
{
    assert (stream != NULL);
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    switch (F) {
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
            fprintf(stream, "x1 = %lf + %lfi\tx2 = %lf + %lfi\n", x1->RE, x1->IM, x2->RE, x2->IM);
            break;
    }
    return;
}
/*Choose Solve Style*/
int ChooseSolve(double a, double b, double c, int F, root* x1, root* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (a == 0) {
        F = LinearSolve(b, c, x1);
    }
    else if (c == 0) {
        LinearSolve(a, b, x1);
        x2->RE = 0;
        F = TWOSOL;
    }
    else {
        F = BinomialSolve(a, b, c, x1, x2);
    }
    return F;
}
#endif
