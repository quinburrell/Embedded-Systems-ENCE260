#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

void sayHi(const char* name)
{
    printf("Hi %s!", name);
}

int add_even_sub_odd(const int data[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] % 2 == 0) {
            sum += data[i];
        } else {
            sum -= data[i];
        }
    }
    return sum;
}

char* alphaShiftRight(char* s)
{
    int slen = strlen(s);
    for (int i = 0; i < slen; i++) {
        char letter = s[i];
        if ((letter > 64 && letter < 90) | (letter > 96 && letter < 122)) {
            letter += 1;
        } else if ((letter == 90) | (letter == 122)) {
            letter -= 25;
        }
        s[i] = letter;
    }
    return s;
}

void swap3(int* x, int* y, int* z)
{
    int temp;
    if (*x < *z) {
        temp = *z;
        *z = *x;
        *x = temp;
    }
    if (*x < *y) {
        temp = *y;
        *y = *x;
        *x = temp;
    }
    if (*y < *z) {
        temp = *y;
        *y = *z;
        *z = temp;
    }
}

int mystrnlen(const char* s, int maxlen)
{
    for (int i = 0; i < maxlen; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return maxlen;
}

int* pairSumSearch(int* data, int numEls, int pairSum)
{
    for (int i = 1; i < numEls; i++) {
        if ((data[i-1] + data[i]) == pairSum) {
            return &data[i-1];
        }
    }
    return NULL;
}

typedef struct {
    char type[50];
    int energy;
    double price;
} Pizza;

typedef struct {
    int x;
    int y;
    int z;
} Vector3d;

Vector3d vector(int x, int y, int z)
{
    Vector3d new = {x, y, z};
    return new;
}

char** split(const char* s)
{
    char* result = malloc(strlen(s));
    char* word = malloc(strlen(s));
    int n = 0, w = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace(s[i]) == 1) {
            result[n] = *word;
            n++;
            w = 0;
        } else {
            word[w] = s[i];
            w++;
        }
    }
    result[n] = 0;
    free(word);
    return *result;
}

int main(void)
{
   char** words = split("He said 'hello' to me!");
int i = 0;
while (words[i] != NULL) {
    puts(words[i]);
    free(words[i]);
    i += 1;
}
free(words);
}
