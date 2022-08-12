#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>

void my_printf(const char *, ...);
void my_vprintf(const char *, va_list);
void print_string(char *);
void number_to_string(int64_t, int, char *);

int main()
{
	uint64_t n = (uint64_t) - 1;
	char *ptr = "hello";
	void (*ptr_func)(char *) = print_string;
	my_printf("Characters: %c %c done.\n", 'a', 65);
	my_printf("Decimals: %d\n %d done\n", 1977, 650000L);
	my_printf("Some different radicals: %d, %x, %x done.\n", 100, 100, 1000000000);
	my_printf("%s \n", "Alx is Amaizing");
	my_printf("testing with pointer: %p, %p, %d, %x\n",ptr_func, ptr, n, n);
	my_printf("testing other possible integer: %d, %d\n",INT_MAX, INT_MIN);

	return (0);
}

void my_printf(const char *format, ...)
{
	va_list args;

	va_start(args, format);
	my_vprintf(format, args);
	va_end(args);
}

void my_vprintf(const char *format, va_list args)
{
	int state = 0; //if it is not a format specifier
	char buffer[65];
	//printf("alx %c is %% cool %d sdjdslmf",'y', 2567)
	while (*format)
	{
		if (state == 0)
		{
			if (*format == '%')
				state = 1;
			else
				putchar(*format);
		}
		else //it is a format specifier
		{
			switch (*format)
			{
				case 'd':
				{	
					int n = va_arg(args, int);
					number_to_string(n, 10, buffer);
					print_string(buffer);
					break;
				}
				case 'c':
				{
					char ch = va_arg(args, int);
					putchar(ch);
					break;
				}
				case 'x':
				{
					int n = va_arg(args, int);
					number_to_string(n, 16, buffer);
					print_string(buffer);
					break;
				}
				case 's':
				{
					char *s = va_arg(args, char *);
					print_string(s);
					break;
				 }
				case 'p':
				{
					putchar('0');
					putchar('x');
					int n = va_arg(args, int);
					number_to_string(n, 16, buffer);
					print_string(buffer);
					break;
				}
				case '%':
				{
					putchar('%');
					break;
				}		
			}
			state = 0;
		}

		format++;
	}

}
void print_string(char *s)
{
	while(*s)
		putchar(*s++);
}
void number_to_string(int64_t number, int base, char *buf)
{
	int i = 0, j;
	char tmp[65];
	if (number < 0)
	{
		buf[0] = '-';
		number *= -1;
	}

	if (number == 0)
	{
		*buf++ = '0';
		*buf = '\0';
		return;
	}
	while (number)
	{
		int rem = number % base;
		if (rem >= 10)
			tmp[i++] = 'a' + (rem - 10);
		else
			tmp[i++] = '0' + rem;

		number /= base;
	}

	for (j = i - 1; j >= 0; j--)
		*buf++ = tmp[j];
	*buf = '\0';
}




