#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double* randomArray(size_t n)
{
    double* numbers = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        numbers[i] = (1.0 * rand()) / RAND_MAX;
    }
    return numbers;
}

int* ramp(size_t n)
{
    int* numbers = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
    return numbers;
}

void fillRamp(int* data, size_t n)
{
    for (int i = 0; i < n; i++) {
        data[i] = i + 1;
    }
}


char* skipping(const char*s)
{
    
    size_t len = strlen(s);
    char* copy = malloc((len+1));
    if (len == 0) {
        copy[0] = 0;
    } else {
        int i = 0;
        while (i < len) {
            if ((i % 2) == 0) {
                copy[i/2] = s[i];
            }
            i++;
        }
        copy[(i+1)/2] = 0;
    }
    return copy;
}

int main(void)
{
    /*int n = 0;
    double* randomNums = NULL;
    printf("How many random doubles? ");
    scanf("%d", &n);
    randomNums = randomArray(n);
    for (int i = 0; i < n; i++) {
        printf("%d, %.6f\n", i, randomNums[i]);
    }
    printf("\n");
    free(randomNums);*/
    /*
    int* data = malloc(4 * sizeof(int));
    fillRamp(data, 4);
    for (int i = 0; i < 4; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }
    free(data);
    return 0;*/
    
    const char* s = "";
    char* skipStr = skipping(s);
    printf("%s", skipStr);
    free(skipStr);
    return 0;
}
