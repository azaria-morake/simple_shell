#include "shell.h"

/**
 * cmd - Checks if file is executable cmd.
 * @info: Data structure.
 * @path: File path.
 *
 * Return: 1 if == true, 0 elsewise.
 */
int cmd(info_t *info, char *path)
{
  struct stat st;

  (void)info;
  if (!path || stat(path, &st))
    return (0);

  if (st.st_mode & S_IFREG)
    {
      return (1);
    }
  return (0);
}

/**
 * duplicate_char - Multiplies chars.
 * @pathstr: PATH string.
 * @start: Entry index.
 * @stop: Terminal index.
 *
 * Return: Points to new buffer.
 */
char *duplicate_char(char *pathstr, int start, int stop)
{
  static char buf[1024];
  int i = 0, k = 0;

  for (k = 0, i = start; i < stop; i++)
    if (pathstr[i] != ':')
      buf[k++] = pathstr[i];
  buf[k] = 0;
  return (buf);
}

/**
 * path_finder - Locates cmd in the PATH string.
 * @info: Data structure.
 * @pathstr: PATH string.
 * @cmd: cmd to locate.
 *
 * Return: full path of cmd if found or NULL
 */
char *path_finder(info_t *info, char *pathstr, char *_cmd)
{
  int i = 0, curr_pos = 0;
  char *path;

  if (!pathstr)
    return (NULL);
  if ((c_strlen(_cmd) > 2) && starts_(_cmd, "./"))
    {
      if (cmd(info, _cmd))
	return (_cmd);
    }
  while (1)
    {
      if (!pathstr[i] || pathstr[i] == ':')
	{
	  path = duplicate_char(pathstr, curr_pos, i);
	  if (!*path)
	    c_strcat(path, _cmd);
	  else
	    {
	      c_strcat(path, "/");
	      c_strcat(path, _cmd);
	    }
	  if (cmd(info, path))
	    return (path);
	  if (!pathstr[i])
	    break;
	  curr_pos = i;
	}
      i++;
    }
  return (NULL);
}
