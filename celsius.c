#include <stdio.h>
#include <stdlib.h>

#define FREEZING_PT 32.0
#define SCALE_FACTOR (5.0/9.0)
int main(void) {
	float farenheit = 0;
	float celsius = 0;
	printf("Enter Farenheit temperature: ");
	scanf("%f", &farenheit);
	celsius = (farenheit - FREEZING_PT) * SCALE_FACTOR;
	printf("Celsius equivalent: %.1f\n", celsius);
	return EXIT_SUCCESS;
}
	
