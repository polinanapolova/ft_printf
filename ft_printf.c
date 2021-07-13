#include "ft_printf.h"

// Specifier: "%[width][flags][.precision][length]specifier", e.g. printf("%10# .5lld", -345);
// cspdiuxX%
int ft_printf_internal(const char *format, va_list *ap)
{
    int length;

    length = 0;
    if (*format == 'c')
    {
        char c = va_arg(*ap, int);
        length += write(1, &c, 1);
    }
    else if (*format == 's')
    {
        char *s = va_arg(*ap, char *);
        length += printf("%s", s);
    }
    else if (*format == 'p') // "0x" + putnbr(p); 
    {
        void *p = va_arg(*ap, void *);
        length += printf("%p", p);
    }
    else if (*format == 'd' || *format == 'i')
    {
        int n = va_arg(*ap, int);
        length += printf("%d", n);
    }
    else if (*format == 'u')
    {
        unsigned int n = va_arg(*ap, unsigned int);
        length += printf("%u", n);
    }
    else if (*format == 'x') // Must be unsigned
    {
        unsigned int n = va_arg(*ap, unsigned int);
        length += printf("%x", n);
    }
    else if (*format == 'X')
    {
        unsigned int n = va_arg(*ap, unsigned int);
        length += printf("%X", n);
    }
    else if (*format == '%')
    {
        length += write(1, "%", 1);
    }
    else
    {
        //  handle cases such as ft_printf("%q");
    }
    return (length);
}

int ft_printf(const char *format, ...)
{
    int     length;
    va_list ap;

    length = 0;
    va_start(ap, format);
    while (*format != '\0')
    {
        if (*format == '%')
        {
            length += ft_printf_internal(++format, &ap);
            format++;
        }
        else
        {
            length += write(1, format++, 1);
        }
    }
    va_end(ap);
    return (length);
}

int main()
{
    int ft_i = 0, i = 0;

    ft_i = ft_printf("Hello, %s! I am %d years old\n", "Artem", 3);
    i = printf("Hello, %s! I am %d years old\n", "Artem", 3);
    
    printf("%d\t%d\n", ft_i, i);
    return (0);
}
