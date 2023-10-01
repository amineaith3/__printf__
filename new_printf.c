#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function
 * @format: A format string containing format specifiers
 *
 * This function formats and prints data to the standard output
 * based on the format string and optional arguments.
 *
 * Return: The number of characters printed on success, or -1 on failure.
 */
int _printf(const char *format, ...)
{
    int printed_chars = 0;  // Total characters printed
    va_list list;           // Argument list
    char buffer[BUFF_SIZE]; // Output buffer
    int buff_ind = 0;       // Index to add characters to the buffer

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%') // Regular character
        {
            buffer[buff_ind++] = format[i]; // Add to the buffer
            if (buff_ind == BUFF_SIZE)      // Buffer is full, print it
                print_buffer(buffer, &buff_ind);
            printed_chars++; // Increment the count of printed characters
        }
        else
        {
            print_buffer(buffer, &buff_ind); // Print the buffer if it's not empty
            i++;                             // Move to the next character after '%'
            int flags = get_flags(format, &i);         // Get formatting flags
            int width = get_width(format, &i, list);    // Get the width specifier
            int precision = get_precision(format, &i, list); // Get the precision specifier
            int size = get_size(format, &i);             // Get the size specifier
            int printed = handle_print(format, &i, list, buffer, flags, width, precision, size);
            if (printed == -1)
                return (-1);
            printed_chars += printed; // Update the total count of printed characters
        }
    }

    print_buffer(buffer, &buff_ind); // Print any remaining characters in the buffer

    va_end(list);

    return (printed_chars); // Return the total number of characters printed
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: An array of characters to print
 * @buff_ind: Pointer to the index of the next character to add to the buffer
 *
 * This function prints the characters stored in the buffer to the standard output
 * and resets the buffer index to zero.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
        write(1, &buffer[0], *buff_ind); // Write characters from the buffer to standard output

    *buff_ind = 0; // Reset the buffer index to zero
}

