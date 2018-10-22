#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sum_of_squares(int x, int y) {
    printf("Calculating the sum of squares of %d and %d\n", x, y);
    return x * x + y * y;
}
double sum_of_sqrts(double d, double e) {
    printf("Calculating the sum of square roots of %f and %f\n", d, e);
    return sqrt(d) + sqrt(e);
}
void print_bigger_arg(int x, double d) {
    printf("This function doesn't return anything;\n");
    printf("It just prints out whichever argument is bigger.\n");
    printf("The biggest argument is ");
    if (x > d) {
        printf("%d\n", x);
    } else {
        printf("%f\n", d);
    }
}
int main(void) {
    int first_result;
    double second_result;
    first_result = sum_of_squares(3, 4);
    printf("result = %d\n", first_result);
    second_result = sum_of_sqrts(3.0, 4.0);
    printf("result = %f\n", second_result);
    print_bigger_arg(3, 4.0);

    return EXIT_SUCCESS;
}
