#include "shell.h"

/**
 * my_hist - displays the history list.
 *
 * @info: Structure containing potential arguments.
 *
 *  Return: 0.
 */
int my_hist(info_t *info)
{
  list_display(info->hist_node);
  return (0);
}

/**
 * unset_alias - Sets alias to string.
 * @info: Parameter struct.
 * @str: String for alias/nic.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
  char *p, c;
  int ret;

  p = str2chr(str, '=');
  if (!p)
    return (1);
  c = *p;
  *p = 0;
  ret = rm_index_node(&(info->nic),
			     node_index(info->nic, node_entry(info->nic, str, -1)));
  *p = c;
  return (ret);
}

/**
 * set_alias - Sets alias to string.
 * @info: Parameter.
 * @str: String.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
  char *p;

  p = str2chr(str, '=');
  if (!p)
    return (1);
  if (!*++p)
    return (unset_alias(info, str));

  unset_alias(info, str);
  return (app_node_term(&(info->nic), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @obj1: Alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *obj1)
{
  char *p = NULL, *a = NULL;

  if (obj1)
    {
      p = str2chr(obj1->str, '=');
      for (a = obj1->str; a <= p; a++)
	c_putchar2(*a);
      c_putchar2('\'');
      c_puts(p + 1);
      c_puts("'\n");
      return (0);
    }
  return (1);
}

/**
 * my_nic - Carbon copy of builtin alias[slight differences]
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int my_nic(info_t *info)
{
  int i = 0;
  char *p = NULL;
  list_t *node = NULL;

  if (info->arg_c == 1)
    {
      node = info->nic;
      while (node)
	{
	  print_alias(node);
	  node = node->nxt;
	}
      return (0);
    }
  for (i = 1; info->arg_v[i]; i++)
    {
      p = str2chr(info->arg_v[i], '=');
      if (p)
	set_alias(info, info->arg_v[i]);
      else
	print_alias(node_entry(info->nic, info->arg_v[i], '='));
    }

  return (0);
}
