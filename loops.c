#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    for (int n = n1; n <= n2; n++) {
        bool isprime = true;
        for (int i = 2; i < n && isprime; i++) {
            if (n % i == 0) {
                isprime = false;
            }
        } 
        if (isprime) {
            printf("%d\n", n);
        }
    }
}
