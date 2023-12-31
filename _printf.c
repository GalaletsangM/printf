#include "main.h"

/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
    int printed_chars = 0;
    va_list args;
    char buffer[BUFF_SIZE];
    int buff_ind = 0;

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
            {
                write(1, buffer, buff_ind);
                buff_ind = 0;
            }
            printed_chars++;
        }
        else
        {
            if (buff_ind > 0)
            {
                write(1, buffer, buff_ind);
                buff_ind = 0;
            }

            int flags = get_flags(format, &i);
            int width = get_width(format, &i, args);
            int precision = get_precision(format, &i, args);
            int size = get_size(format, &i);
            i++;

            int printed = handle_print(format, &i, args, buffer,
                                        flags, width, precision, size);

            if (printed == -1)
            {
                va_end(args);
                return (-1);
            }

            printed_chars += printed;
        }
    }

    if (buff_ind > 0)
        write(1, buffer, buff_ind);

    va_end(args);

    return (printed_chars);
}
