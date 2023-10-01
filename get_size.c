#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: Current position in the format string
 *
 * Return: Size specifier.
 */
int get_size(const char *format, int *i) {
    int curr_i = *i + 1;
    int size = 0;

    if (format[curr_i] == 'l') {
        size = S_LONG;
    } else if (format[curr_i] == 'h') {
        size = S_SHORT;
    }

    *i = (size == 0) ? curr_i - 1 : curr_i;
    return size;
}

