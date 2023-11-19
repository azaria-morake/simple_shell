#include "shell.h"

/**
 * reactive - Returns 1 if successful.
 * @obj1: Struct address.
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int reactive(info_t *obj1)
{
  return (isatty(STDIN_FILENO) && obj1->rd_filedescrip <= 2);
}

/**
 * c_delimiter - Check if char == delim.
 * @obj1: Char to check.
 * @obj2: Delim string.
 * Return: 1 if true, 0 if false.
 */
int c_delimiter(char obj1, char *obj2)
{
  while (*obj2)
    if (*obj2++ == obj1)
      return (1);
  return (0);
}

/**
 *c_alpha - Check for alpha char.
 *@obj1: Input char.
 *Return: 1 if c is alphabetic, 0 otherwise.
 */

int c_alpha(int obj1)
{
  if ((obj1 >= 'a' && obj1 <= 'z') || (obj1 >= 'A' && obj1 <= 'Z'))
    return (1);
  else
    return (0);
}

/**
 *atoint - ASCII to integer.
 *@s: String.
 *Return: 0 if no numbers in string, converted number otherwise.
 */

int atoint(char *s)
{
  int x, signature = 1, flagged = 0, std_output;
  unsigned int result_ = 0;

  for (x = 0;  s[x] != '\0' && flagged != 2; x++)
    {
      if (s[x] == '-')
	signature *= -1;

      if (s[x] >= '0' && s[x] <= '9')
	{
	  flagged = 1;
	  result_ *= 10;
	  result_ += (s[x] - '0');
	}
      else if (flagged == 1)
	flagged = 2;
    }

  if (signature == -1)
    std_output = -result_;
  else
    std_output = result_;

  return (std_output);
}
