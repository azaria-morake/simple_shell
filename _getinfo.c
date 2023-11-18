#include "shell.h"

/**
 * clr_data - Clears data.
 * @info: Clearance address.
 */
void clr_data(info_t *info)
{
  info->ar_g = NULL;
  info->arg_v = NULL;
  info->cmd_path = NULL;
  info->arg_c = 0;
}

/**
 * stage_data - Sets data.
 * @info: Index.
 * @av: Argument vector.
 */
void stage_data(info_t *info, char **av)
{
  int i = 0;

  info->fl_name = av[0];
  if (info->ar_g)
    {
      info->arg_v = token1(info->ar_g, " \t");
      if (!info->arg_v)
	{
	  info->arg_v = malloc(sizeof(char *) * 2);
	  if (info->arg_v)
	    {
	      info->arg_v[0] = c_strdup(info->ar_g);
	      info->arg_v[1] = NULL;
	    }
	}
      for (i = 0; info->arg_v && info->arg_v[i]; i++)
	;
      info->arg_c = i;

      rm_nic(info);
      rm_vrs(info);
    }
}

/**
 * rm_data - Frees data struct fields.
 * @info: Data struct address.
 * @all: True for all freed fields.
 */
void rm_data(info_t *info, int all)
{
  _release(info->arg_v);
  info->arg_v = NULL;
  info->cmd_path = NULL;
  if (all)
    {
      if (!info->cmd_bufferer)
	free(info->ar_g);
      if (info->_home)
	free_ls(&(info->_home));
      if (info->hist_node)
	free_ls(&(info->hist_node));
      if (info->nic)
	free_ls(&(info->nic));
      _release(info->environ);
      info->environ = NULL;
      release((void **)info->cmd_bufferer);
      if (info->rd_filedescrip > 2)
	close(info->rd_filedescrip);
      c_putchar(BUFFER_FLUSH);
    }
}

