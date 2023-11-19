#include "shell.h"

/**
 * c_strcpy - cp str.
 * @dest: End point.
 * @src: Source point.
 *
 * Return: End pointer.
 */
char *c_strcpy(char *dest, char *src)
{
  int i = 0;

  if (dest == src || src == 0)
    return (dest);
  while (src[i])
    {
      dest[i] = src[i];
      i++;
    }
  dest[i] = 0;
  return (dest);
}

/**
 * c_strdup - Duplicates a str.
 * @str: String in question.
 *
 * Return: Duplicate str pointer.
 */
char *c_strdup(const char *str)
{
  int length = 0;
  char *ret;

  if (str == NULL)
    return (NULL);
  while (*str++)
    length++;
  ret = malloc(sizeof(char) * (length + 1));
  if (!ret)
    return (NULL);
  for (length++; length--;)
    ret[length] = *--str;
  return (ret);
}

/**
 *c_puts - Std input str.
 *@str: String in question.
 *
 * Return: 0.
 */
void c_puts(char *str)
{
  int i = 0;

  if (!str)
    return;
  while (str[i] != '\0')
    {
      c_putchar(str[i]);
      i++;
    }
}

/**
 * c_putchar - Char c to stdout.
 * @c: Char in question.
 *
 * Return: On success 1.
 * On error, -1 is returned, errno set appropriately.
 */
int c_putchar(char c)
{
  static int i;
  static char buf[WRITE_BUFFER_SIZE];

  if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
      write(1, buf, i);
      i = 0;
    }
  if (c != BUFFER_FLUSH)
    buf[i++] = c;
  return (1);
}
