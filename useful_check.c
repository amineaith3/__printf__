#include "main.h"

// Function to check if a character is printable
int is_printable(char c) {
    return (c >= 32 && c < 127);
}

// Function to append ASCII code in hexadecimal format to a buffer
int append_hexa_code(char ascii_code, char buffer[], int i) {
    char map_to[] = "0123456789ABCDEF";
    
    if (ascii_code < 0) {
        ascii_code *= -1;
    }

    buffer[i++] = '\\';
    buffer[i++] = 'x';
    buffer[i++] = map_to[ascii_code / 16];
    buffer[i] = map_to[ascii_code % 16];

    return 3;
}

// Function to check if a character is a digit
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

// Function to cast a number to the specified size
long int convert_size_number(long int num, int size) {
    if (size == S_LONG) {
        return num;
    } else if (size == S_SHORT) {
        return (short)num;
    } else {
        return (int)num;
    }
}

// Function to cast an unsigned number to the specified size
unsigned long int convert_size_unsgnd(unsigned long int num, int size) {
    if (size == S_LONG) {
        return num;
    } else if (size == S_SHORT) {
        return (unsigned short)num;
    } else {
        return (unsigned int)num;
    }
}

