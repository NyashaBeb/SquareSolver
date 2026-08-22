#ifndef COOLFOO
#define COOLFOO 1
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "colorprint.c"

int bgetc(void)
{
    char x = 0;
    if ((x = fgetc(stdin)) == EOF) {
        ColorPrint(stdout, "%rtWrong input%wt\n");
        exit(EXIT_FAILURE);
    }
    if (fgetc(stdin) != '\n') {
       ColorPrint(stdout, "%rtToo many arguments%wt\n");
       exit(EXIT_FAILURE);
    }
    return x;
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

/*!
    \brief Check scanf output
    \param scanval [in] scanf output value
    \return Stop program if something goes wrong
*/

void ScanfTest(int scanval, int num)
{
    if (scanval == EOF) {
        ColorPrint(stdout, "%rtEnd Of File%wt\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval == 0) {
        ColorPrint(stdout, "%rtArgument failure%wt\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval != num) {
        ColorPrint(stdout, "%rtArgument count error%wt\n");
        exit(EXIT_FAILURE);
    }
    return;
}
#endif
