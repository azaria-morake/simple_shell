#include "shell.h"

/**
 * set_mem - Sets up memory.
 * @s: Pointer.
 * @b: Byte to set.
 * @n: Amount of bytes.
 * Return: s.
 */
char *set_mem(char *s, char b, unsigned int n)
{
  unsigned int i;

  for (i = 0; i < n; i++)
    s[i] = b;
  return (s);
}

/**
 * _release - Clears str of str.
 * @pp: Strings
 */
void _release(char **pp)
{
  char **a = pp;

  if (!pp)
    return;
  while (*pp)
    free(*pp++);
  free(a);
}

/**
 * c_realloc - Restores memory block.
 * @ptr: Points to recent most malloc block.
 * @old_size: Most recent block size in bytes.
 * @new_size: New block size in bytes.
 *
 * Return: Pointer to old block.
 */
void *c_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
  char *p;

  if (!ptr)
    return (malloc(new_size));
  if (!new_size)
    return (free(ptr), NULL);
  if (new_size == old_size)
    return (ptr);

  p = malloc(new_size);
  if (!p)
    return (NULL);

  old_size = old_size < new_size ? old_size : new_size;
  while (old_size--)
    p[old_size] = ((char *)ptr)[old_size];
  free(ptr);
  return (p);
}
