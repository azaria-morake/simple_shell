#include "shell.h"

/**
 * myhabitat - prints the current env
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int myhabitat(info_t *info)
{
  display_ls_str(info->usr_env);
  return (0);
}

/**
 * habitat2 - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *habitat2(info_t *info, const char *name)
{
  list_t *node = info->usr_env;
  char *p;

  while (node)
    {
      p = starts_(node->str, name);
      if (p && *p)
	return (p);
      node = node->next;
    }
  return (NULL);
}

/**
 * set_myhabitat - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
  if (info->arg_c != 3)
    {
      c_puts2("No. of arguments invalid.\n");
      return (1);
    }
  if (habitat_set(info, info->arg_v[1], info->arg_v[2]))
    return (0);
  return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int set_myhabitat(info_t *info)
{
  int i;

  if (info->arg_c == 1)
    {
      c_puts2("Insufficient number of arguments..\n");
      return (1);
    }
  for (i = 1; i <= info->arg_c; i++)
    habitat_unset(info, info->arg_v[i]);

  return (0);
}

/**
 * group_habitat_ls - Populates env linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int group_habitat_ls(info_t *info)
{
  list_t *node = NULL;
  size_t i;

  for (i = 0; _home[i]; i++)
    add_node_end(&node, _home[i], 0);
  info->usr_env = node;
  return (0);
}
