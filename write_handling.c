#include "main.h"

// Function to handle writing a single character to a buffer and printing it
int handle_write_char(char c, char buffer[], int flags, int width) {
    int i = 0;

    // Check if zero padding flag is set
    if (flags & F_ZERO) {
        buffer[i++] = '0';
    }

    // Store the character in the buffer
    buffer[i++] = c;
    buffer[i] = '\0';

    // Check if a width is specified
    if (width > 1) {
        if (flags & F_MINUS) {
            // If minus flag is set, print character followed by padding
            return (write(1, &buffer[0], 1) + write(1, &buffer[1], width - 1));
        } else {
            // If minus flag is not set, print padding followed by character
            return (write(1, &buffer[1], width - 1) + write(1, &buffer[0], 1));
        }
    }

    // If no width, just print the character
    return (write(1, &buffer[0], 1));
}

// Function to handle writing a number to a buffer and printing it
int write_number(int is_negative, int ind, char buffer[], int flags, int width) {
    int length = BUFF_SIZE - ind - 1;
    char padd = ' ', extra_ch = 0;

    // Determine padding character based on flags
    if ((flags & F_ZERO) && !(flags & F_MINUS)) {
        padd = '0';
    }
    
    // Determine extra character (e.g., '-' for negative numbers)
    if (is_negative) {
        extra_ch = '-';
    } else if (flags & F_PLUS) {
        extra_ch = '+';
    } else if (flags & F_SPACE) {
        extra_ch = ' ';
    }

    // Call the helper function to print the number
    return (write_num(ind, buffer, flags, width, length, padd, extra_ch));
}

// Function to write a number to a buffer and print it
int write_num(int ind, char buffer[], int flags, int width, int length, char padd, char extra_c) {
    int i, padd_start = 1;

    // Adjust the length if an extra character is present
    if (extra_c != 0) {
        length++;
    }

    // Check if width is specified
    if (width > length) {
        for (i = 1; i < width - length + 1; i++) {
            buffer[i] = padd;
        }
        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ') {
            // If minus flag is set and padding is space, print extra char before the number
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
        } else if (!(flags & F_MINUS) && padd == ' ') {
            // If minus flag is not set and padding is space, print extra char after the number
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
        } else if (!(flags & F_MINUS) && padd == '0') {
            // If minus flag is not set and padding is zero, print extra char before the padding
            if (extra_c) {
                buffer[--padd_start] = extra_c;
            }
            return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start)));
        }
    }

    // If no width, print the number with or without the extra char
    if (extra_c) {
        buffer[--ind] = extra_c;
    }
    return (write(1, &buffer[ind], length));
}

// Function to handle writing an unsigned number to a buffer and printing it
int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width) {
    int length = BUFF_SIZE - ind - 1, i = 0;
    char padd = ' ';

    // Check if precision is greater than zero and less than the length
    if (precision > 0 && precision < length) {
        padd = ' ';
    }

    // Determine padding character based on flags
    if ((flags & F_ZERO) && !(flags & F_MINUS)) {
        padd = '0';
    }

    // Check if width is specified
    if (width > length) {
        for (i = 0; i < width - length; i++) {
            buffer[i] = padd;
        }
        buffer[i] = '\0';

        if (flags & F_MINUS) {
            // If minus flag is set, print the number followed by padding
            return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
        } else {
            // If minus flag is not set, print padding followed by the number
            return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
        }
    }

    // If no width, print the number
    return (write(1, &buffer[ind], length));
}

// Function to handle writing a pointer address to a buffer and printing it
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start) {
    int i;

    // Check if width is specified
    if (width > length) {
        for (i = 3; i < width - length + 3; i++) {
            buffer[i] = padd;
        }
        buffer[i] = '\0';

        if (flags & F_MINUS && padd == ' ') {
            // If minus flag is set and padding is space, print extra char and address before the padding
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
        } else if (!(flags & F_MINUS) && padd == ' ') {
            // If minus flag is not set and padding is space, print extra char and address after the padding
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c) {
                buffer[--ind] = extra_c;
            }
            return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
        } else if (!(flags & F_MINUS) && padd == '0') {
            // If minus flag is not set and padding is zero, print extra char and address before the padding
            if (extra_c) {
                buffer[--padd_start] = extra_c;
            }
            buffer[1] = '0';
            buffer[2] = 'x';
            return (write(1, &buffer[padd_start], i - padd_start) +
                    write(1, &buffer[ind], length - (1 - padd_start) - 2));
        }
    }

    // If no width, print the pointer address
    buffer[--ind] = 'x';
    buffer[--ind] = '0';
    if (extra_c) {
        buffer[--ind] = extra_c;
    }
    return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

