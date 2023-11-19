/**
 * loop - Verify if the current buffer char is a chain delimiter.
 * @obj1: Parameter structure.
 * @obj2: Character variable buffer.
 * @obj3: Current buffer position address.
 *
 * Return: 1 on success, 0 on failure.
 */

#include "shell.h"

int loop(info_t *obj1, char *obj2, size_t *obj3)
{
  size_t x = *obj3;

  if (obj2[x] == '|' && obj2[x + 1] == '|')
    {
      obj2[x] = 0;
      x++;
      obj1->cmd_race = C_CMD_OR;
    }
  else if (obj2[x] == '&' && obj2[x + 1] == '&')
    {
      obj2[x] = 0;
      x++;
      obj1->cmd_race = C_CMD_AND;
    }
  else if (obj2[x] == ';') /* found end of this command */
    {
      obj2[x] = 0; /* replace semicolon with null */
      obj1->cmd_race = CMD_LOOP;
    }
  else
    return (0);
  *obj3 = x;
  return (1);
}

/**
 * inspect_loop - Check if chaining should continue based on the last status.
 * @obj1: Parameter structure.
 * @obj2: Character buffer.
 * @obj3: Buffer current position address.
 * @x: Initial buffer position.
 * @length: Buffer length.
 *
 * Return: Expects no return.
 */
void inspect_loop(info_t *obj1, char *obj2, size_t *obj3, size_t x, size_t length)
{
  size_t xx = *obj3;

  if (obj1->cmd_race == C_CMD_AND)
    {
      if (obj1->condition)
	{
	  obj2[x] = 0;
	  xx = length;
	}
    }
  if (obj1->cmd_race == C_CMD_OR)
    {
      if (!obj1->condition)
	{
	  obj2[x] = 0;
	  xx = length;
	}
    }

  *obj3 = xx;
}

/**
 * rm_nic - Substitute aliases in the tokenized string.
 * @obj1: Parameter structure.
 *
 * Return: 1 on success, 0 on failure.
 */
int rm_nic(info_t *obj1)
{
  int x;
  list_t *struct_node;
  char *obj2;

  for (x = 0; x < 10; x++)
    {
      struct_node = node_entry(obj1->nic, obj1->arg_v[0], '=');
      if (!struct_node)
	return (0);
      free(obj1->arg_v[0]);
      obj2 = str2chr(struct_node->str, '=');
      if (!obj2)
	return (0);
      obj2 = c_strdup(obj2 + 1);
      if (!obj2)
	return (0);
      obj1->arg_v[0] = obj2;
    }
  return (1);
}

/**
 * rm_vrs - Replaces vars in str token.
 * @info: Parameter struct.
 *
 * Return: 1 if replaced, 0 if failed.
 */
int rm_vrs(info_t *info)
{
  int i = 0;
  list_t *node;

  for (i = 0; info->arg_v[i]; i++)
    {
      if (info->arg_v[i][0] != '$' || !info->arg_v[i][1])
	continue;

      if (!c_strcmp(info->arg_v[i], "$?"))
	{
	  rm_str(&(info->arg_v[i]),
			 c_strdup(num_converter(info->condition, 10, 0)));
	  continue;
	}
      if (!c_strcmp(info->arg_v[i], "$$"))
	{
	  rm_str(&(info->arg_v[i]),
			 c_strdup(num_converter(getpid(), 10, 0)));
	  continue;
	}
      node = node_entry(info->usr_env, &info->arg_v[i][1], '=');
      if (node)
	{
	  rm_str(&(info->arg_v[i]),
			 c_strdup(str2chr(node->str, '=') + 1));
	  continue;
	}
      rm_str(&info->arg_v[i], c_strdup(""));

    }
  return (0);
}

/**
 * rm_str - Replaces string.
 * @old: Address of old string.
 * @new: New string
 *
 * Return: 1 on sucess or else 0.
 */
int rm_str(char **old, char *new)
{
  free(*old);
  *old = new;
  return (1);
}
