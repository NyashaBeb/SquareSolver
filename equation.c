#ifndef EQUATION
#define EQUATION 1

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <float.h>
#include "colorprint.c"

enum flags {
    INFSOL = 999999,
    NOSOL = 999990,
    ONESOL = 999991,
    TWOSOL = 999992,
    IMSOL = 999998
};

int IsNull (double x);

typedef struct {
    double RE;
    double IM;
} root;

/*!
    \brief Solve binomial equation root
    \param a, b, c [in] equation coefficients
    \param x1, x2 [out] equation root
    \return IMSOL if 2 imaginary roots
    \return ONESOL if 1 real and 1 imaginary root
    \return TWOSOL if 2 real roots
    \note Don't work if equation non binomial
*/

int BinomialSolve(double a, double b, double c, root* x1, root* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (IsNull(a)) {
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
    else if (IsNull(disс)) {
        x1->RE = -b / (2 * a);
        return ONESOL;
    }
    else {
        x1->RE = (-b + sqrt(disс)) / (2 * a);
        x2->RE = (-b - sqrt(disс)) / (2 * a);
        return TWOSOL;
    }
}

/*!
    \brief Solve linear equation root
    \param a, b [in] equation coefficients
    \param x [out] equation root
    \return INFSOL if equation has infinity amount of roots
    \return NOSOL if equation has no roots
    \return ONESOL if 1 root
*/

int LinearSolve(double a, double b, root* x)
{
    assert (x != NULL);

    if (IsNull(a)) {
        return (IsNull(b))? INFSOL : NOSOL;
    }
    else {
        x->RE = -b / a;
        return ONESOL;
    }
}

/*!
    \brief Print equation roots in stream
    \param stream [in] stream directory
    \param F [in] output format flag
    \param x1, x2 [out] equation roots
*/

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
            ColorPrint(stream, "x = %gb\n", x1->RE);
            break;
        case TWOSOL:
            ColorPrint(stream, "x1 = %gb\tx2 = %gb\n", x1->RE, x2->RE);
            break;
        case IMSOL:
            ColorPrint(stream, "x1 = %gb + %gbi\tx2 = %gb + %gbi\n", x1->RE, x1->IM, x2->RE, x2->IM);
            break;
    }
    return;
}

/*!
    \brief Identify equation type
    \param a, b, c [in] equation coefficients
    \param F [out] output format key
    \param x1, x2 [out] equation roots
    \return INFSOL if equation has infinity amount of roots
    \return NOSOL if equation has no roots
    \return ONESOL if 1 root
    \return IMSOL if 2 imaginary roots
    \return TWOSOL if 2 real roots
*/

int ChooseSolve(double a, double b, double c, int F, root* x1, root* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (IsNull(a)) {
        F = LinearSolve(b, c, x1);
    }
    else if (IsNull(c)) {
        LinearSolve(a, b, x1);
        x2->RE = 0;
        F = TWOSOL;
    }
    else {
        F = BinomialSolve(a, b, c, x1, x2);
    }
    return F;
}

/*!
    \brief Check double error in equality with zero
    \param x [in]
    \return 1 or 0 like comparison ==
*/

int IsNull (double x) {
    if (fabs(x) <= DBL_EPSILON) {
        return 1;
    }
    return 0;
}

#endif
