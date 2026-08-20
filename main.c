#include "equation.c"

const int MAXLINE = 10000;
/*Using Functions*/
void scanftest(int scanval);

int main()
{
/*Program Start*/
    printf("SquareSolver2008\n2026 (c) Nyasha\n");
 /*  printf("Insert a b c: (-100000/100000)\n"); */
/*File Open*/
    FILE* xin = fopen("INPUT", "r");
    FILE* xout = fopen("OUTPUT", "w");
/*Input*/
    double a = 0, b = 0, c = 0;
    char equation[MAXLINE] = { 0 };

    while (fgets(equation, MAXLINE, xin) != NULL)
    { /*Loop Start*/
    int test = sscanf(equation, "%lf %lf %lf", &a, &b, &c);
    scanftest(test);
    /*Choose*/
    int F = 0;
    root x1 = {0}, x2 = {0};

    F = ChooseSolve(a, b, c, F, &x1, &x2);
    /*Printing*/
    PrintSolve(xout, F, &x1, &x2);
    } /*Loop end*/
/*End Program*/
    fclose(xin);
    fclose (xout);
    printf("Files were edited succesfully\n");
    return 0;
}

void scanftest(int scanval)
{
    if (scanval == EOF){
        printf("End Of File\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval == 0) {
        printf("Argument failure\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval != 3) {
        printf("Argument count error\n");
        exit(EXIT_FAILURE);
    }
}
