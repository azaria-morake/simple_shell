#include "shell.h"

/**
 * habitat - Environment string array.
 * @info: Structure containing potential arguments.
 *
 * Return: 0.
 */
char **habitat(info_t *info)
{
  if (!info->environ || info->home_mod)
    {
      info->environ = ls_to_str(info->_home);
      info->env_changed = 0;
    }

  return (info->environ);
}

/**
 * habitat_unset - Reset environment var.
 * @info: Structure containing potential arguments.
 *
 *  Return: 1 on delete or 0.
 * @var: Environment string.
 */
int habitat_unset(info_t *info, char *var)
{
  list_t *node = info->_home;
  size_t i = 0;
  char *p;

  if (!node || !var)
    return (0);

  while (node)
    {
      p = node_entry(node->str, var);
      if (p && *p == '=')
	{
	  info->home_mod = rm_index_node(&(info->_home), i);
	  i = 0;
	  node = info->_home;
	  continue;
	}
      node = node->nxt;
      i++;
    }
  return (info->home_mod);
}

/**
 * habitat_set - New env var/mode existing.
 * @info: Structure containing potential arguments.
 * @var: String env var.
 * @value: Value of string env var.
 *  Return: 0.
 */
int habitat_set(info_t *info, char *var, char *value)
{
  char *buf = NULL;
  list_t *node;
  char *p;

  if (!var || !value)
    return (0);

  buf = malloc(c_strlen(var) + c_strlen(value) + 2);
  if (!buf)
    return (1);
  c_strcpy(buf, var);
  c_strcat(buf, "=");
  c_strcat(buf, value);
  node = info->_home;
  while (node)
    {
      p = node_entry(node->str, var);
      if (p && *p == '=')
	{
	  free(node->str);
	  node->str = buf;
	  info->home_mod = 1;
	  return (0);
	}
      node = node->nxt;
    }
  app_node_term(&(info->_home), buf, 0);
  free(buf);
  info->home_mod = 1;
  return (0);
}

