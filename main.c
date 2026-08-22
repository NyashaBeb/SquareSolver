#include "equation.c"
#include "colorprint.c"
#include "coolfoo.c"
/*Using Functions*/
int ManPut(void);
int FilePut(void);

int main()
{
/*Program Start*/
    printf("SquareSolver2008\n2026 (c) Nyasha\n");
    ColorPrint(stdout, "%btManual%wt or %btFile%wt input? [m/f]\n");
    char x = bgetc();
/*Terminal argument work*/
    switch (x) {
        case 'm':
            ManPut();
            break;
        case 'f':
            FilePut();
            break;
        default:
            ColorPrint(stdout, "%rtWrong input%wt\n");
            return 1;
    }
    return 0;
}

/*!
    \brief Handle user's input from stdin to solve equation
    \return Output equation roots to stdout
    \note Asks parameters later
*/

int ManPut(void)
{
    ColorPrint(stdout, "Type: %bc, %bc, %bc (a * x^2 + b * x + c = 0)\n", 'a', 'b', 'c');
/*Input*/
    double a = 0, b = 0, c = 0;

    int test = scanf("%lf %lf %lf", &a, &b, &c);
    ScanfTest(test, 3);
/*Choose*/
    int key = 0;
    root x1 = { 0 }, x2 = { 0 };
    key = ChooseSolve(a, b, c, key, &x1, &x2);
/*Printing*/
    PrintSolve(stdout, key, &x1, &x2);
/*End Program*/
    ColorPrint(stdout, "%gtSuccess%wt\n");
    return 0;
}

/*!
    \brief Handle user's input from file to solve equation
    \return Output equation roots to file
    \note Asks parameters later
*/

int FilePut(void)
{
/*File input*/
    ColorPrint(stdout, "Type: %btfile1%wt (from)\n");
    char from[MAXLINE] = { 0 };
    scanf("%s", from);

    FILE* xin;
    if ((xin = fopen(from, "r")) == NULL) {
        ColorPrint(stdout, "%rtNo such file in directory%wt\n");
        exit(EXIT_FAILURE);
    }

    ColorPrint(stdout, "Type: %btfile2%wt (from)\n");
    char to[MAXLINE] = { 0 };
    scanf("%s", to);

    FILE* xout;
    if ((xout = fopen(to, "w")) == NULL) {
        ColorPrint(stdout, "%rtNo such files in directory%wt\n");
        exit(EXIT_FAILURE);
    }
/*Input*/
    double a = 0, b = 0, c = 0;
    char equation[MAXLINE] = { 0 };

    while (fgets(equation, MAXLINE, xin) != NULL)
    { /*Loop Start*/
        int test = sscanf(equation, "%lf %lf %lf", &a, &b, &c);
        ScanfTest(test, 3);
    /*Choose*/
        int F = 0;
        root x1 = { 0 }, x2 = { 0 };

        F = ChooseSolve(a, b, c, F, &x1, &x2);
    /*Printing*/
        PrintSolve(xout, F, &x1, &x2);
    } /*Loop end*/
    fclose(xin);
    fclose (xout);
    ColorPrint(stdout, "%gtFile was edited successfully%wt\n");
    return 0;
}
