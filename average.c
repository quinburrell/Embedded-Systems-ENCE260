/* Rather meaningless program demonstrating the use of functions.
 * Taken from the text by King, section 9.2, with slight modifications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double average(double operand1, double operand2);
double discriminant(double a, double b, double c)
{
    return ((pow(b, 2)) - 4 * a * c);
}

int main(void)
{
    double num1 = 0.0, num2 = 0.0, num3 = 0.0;
    printf("Enter three numbers: ");
    scanf("%lf%lf%lf", &num1, &num2, &num3);
    printf("Average of %g and %g: %g\n", num1, num2, average(num1,num2));
    printf("Average of %g and %g: %g\n", num2, num3, average(num2,num3));
    printf("Average of %g and %g: %g\n", num1, num3, average(num1,num3));
    printf("discriminant: %g", discriminant(num1, num2, num3));
    return EXIT_SUCCESS;
}

double average(double operand1, double operand2)
{
    return (operand1 + operand2) / 2;
}
