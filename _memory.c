#include "shell.h"

/**
 * release - Clear pointer.
 * @ptr: Pointer index.
 *
 * Return: 1 if freed, or if else 0.
 */
int release(void **ptr)
{
  if (ptr && *ptr)
    {
      free(*ptr);
      *ptr = NULL;
      return (1);
    }
  return (0);
}
