#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

const int MAXLINE = 10000;

enum flags {
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
/*  printf("Insert a b c: (-100000/100000)\n");*/
/*File Open*/
    FILE* xin = fopen("INPUT", "r");
    FILE* xout = fopen("OUTPUT", "w");
/*Input*/
    double a = 0, b = 0, c = 0;
    char equality[MAXLINE];

    while (fgets(equality, MAXLINE, xin) != NULL)
    { /*Loop Start*/
    int test = sscanf(equality, "%lf %lf %lf", &a, &b, &c);

    if (test == EOF){
        printf("End Of File\n");
        exit(EXIT_FAILURE);
    }
    else if (test == 0) {
        printf("Argument failure\n");
        exit(EXIT_FAILURE);
    }
    else if (test != 3) {
        printf("Argument count error\n");
        exit(EXIT_FAILURE);
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
            fprintf(xout, "InfinitySolves\n");
            break;
        case NOSOL:
            fprintf(xout, "NoSolves\n");
            break;
        case ONESOL:
            fprintf(xout, "x = %lf\n", x1);
            break;
        case TWOSOL:
            fprintf(xout, "x1 = %lf\tx2 = %lf\n", x1, x2);
            break;
    }
    } /*Loop end*/
/*End Program*/
    fclose(xin);
    fclose (xout);
    printf("Files were edited succesfully\n");
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
