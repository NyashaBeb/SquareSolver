#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    double disk = b * b - 4 * a * c;

    if (disk < 0) {
        printf("No Solves\n");
    }
    else if (disk == 0) {
        double solve = (-1 * b) / (2 * a);
        printf("%lf\n", solve);
    }
    else {
        double solve1, solve2;
        solve1 = (sqrt(disk) - b) / (2 * a);
        solve2 = (-1 * (sqrt(disk) + b)) / (2 * a);
        printf("%lf\t %lf\n", solve1, solve2);
    }
}
