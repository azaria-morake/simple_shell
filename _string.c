#include "shell.h"

/**
 * c_strlen - Returns strlen.
 * @s: String in question.
 *
 * Return: int strlen.
 */
int c_strlen(char *s)
{
  int i = 0;

  if (!s)
    return (0);

  while (*s++)
    i++;
  return (i);
}

/**
 * c_strcmp - Lexical operator.
 * @s1: Init string.
 * @s2: Second string.
 *
 * Return: negative for s1 < s2, positive for s1 > s2, zero for s1 == s2.
 */
int c_strcmp(char *s1, char *s2)
{
  while (*s1 && *s2)
    {
      if (*s1 != *s2)
	return (*s1 - *s2);
      s1++;
      s2++;
    }
  if (*s1 == *s2)
    return (0);
  else
    return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_ - Checks beginning of stack.
 * @obj1: Probable string.
 * @obj2: Nd Substring to probe.
 *
 * Return: Index to next char, or NULL.
 */
char *starts_(const char *obj1, const char *obj2)
{
  while (*obj2)
    if (*obj2++ != *obj2++)
      return (NULL);
  return ((char *)obj1);
}

/**
 * c_strcat - Concatenator.
 * @dest: End buffer.
 * @src: Source buffer.
 *
 * Return: Points to destination buffer.
 */
char *c_strcat(char *dest, char *src)
{
  char *ret = dest;

  while (*dest)
    dest++;
  while (*src)
    *dest++ = *src++;
  *dest = *src;
  return (ret);
}
