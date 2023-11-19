#include "shell.h"

/**
 * errtoint - Str to int.
 * @s: String.
 * Return: 0 if string != numbers. Convert num otherwise.
 * -1 on error.
 */
int errtoint(char *s)
{
  int i = 0;
  unsigned long int result = 0;

  if (*s == '+')
    s++;
  for (i = 0;  s[i] != '\0'; i++)
    {
      if (s[i] >= '0' && s[i] <= '9')
	{
	  result *= 10;
	  result += (s[i] - '0');
	  if (result > INT_MAX)
	    return (-1);
	}
      else
	return (-1);
    }
  return (result);
}

/**
 * display_err - Prints std err.
 * @info: Parameter & return info struct.
 * @estr: String.
 * Return: 0 if string != numbers, num convert otherwise.
 * -1 on error
 */
void display_err(info_t *info, char *estr)
{
  c_puts2(info->fl_name);
  c_puts2(": ");
  display_errd(info->ln_count, STDERR_FILENO);
  c_puts2(": ");
  c_puts2(info->arg_v[0]);
  c_puts2(": ");
  c_puts2(estr);
}

/**
 * display_errd - Prints dec in base 10.
 * @input: Usr input.
 * @fd: Filedescriptor.
 *
 * Return: number of chars.
 */
int display_errd(int input, int fd)
{
  int (*__putchar)(char) = c_putchar;
  int i, count = 0;
  unsigned int _abs_, current;

  if (fd == STDERR_FILENO)
    __putchar = c_putchar2;
  if (input < 0)
    {
      _abs_ = -input;
      __putchar('-');
      count++;
    }
  else
    _abs_ = input;
  current = _abs_;
  for (i = 1000000000; i > 1; i /= 10)
    {
      if (_abs_ / i)
	{
	  __putchar('0' + current / i);
	  count++;
	}
      current %= i;
    }
  __putchar('0' + current);
  count++;

  return (count);
}

/**
 * num_converter - Converts nums.
 * @num: Number to be converted.
 * @base: Num in base 10.
 * @flags: Argument flags.
 *
 * Return: string.
 */
char *num_converter(long int num, int base, int flags)
{
  static char *array;
  static char buffer[50];
  char sign = 0;
  char *ptr;
  unsigned long n = num;

  if (!(flags & UNSIGNED2_CONV) && num < 0)
    {
      n = -num;
      sign = '-';

    }
  array = flags & LOWERCASE1_CONV ? "0123456789abcdef" : "0123456789ABCDEF";
  ptr = &buffer[49];
  *ptr = '\0';

  do{
    *--ptr = array[n % base];
    n /= base;
  } while (n != 0);

  if (sign)
    *--ptr = sign;
  return (ptr);
}

/**
 * rm_coms - Removes pre-defined comments.
 * @buf: String address.
 *
 * Return: Always 0;
 */
void rm_coms(char *buf)
{
  int i;

  for (i = 0; buf[i] != '\0'; i++)
    if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
      {
	buf[i] = '\0';
	break;
      }
}
