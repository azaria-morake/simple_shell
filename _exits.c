#include "shell.h"

/**
 * _strn_cpy - Copies str.
 * @destiny: String destination.
 * @strsrc: String origin.
 * @num: Number of chars to be copied.
 * Return: Concat string.
 */
char *_strn_cpy(char *destiny, char *strsrc, int num)
{
  int i, j;
  char *s = destiny;

  i = 0;
  while (strsrc[i] != '\0' && i < num - 1)
    {
      destiny[i] = strsrc[i];
      i++;
    }
  if (i < num)
    {
      j = i;
      while (j < num)
	{
	  destiny[j] = '\0';
	  j++;
	}
    }
  return (s);
}

/**
 * strn_cat - Concatenates strings.
 * @destiny: String 1.
 * @strsrc: String 2.
 * @num: Maxmimal bytes.
 * Return: Concatenated str.
 */
char *strn_cat(char *destiny, char *strsrc, int num)
{
  int i, j;
  char *s = destiny;

  i = 0;
  j = 0;
  while (destiny[i] != '\0')
    i++;
  while (strsrc[j] != '\0' && j < num)
    {
      destiny[i] = strsrc[j];
      i++;
      j++;
    }
  if (j < num)
    destiny[i] = '\0';
  return (s);
}

/**
 * str2chr - Finds char in str.
 * @str: Parsed str.
 * @_char: Char to find.
 *Return: s.
 */
char *str2chr(char *str, char _char)
{
  do {
    if (*str == _char)
      return (str);
  } while (*str++ != '\0');

  return (NULL);
}

