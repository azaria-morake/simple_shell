#include "shell.h"

/**
 * app_node - Adds a new node.
 * @head: Pointer.
 * @str: strING field.
 * @num: History node index.
 *
 * Return: size of ls.
 */
list_t *app_node(list_t **head, const char *str, int num)
{
  list_t *new_head;

  if (!head)
    return (NULL);
  new_head = malloc(sizeof(list_t));
  if (!new_head)
    return (NULL);
  set_mem((void *)new_head, 0, sizeof(list_t));
  new_head->_number = num;
  if (str)
    {
      new_head->str = c_strdup(str);
      if (!new_head->str)
	{
	  free(new_head);
	  return (NULL);
	}
    }
  new_head->nxt = *head;
  *head = new_head;
  return (new_head);
}

/**
 * app_node_term - Adds a node.
 * @head: Pointer.
 * @str: String field.
 * @num: History node index.
 *
 * Return: size of ls.
 */
list_t *app_node_term(list_t **head, const char *str, int num)
{
  list_t *new_node, *node;

  if (!head)
    return (NULL);

  node = *head;
  new_node = malloc(sizeof(list_t));
  if (!new_node)
    return (NULL);
  set_mem((void *)new_node, 0, sizeof(list_t));
  new_node->_number = num;
  if (str)
    {
      new_node->str = c_strdup(str);
      if (!new_node->str)
	{
	  free(new_node);
	  return (NULL);
	}
    }
  if (node)
    {
      while (node->nxt)
	node = node->nxt;
      node->nxt = new_node;
    }
  else
    *head = new_node;
  return (new_node);
}

/**
 * display_ls_str - Prints the str element of a list_t.
 * @h: Points to the first node.
 *
 * Return: size of ls.
 */
size_t display_ls_str(const list_t *h)
{
  size_t i = 0;

  while (h)
    {
      c_puts(h->str ? h->str : "(nil)");
      c_puts("\n");
      h = h->nxt;
      i++;
    }
  return (i);
}

/**
 * rm_index_node - Removes node at index.
 * @head: Pointer.
 * @index: Node index.
 *
 * Return: 1 on success, 0 in failure.
 */
int rm_index_node(list_t **head, unsigned int index)
{
  list_t *node, *prev_node;
  unsigned int i = 0;

  if (!head || !*head)
    return (0);

  if (!index)
    {
      node = *head;
      *head = (*head)->nxt;
      free(node->str);
      free(node);
      return (1);
    }
  node = *head;
  while (node)
    {
      if (i == index)
	{
	  prev_node->nxt = node->nxt;
	  free(node->str);
	  free(node);
	  return (1);
	}
      i++;
      prev_node = node;
      node = node->nxt;
    }
  return (0);
}

/**
 * free_ls - Frees all nodes from a list.
 * @head_ptr: Points to head node.
 *
 * Return: void.
 */
void free_ls(list_t **head_ptr)
{
  list_t *node, *next_node, *head;

  if (!head_ptr || !*head_ptr)
    return;
  head = *head_ptr;
  node = head;
  while (node)
    {
      next_node = node->nxt;
      free(node->str);
      free(node);
      node = next_node;
    }
  *head_ptr = NULL;
}
