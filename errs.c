#include "shell.h"

/**
 * c_puts2 - Captures str input.
 * @str: String to be printed.
 *
 * Return: 0.
 */
void c_puts2(char *str)
{
  int i = 0;

  if (!str)
    return;
  while (str[i] != '\0')
    {
      c_putchar2(str[i]);
      i++;
    }
}

/**
 * c_putchar2 - Char to stderr.
 * @c: Char.
 *
 * Return: On success 1.
 * On error, -1 is returned, errno appropriately set.
 */
int c_putchar2(char c)
{
  static int i;
  static char buf[WRITE_BUFFER_SIZE];

  if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
      write(2, buf, i);
      i = 0;
    }
  if (c != BUFFER_FLUSH)
    buf[i++] = c;
  return (1);
}

/**
 * c_put - Filedescriptor char assignment.
 * @c: Char to be written.
 * @fd: The filedescriptor.
 *
 * Return: On success 1.
 * On error, -1 is returned, errno appropriately set.
 */
int c_put(char c, int fd)
{
  static int i;
  static char buf[WRITE_BUFFER_SIZE];

  if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
      write(fd, buf, i);
      i = 0;
    }
  if (c != BUFFER_FLUSH)
    buf[i++] = c;
  return (1);
}

/**
 * c_puts - Prints std input str.
 * @str: String.
 * @fd: Std input copy filedescriptor.
 *
 * Return: Number of chars.
 */
int c_putsfd(char *str, int fd)
{
  int i = 0;

  if (!str)
    return (0);
  while (*str)
    {
      i += c_put(*str++, fd);
    }
  return (i);
}
