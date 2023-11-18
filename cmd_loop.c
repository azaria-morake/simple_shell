/**
 * cmd_looper - Bash prompt.
 * @obj1: Parameter.
 * @obj2: Arg object.
 *
 * Return: 0 on success, 1 on failure or err.
 */

#include "shell.h"

int cmd_looper(info_t *obj1, char **obj2)
{
  ssize_t x = 0;
  int builtin_return = 0;

  while (x != -1 && builtin_return != -2)
    {
      clr_data(obj1);
      if (reactive(obj1))
	c_puts("$ ");
      c_putchar(BUFFER_FLUSH);
      x = _input(obj1);
      if (x != -1)
	{
	  stage_data(obj1, obj2);
	  builtin_return = builtin_finder(obj1);
	  if (builtin_return == -1)
	    cmd_finder(obj1);
	}
      else if (reactive(obj1))
	c_putchar('\n');
      clr_data(obj1, 0);
    }
  record_hist(obj1);
  clr_data(obj1, 1);
  if (!reactive(obj1) && obj1->condition)
    exit(obj1->condition);
  if (builtin_return == -2)
    {
      if (obj1->exits_err == -1)
	exit(obj1->condition);
      exit(obj1->exits_err);
    }
  return (builtin_return);
}

/**
 * builtin_finder - Finds builtin cmd.
 * @obj: Parameter struct.
 *
 * Return: -1 if builtin != found.
 * 0 if builtin == success.
 * 1 if builtin found but != success.
 * -2 if builtin exits.
 */
int builtin_finder(info_t *obj1)
{
  int x, built_in_return = -1;
  builtin_table builtin_tbl[] = {
    {"exit", c_esc},
    {"env", myhabitat},
    {"help", mayday},
    {"history", my_hist},
    {"setenv", set_myhabitat},
    {"unsetenv", unset_myhabitat},
    {"cd", c_cmd},
    {"alias", my_nic},
    {NULL, NULL}
  };

  for (x = 0; builtin_tbl[i].type; x++)
    if (str_cmp(obj1->arg_v[0], builtin_tbl[i].type) == 0)
      {
	obj1->ln_count++;
	built_in_return = builtin_tbl[x].func(obj1);
	break;
      }
  return (built_in_return);
}

/**
 * cmd_finder- Finds cmd in PATH.
 * @obj1: Parameter.
 *
 * Return: expects no return.
 */

void cmd_finder(info_t *obj1)
{
  char *passage = NULL;
  int x, y;

  obj1->cmd_path = obj1->arg_v[0];
  if (obj1->ln_flag == 1)
    {
      obj1->ln_count++;
      obj1->ln_flag = 0;
    }
  for (x = 0, y = 0; obj1->ar_g[x]; x++)
    if (!c_delimiter(obj1->ar_g[x], " \t\n"))
      y++;
  if (!y)
    return;

  passage = path_finder(obj1, habitat2(obj1, "PATH="), obj1->arg_v[0]);
  if (passage)
    {
      obj1->cmd_path = passage;
      cmd_fork(obj1);
    }
  else
    {
      if ((reactive(obj1) || habitat2(obj1, "PATH=")
	   || obj->arg_v[0][0] == '/') && cmd(obj1, obj1->arg_v[0]))
	cmd_fork(obj1);
      else if (*(obj1->ar_g) != '\n')
	{
	  obj1->condition = 127;
	  display_err(obj1, "Unknown\n");
	}
    }
}

/**
 * cmd_fork - Invokes exec.
 * @obj1: Parameter.
 *
 * Return: expects no return.
 */

void cmd_fork(info_t *obj1)
{
  pid_t kid_pid;

  kid_pid = fork();
  if (kid_pid == -1)
    {
      /* TODO: PUT ERROR FUNCTION */
      perror("Error:");
      return;
    }
  if (kid_pid == 0)
    {
      if (execve(obj1->cmd_path, obj1->arg_v, habitat(obj1)) == -1)
	{
	  rm_data(obj1, 1);
	  if (errno == EACCES)
	    exit(126);
	  exit(1);
	}
      /* TODO: PUT ERROR FUNCTION */
    }
  else
    {
      wait(&(obj1->condition));
      if (WIFEXITED(obj1->condition))
	{
	  obj1->condition = WEXITSTATUS(obj1->condition);
	  if (obj1->condition == 126)
	    display_err(info, "Restricted\n");
	}
    }
}
