#include "equation.c"
#include "colorprint.c"

const int REPEAT = 2;

typedef struct {
    double a;
    double b;
    double c;
} coeffs;

typedef struct {
    int nroot;
    root x1;
    root x2;
} sol;

typedef struct {
    int nroot;
    root x1;
    root x2;
} solref;

int TakeSolveValue(int flag);
int BinomialTest(int key, coeffs* abc, sol* x1x2, solref* x1x2r);
int BinomialTestPrint(int key);
int ParseFile(FILE* stream, coeffs* abc, solref* x1x2r);
void TestPrint(int fmt, coeffs abc, sol x1x2, solref x1x2r);
int TestCmp(sol* x1x2, solref* x1x2r);

int main()
{
    printf("EquationTester2004\n2026 (c) Nyasha\n");
/*User ask [bi/li]*/
    ColorPrint(stdout, "%btBinomial%wt or %btLinear%wt: [b/l]\n");
    int x = bgetc();
/*Test*/
    switch (x) {
        case 'b':
            BinomialTestPrint(2);
            break;
        case 'l':
            BinomialTestPrint(1);
            break;
        default:
            ColorPrint(stdout, "%rtWrong input%wt\n");
            break;
    }
    return 0;
}

int BinomialTest(int key, coeffs* abc, sol* x1x2, solref* x1x2r)
{
    int res = 0;
/*my tests*/
    FILE* stream;
    if (key == 1) {
        stream = fopen("LINTESTLIST", "r");
    }
    else if (key == 2) {
        stream = fopen("BINTESTLIST", "r");
    }
    else {
        ColorPrint(stdout, "%rtKey Failure\n");
        exit(EXIT_FAILURE);
    }

    int repeat = 0;
    for (repeat = REPEAT; repeat > 0; --repeat)
    {
        ParseFile(stream, abc, x1x2r);
        if (key == 1) {
            res = LinearSolve(abc->a, abc->b, &x1x2->x1);
        }
        else {
            res = BinomialSolve(abc->a, abc->b, abc->c, &x1x2->x1, &x1x2->x2);
        }
        x1x2->nroot = TakeSolveValue(res);
    /*compare*/
        if (TestCmp(x1x2, x1x2r) == 0) {
            fclose(stream);
            return key;
        }
    }
    fclose(stream);
    return 0;
}

int BinomialTestPrint(int key)
{
    int fmt = -1;
    coeffs abc = { 0 };
    sol x1x2 = { 0 };
    solref x1x2r = { 0 };

    fmt = BinomialTest(key, &abc, &x1x2, &x1x2r);

    TestPrint(fmt, abc, x1x2, x1x2r);
    return 0;
}

int TakeSolveValue(int flag) {
    switch(flag) {
        case NOSOL:
            return 0;
        case ONESOL:
            return 1;
        case TWOSOL:
            return 2;
        case IMSOL:
            return -2;
        case INFSOL:
            return 9;
        default:
            ColorPrint(stdout, "%rtSolve error%wt\n");
            exit(EXIT_FAILURE);
    }
}

int ParseFile(FILE* stream, coeffs* abc, solref* x1x2r)
{
    int out = fscanf(stream, "%lf %lf %lf", &abc->a, &abc->b, &abc->c);
    ScanfTest(out, 3);
    out = fscanf(stream, "%d %lf %lf %lf %lf", &x1x2r->nroot, &x1x2r->x1.RE, &x1x2r->x1.IM, &x1x2r->x2.RE, &x1x2r->x2.IM);
    ScanfTest(out, 5);
    return 0;
}

int TestCmp(sol* x1x2, solref* x1x2r)
{
    if (x1x2->nroot != x1x2r->nroot) {
        return 0;
    }
    else if (x1x2->x1.IM != x1x2r->x1.IM || x1x2->x1.RE != x1x2r->x1.RE) {
        return 0;
    }
    else if (x1x2->x2.IM != x1x2r->x2.IM || x1x2->x2.RE != x1x2r->x2.RE) {
        return 0;
    }
    return 1;
}

void TestPrint(int fmt, coeffs abc, sol x1x2, solref x1x2r)
{
    if (fmt == 0) {
        ColorPrint(stdout, "%gtAll correct%wt\n");
    }
    else if (fmt == 1) {
        ColorPrint(stdout, "\n%rtTest failed :%wt %bc = %wb, %bc = %wb\n\n"
                   "%rtExpected    :%wt %btnroots%wt = %wd, %btx1%wt = %wb\n"
                   "%rtGot         :%wt %btnroots%wt = %wd, %btx1%wt = %wb\n",
                   'a', abc.a, 'b', abc.b,
                   x1x2r.nroot, x1x2r.x1.RE,
                   x1x2.nroot, x1x2.x1.RE
                );
    }
    else if (fmt == 2) {
    ColorPrint(stdout, "\n%rtTest failed :%wt %bc = %wb, %bc = %wb, %bc = %wb\n\n"
                  "%rtExpected    :%wt %btnroots%wt = %wd, %btx1%wt = %wb + %wbi, %btx2%wt = %wb + %wbi\n"
                  "%rtGot         :%wt %btnroots%wt = %wd, %btx1%wt = %wb + %wbi, %btx2%wt = %wb + %wbi\n",
                  'a', abc.a, 'b', abc.b, 'c', abc.c,
                  x1x2r.nroot, x1x2r.x1.RE, x1x2r.x1.IM, x1x2r.x2.RE, x1x2r.x2.IM,
                  x1x2.nroot, x1x2.x1.RE, x1x2.x1.IM, x1x2.x2.RE, x1x2.x2.IM
                );
    }
    else {
        ColorPrint(stdout, "%rtWrong format%wt\n");
        exit(EXIT_FAILURE);
    }
    return;
}
