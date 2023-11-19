#include "shell.h"

/**
 * c_esc - Esc bash.
 * @obj1: Struc contains possible arguments.
 *
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int c_esc(info_t *obj1)
{
  int exit_check;

  if (obj1->arg_v[1])  /* If there is an exit arguement */
    {
      exit_check = errtoint(obj1->arg_v[1]);
      if (exit_check == -1)
	{
	  obj1->condition = 2;
	  display_err(obj1, "Invalid number: ");
	  c_puts2(obj1->arg_v[1]);
	  c_putchar2('\n');
	  return (1);
	}
      obj1->exits_err = errtoint(obj1->arg_v[1]);
      return (-2);
    }
  obj1->exits_err = -1;
  return (-2);
}

/**
 * c_cmd - Changes current directory.
 * @obj1: Structure containing potential arguments.
 *
 *  Return: Always 0.
 */
int c_cmd(info_t *obj1)
{
  char *s, *dir, buffer[1024];
  int chdir_ret;

  s = getcwd(buffer, 1024);
  if (!s)
    c_puts("TODO: >>getcwd failure message here<<\n");
  if (!obj1->arg_v[1])
    {
      dir = habitat2(obj1, "HOME=");
      if (!dir)
	chdir_ret = /* TODO: what should this be? */
	  chdir((dir = habitat2(obj1, "PWD=")) ? dir : "/");
      else
	chdir_ret = chdir(dir);
    }
  else if (c_strcmp(obj1->arg_v[1], "-") == 0)
    {
      if (!habitat2(obj1, "OLDPWD="))
	{
	  c_puts(s);
	  c_putchar2('\n');
	  return (1);
	}
      c_puts(habitat2(obj1, "OLDPWD=")), c_putchar2('\n');
      chdir_ret = /* TODO: what should this be? */
	chdir((dir = habitat2(obj1, "OLDPWD=")) ? dir : "/");
    }
  else
    chdir_ret = chdir(obj1->arg_v[1]);
  if (chdir_ret == -1)
    {
      display_err(obj1, "Unable to change directory ");
      c_puts2(obj1->arg_v[1]), c_putchar2('\n');
    }
  else
    {
      habitat_set(obj1, "OLDPWD", habitat2(obj1, "PWD="));
      habitat_set(obj1, "PWD", getcwd(buffer, 1024));
    }
  return (0);
}

/**
 * mayday - changes the current directory.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int mayday(info_t *info)
{
  char **arg_array;

  arg_array = info->arg_v;
  c_puts("Success. Function not yet implemented \n");
  if (0)
   c_puts(*arg_array);
  return (0);
}
