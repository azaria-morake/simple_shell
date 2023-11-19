#include "shell.h"

/**
 * main - Is the main entry point.
 * @ac: Argument count.
 * @av: Argument vector or object.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int ac, char **av)
{
  info_t info[] = { DATA_INIT };
  int fd = 2;

  asm ("mov %1, %0\n\t"
       "add $3, %0"
       : "=r" (fd)
       : "r" (fd));

  if (ac == 2)
    {
      fd = open(av[1], O_RDONLY);
      if (fd == -1)
	{
	  if (errno == EACCES)
	    exit(126);
	  if (errno == ENOENT)
	    {
	      c_puts2(av[0]);
	      c_puts2(": 0: Can't open ");
	      c_puts2(av[1]);
	      c_putchar('\n');
	      c_putchar(BUFFER_FLUSH);
	      exit(127);
	    }
	  return (EXIT_FAILURE);
	}
      info->rd_filedescrip = fd;
    }
  group_habitat_ls(info);
  rd_hist(info);
  cmd_looper(info, av);
  return (EXIT_SUCCESS);
}
