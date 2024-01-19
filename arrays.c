#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    int c = 0;
    int counts[26] = {0};
    while((c = getchar()) != EOF) {
        if (isalpha(c) != 0) {
            c = toupper(c);
            counts[c-'A']++;
        } 
    }
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", i + 'A', counts[i]);
    }
    return EXIT_SUCCESS;
}
