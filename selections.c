#include <stdio.h>

int main(void)
{
	int value = 0;
	printf("what's the pip-value of your playing card? ");
	scanf("%d", &value);
	if (value < 1 || value > 13) {
		puts("No such card");
	} else if (value == 1) {
		puts("It's an ace.");
	} else if (value < 11) {
		printf("It's a %d.\n", value);
	} else {
		printf("It's a face card. Specifically a ");
		switch (value) {
		case 11:
			puts("Jack.");
			break;
		case 12:
			puts("Queen.");
			break;
		case 13:
			puts("King.");
		}
	}
}
