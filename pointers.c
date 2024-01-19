#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printViaPtr(const int* intPtr)
{
    printf("%d\n", *intPtr);
}

void print2Ints(int number1, int number2) 
{
    printViaPtr(&number1);
    printViaPtr(&number2);
}

void swap(int* address1, int* address2)
{
    int temp = *address1;
    *address1 = *address2;
    *address2 = temp;
}

void oof(char* p1, char* p2)
{
    *p1 = *p2;
}

// Print the first n elements of array data in braces, comma-separated
void printArray(const int data[], int n)
{
    if (n <= 0) {
        printf("{}");
    }
    else {      
        printf("{%d", data[0]);
        for (int i = 1; i < n; i++) {
            printf(",%d", data[i]);
        }
        printf("}");
    }
}

void findTwoLargest(const int data[], int n, int* largest, int* second)
{
    for (int i = 0; i < n; i++) {
        if ((data[i] > *second) | (*second == 0)) {
            if ((data[i] > *largest) | (*largest == 0)) {
                *second = *largest;
                *largest = data[i];
            } else {
                *second = data[i];
            }
        }
    }
}

// Test the function findTwoLargest on array 'data' of length 'n.
// It is assumed that n >= 2.
void test_array(const int data[], int n)
{
    int largest = 0, second = 0;

    findTwoLargest(data, n, &largest, &second);
    printf("The two largest elements from ");
    printArray(data, n);
    printf(" are %d and %d\n", largest, second);
}

// Next, a set of test arrays

int array1[] = { 1, 2, 3, 4, 5, 6 };
int array2[] = { 20, 19, 18 };
int array3[] = { -1, -2, -3 , -17 };
int array4[] = { 17, 14 };
int array5[] = { 4, 45, 123, 3, 345, 27, 479 };

// Lastly, the main test routine.
int main()
{
    test_array(array1, 6);
    test_array(array2, 3);
    test_array(array3, 4);
    test_array(array4, 2);
    test_array(array5, 7);
    return 0;
}
