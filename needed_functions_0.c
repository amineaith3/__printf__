#include "main.h"

int print_char(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char c = va_arg(types, int);
    return (handle_write_char(c, buffer, flags, width, precision, size));
}

int print_string(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    char *str = va_arg(types, char *);

    if (str == NULL)
        str = (precision >= 0 && precision < 6) ? "      " : "(null)";

    int length = (precision >= 0) ? strnlen(str, precision) : strlen(str);

    if (width > length)
    {
        if (flags & F_MINUS)
        {
            write(1, str, length);
            for (int i = width - length; i > 0; i--)
                write(1, " ", 1);
        }
        else
        {
            for (int i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, str, length);
        }
        return width;
    }

    return write(1, str, length);
}

int print_percent(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    UNUSED(types);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return write(1, "%%", 1);
}

int print_int(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    long int n = va_arg(types, long int);
    int is_negative = 0;
    n = convert_size_number(n, size);

    if (n < 0)
    {
        n = -n;
        is_negative = 1;
    }

    return write_number(is_negative, buffer, flags, width, precision, n);
}

int print_binary(va_list types, char buffer[],
    int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(types, unsigned int);
    unsigned int m = 2147483648; // (2 ^ 31)
    unsigned int a[32];
    int count = 0;

    for (int i = 0; i < 32; i++)
    {
        a[i] = n / m;
        m /= 2;
    }

    for (int i = 0, sum = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];
            write(1, &z, 1);
            count++;
        }
    }

    return count;
}

