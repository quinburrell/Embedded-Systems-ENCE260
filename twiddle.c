#include <stdio.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 80

// Read a name (or any string) into the parameter array.
// Terminate it with null.
void readName(int maxLen, char name[])
{
    int c = 0;
    int i = 0;
    printf("Enter your name: ");
    while ((c = getchar()) != '\n' && c != EOF && i < maxLen - 1) {
        name[i++] = c;
    }
    name[i] = '\0';  /* terminator */
}

void convertStringToUpper(char name[]) 
{
    int i = 0;
    while (name[i] != '\0') {
        name[i] = toupper(name[i]);
        i++;
    }
}

int countMatches(int n, int data[], int searchValue)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] == searchValue) {
           count++; 
        }
    }
    return count;
}

int main(void)
{
    char name[MAX_NAME_LENGTH];
    readName(MAX_NAME_LENGTH, name);
    convertStringToUpper(name);
    printf("Your name in upper case: %s\n", name);
    int nums[] = {1, 2, 3, 4, 1, 1, 5}; 
    printf("%d\n", countMatches(7, nums, 1));
}
