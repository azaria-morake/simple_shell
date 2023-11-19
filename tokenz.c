#include "shell.h"

/**
 * token1 - Breaks string into tokens.
 * @str: Std input.
 * @d: Delimiter.
 * Return: Pointer to string array,NULL in failure
 */

char **token1(char *str, char *d)
{
  int i, j, k, m, numwords = 0;
  char **s;

  if (str == NULL || str[0] == 0)
    return (NULL);
  if (!d)
    d = " ";
  for (i = 0; str[i] != '\0'; i++)
    if (!c_delimiter(str[i], d) && (c_delimiter(str[i + 1], d) || !str[i + 1]))
      numwords++;

  if (numwords == 0)
    return (NULL);
  s = malloc((1 + numwords) * sizeof(char *));
  if (!s)
    return (NULL);
  for (i = 0, j = 0; j < numwords; j++)
    {
      while (c_delimiter(str[i], d))
	i++;
      k = 0;
      while (!c_delimiter(str[i + k], d) && str[i + k])
	k++;
      s[j] = malloc((k + 1) * sizeof(char));
      if (!s[j])
	{
	  for (k = 0; k < j; k++)
	    free(s[k]);
	  free(s);
	  return (NULL);
	}
      for (m = 0; m < k; m++)
	s[j][m] = str[i++];
      s[j][m] = 0;
    }
  s[j] = NULL;
  return (s);
}

/**
 * *token2 - Breaks string into 2 tokens.
 * @str: Std input.
 * @d: Delimeter.
 * Return: Pointer to a string array, NULL in failure.
 */
char **token2(char *str, char d)
{
  int i, j, k, m, numwords = 0;
  char **s;

  if (str == NULL || str[0] == 0)
    return (NULL);
  for (i = 0; str[i] != '\0'; i++)
    if ((str[i] != d && str[i + 1] == d) ||
	(str[i] != d && !str[i + 1]) || str[i + 1] == d)
      numwords++;
  if (numwords == 0)
    return (NULL);
  s = malloc((1 + numwords) * sizeof(char *));
  if (!s)
    return (NULL);
  for (i = 0, j = 0; j < numwords; j++)
    {
      while (str[i] == d && str[i] != d)
	i++;
      k = 0;
      while (str[i + k] != d && str[i + k] && str[i + k] != d)
	k++;
      s[j] = malloc((k + 1) * sizeof(char));
      if (!s[j])
	{
	  for (k = 0; k < j; k++)
	    free(s[k]);
	  free(s);
	  return (NULL);
	}
      for (m = 0; m < k; m++)
	s[j][m] = str[i++];
      s[j][m] = 0;
    }
  s[j] = NULL;
  return (s);
}
