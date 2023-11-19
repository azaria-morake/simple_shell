#include "shell.h"

/**
 * ls_lenght - Linked list lenghth.
 * @h: Points to first nod.e
 *
 * Return: Size of ls.
 */
size_t ls_lenght(const list_t *h)
{
  size_t i = 0;

  while (h)
    {
      h = h->nxt;
      i++;
    }
  return (i);
}

/**
 * ls_to_str - Returns array of strings from list->str.
 * @head: Points to the first node.
 *
 * Return: String array.
 */
char **ls_to_str(list_t *head)
{
  list_t *node = head;
  size_t i = ls_lenght(head), j;
  char **strs;
  char *str;

  if (!head || !i)
    return (NULL);
  strs = malloc(sizeof(char *) * (i + 1));
  if (!strs)
    return (NULL);
  for (i = 0; node; node = node->nxt, i++)
    {
      str = malloc(c_strlen(node->str) + 1);
      if (!str)
	{
	  for (j = 0; j < i; j++)
	    free(strs[j]);
	  free(strs);
	  return (NULL);
	}

      str = c_strcpy(str, node->str);
      strs[i] = str;
    }
  strs[i] = NULL;
  return (strs);
}


/**
 * list_display - Prints linked list elements.
 * @h: Points to first node.
 *
 * Return: Size of ls.
 */
size_t list_display(const list_t *h)
{
  size_t i = 0;

  while (h)
    {
      c_puts(num_converter(h->_number, 10, 0));
      c_putchar(':');
      c_putchar(' ');
      c_puts(h->str ? h->str : "(nil)");
      c_puts("\n");
      h = h->nxt;
      i++;
    }
  return (i);
}

/**
 * node_entry - Entry node.
 * @node: Points to ls head.
 * @prefix: Matching string.
 * @c: Char to match.
 *
 * Return: Matching node or /0.
 */
list_t *node_entry(list_t *node, char *prefix, char c)
{
  char *p = NULL;

  while (node)
    {
      p = starts_(node->str, prefix);
      if (p && ((c == -1) || (*p == c)))
	return (node);
      node = node->nxt;
    }
  return (NULL);
}

/**
 * node_index - Gets index of nodes.
 * @head: Points to ls head.
 * @node: Points to node.
 *
 * Return: node index or -1.
 */
ssize_t node_index(list_t *head, list_t *node)
{
  size_t i = 0;

  while (head)
    {
      if (head == node)
	return (i);
      head = head->nxt;
      i++;
    }
  return (-1);
}
