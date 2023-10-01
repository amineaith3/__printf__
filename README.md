# new_printf

## Custom Printf Implementation
This project implements a custom printf function, named _printf, in C. 
The custom printf function allows you to format and print data to the standard output using format specifiers similar to the standard printf function in the C Standard Library.

## Project Structure
The project is organized into several source code files, each containing specific functionality. Here's an overview of the project structure:

## Source Files:
new_printf.c: The main entry point of the custom printf function, which processes the format string and calls relevant functions to handle format specifiers.
functions.c, functions1.c, functions2.c: Files containing functions for handling various format specifiers (e.g., %c, %s, %d, %x, etc.).
get_flags.c, get_width.c, get_precision.c, get_size.c: Files responsible for extracting formatting information (flags, width, precision, size) from the format string.
print_handling.c: Contains the logic for calling the appropriate function to handle each format specifier.
useful_check.c: Utility functions used throughout the project (e.g., character checks, conversion functions).
write_handling.c: Functions for writing formatted data to the output buffer.
## Header File:
main.h: Header file containing function prototypes, constant definitions, and struct declarations.
Usage
To use the custom new_printf function in your C program, include the "main.h" header and call _printf with your desired format string and arguments, just like you would with the standard printf function.
