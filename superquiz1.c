/*program takes a single b bit int input and returns it and 
 * its assosiated ascii char */
#include <stdio.h>

// A function to read a small format (8-bit) number
int readUCharInt(unsigned char* input)
{
    int size;
    size = scanf("%hhu", input);
    return size;
}

//reads a string of int values from input and places them in an array
int readInput(unsigned char input[], size_t inputMaxLength)
{
    int i = 0;
    while (i < inputMaxLength) {
        int value = readUCharInt(&input[i]);
        if (value == -1) {
            return i;
        }
        i++;
    }
    if (input[i+1] != '\0') {
        return -1;
    } else {
        return i;
    }
}

//splits the input based on a key at the start of the input array.
int splitInput(unsigned char input[], size_t inputLength, int section, unsigned char part[], size_t maxPartLength)
{
    int i = 1;
    if (section == 0) {
        while (input[i] != input[0]) {
            if (i > maxPartLength) {
                return -1;
            }
            part[i-1] = input[i];
            i++;
        }
    } 
    if (section == 1) {
        int j = 1;
        while (input[j] != input[0]) {
            j++;
        }
        while (i+j < inputLength) {
            if (i >= maxPartLength) {
                return -1;
            }
            part[i-1] = input[i+j];
            i++;
        }
    } 
    return --i;
}

//decrypts the message based on key numbers as per Caesar cipher
void decryptMessage(unsigned char key[], size_t keyLength, unsigned char message[], size_t messageLength)
{
    int i, j = 0;
    for (i = 0; i < messageLength; i++) {
        if (j == keyLength) {
            j = 0;
        }
        message[i] -= key[j];
        j++;
    }
    message[i+1] = 0;
}

/*reads an input of ints representing a message encrypted by the caesar
cipher, decrypts it, then outputs it as ASCII characters */
#define MAX_INPUT_LENGTH 4096
#define MAX_KEY_LENGTH 1022
#define MAX_TEXT_LENGTH 3071
int main()
{
    unsigned char input[MAX_INPUT_LENGTH], key[MAX_KEY_LENGTH], message[MAX_TEXT_LENGTH];
    int inputLength = readInput(input, MAX_INPUT_LENGTH);
    int keyLength = splitInput(input, inputLength, 0, key, MAX_KEY_LENGTH);
    int messageLength = splitInput(input, inputLength, 1, message, MAX_KEY_LENGTH);
    decryptMessage(key, keyLength, message, messageLength);
    for (int i = 0; i < messageLength; i++) {
        printf("%c", message[i]);
    }
}
