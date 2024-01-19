    #include <stdio.h>
#include <stdlib.h>

#define MILE_TO_KM 1.609344
int main(void) {
	float miles;
	float kms;
	printf("How many miles? ");
	scanf("%f", &miles);
    kms = miles * MILE_TO_KM;
	printf("That's %.2f km.", kms);
	return EXIT_SUCCESS;
}
