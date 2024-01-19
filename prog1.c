#include <stdio.h>
#include <math.h>

int main(void)
{
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a==0) {
        puts("Not a quadratic");
    } else {
        double root1 = b*b-(4*a*c);
        if (root1 < 0) {
            puts("Complex roots");
        } else {
            root1 = sqrt(root1);
            double root2 = (-b + root1)/(2*a);
            root1 = (-b - root1)/(2*a);
            if (root1 > root2) {
				double temp = root1;
				root1 = root2;
				root2 = temp;
			}
            printf("Roots are %.4f and %.4f", root1, root2);
        }
    }
}
