#include "equation.c"
#include "colorprint.c"

/*Using Functions*/
void scanftest(int scanval);
int ManPut(void);
int FilePut(void);

int main()
{
/*Program Start*/
    printf("SquareSolver2008\n2026 (c) Nyasha\n");
    ColorPrint(stdout, "%btManual%wt or %btFile%wt input? [m/f]\n");
    char x = 0;
    if ((x = fgetc(stdin)) == EOF) {
        ColorPrint(stdout, "%rtWrong input%rt\n");
        exit(EXIT_FAILURE);
    }
/*Terminal argument work*/
    if (x == 'm') {
        ManPut();
    }
    else {
        FilePut();
    }
    return 0;
}
/*Check scanf result*/
void scanftest(int scanval)
{
    if (scanval == EOF) {
        ColorPrint(stdout, "%rtEnd Of File%rt\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval == 0) {
        ColorPrint(stdout, "%rtArgument failure%rt\n");
        exit(EXIT_FAILURE);
    }
    else if (scanval != 3) {
        ColorPrint(stdout, "%rtArgument count error%rt\n");
        exit(EXIT_FAILURE);
    }
}
/*Manual input/output style*/
int ManPut(void)
{
    ColorPrint(stdout, "Type: %bc, %bc, %bc (a * x^2 + b * x + c = 0)\n", 'a', 'b', 'c');
/*Input*/
    double a = 0, b = 0, c = 0;

    int test = scanf("%lf %lf %lf", &a, &b, &c);
    scanftest(test);
/*Choose*/
    int F = 0;
    root x1 = { 0 }, x2 = { 0 };
    F = ChooseSolve(a, b, c, F, &x1, &x2);
/*Printing*/
    PrintSolve(stdout, F, &x1, &x2);
/*End Program*/
    ColorPrint(stdout, "%gtSuccess%wt\n");
    return 0;
}
/*Files input/output style*/
int FilePut(void)
{
/*File input*/
    ColorPrint(stdout, "Type: %btfile1%wt (from)\n");
    char from[MAXLINE] = { 0 };
    scanf("%s", from);

    FILE* xin;
    if ((xin = fopen(from, "r")) == NULL) {
        ColorPrint(stdout, "%rtNo such file in directory%rt\n");
        exit(EXIT_FAILURE);
    }

    ColorPrint(stdout, "Type: %btfile2%wt (from)\n");
    char to[MAXLINE] = { 0 };
    scanf("%s", to);

    FILE* xout;
    if ((xout = fopen(to, "w")) == NULL) {
        ColorPrint(stdout, "%rtNo such files in directory%rt\n");
        exit(EXIT_FAILURE);
    }
/*Input*/
    double a = 0, b = 0, c = 0;
    char equation[MAXLINE] = { 0 };

    while (fgets(equation, MAXLINE, xin) != NULL)
    { /*Loop Start*/
        int test = sscanf(equation, "%lf %lf %lf", &a, &b, &c);
        scanftest(test);
    /*Choose*/
        int F = 0;
        root x1 = { 0 }, x2 = { 0 };

        F = ChooseSolve(a, b, c, F, &x1, &x2);
    /*Printing*/
        PrintSolve(xout, F, &x1, &x2);
    } /*Loop end*/
/*End Program*/
    fclose(xin);
    fclose (xout);
    ColorPrint(stdout, "%gtFile was edited successfully%wt\n");
    return 0;
}
