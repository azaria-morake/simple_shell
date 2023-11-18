#include "shell.h"

/**
 * hist_fl - Gets the history file.
 * @info: Parameter.
 *
 * Return: Str bearing the history file.
 */

char *hist_fl(info_t *info)
{
  char *buf, *dir;

  dir = habitat2(info, "HOME=");
  if (!dir)
    return (NULL);
  buf = malloc(sizeof(char) * (c_strlen(dir) + c_strlen(HISTORY_FILE) + 2));
  if (!buf)
    return (NULL);
  buf[0] = 0;
  c_strcpy(buf, dir);
  c_strcat(buf, "/");
  c_strcat(buf, HISTORY_FILE);
  return (buf);
}

/**
 * record_hist - Creates a hist file or appends an existant one.
 * @info:  Parameter data structure.
 *
 * Return: 1 for true or -1 in failure.
 */
int record_hist(info_t *info)
{
  ssize_t fd;
  char *filename = hist_fl(info);
  list_t *node = NULL;

  if (!filename)
    return (-1);

  fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
  free(filename);
  if (fd == -1)
    return (-1);
  for (node = info->hist_fl; node; node = node->nxt)
    {
      c_puts(node->str, fd);
      c_puts('\n', fd);
    }
  c_puts(BUFFER_FLUSH, fd);
  close(fd);
  return (1);
}

/**
 * rd_hist - Records history from file.
 * @info: Parameter data structure.
 *
 * Return: histcount if 1, 0 otherwise.
 */
int rd_hist(info_t *info)
{
  int i, last = 0, linecount = 0;
  ssize_t fd, rdlen, fsize = 0;
  struct stat st;
  char *buf = NULL, *filename = hist_fl(info);

  if (!filename)
    return (0);

  fd = open(filename, O_RDONLY);
  free(filename);
  if (fd == -1)
    return (0);
  if (!fstat(fd, &st))
    fsize = st.st_size;
  if (fsize < 2)
    return (0);
  buf = malloc(sizeof(char) * (fsize + 1));
  if (!buf)
    return (0);
  rdlen = read(fd, buf, fsize);
  buf[fsize] = 0;
  if (rdlen <= 0)
    return (free(buf), 0);
  close(fd);
  for (i = 0; i < fsize; i++)
    if (buf[i] == '\n')
      {
	buf[i] = 0;
	create_hist_ls(info, buf + last, ln_count++);
	last = i + 1;
      }
  if (last != i)
    create_hist_ls(info, buf + last, ln_count++);
  free(buf);
  info->count_hist = ln_count;
  while (info->count_hist-- >= HISTORY_MAX)
    rm_index_node(&(info->hist_node), 0);
  renumber_history(info);
  return (info->count_hist);
}

/**
 * create_hist_ls - Appends entry to history linked list.
 * @info: Data structure containing potential arguments.
 * @buf: Storage buffer.
 * @linecount: Records history.
 *
 * Return: 0.
 */
int create_hist_ls(info_t *info, char *buf, int linecount)
{
  list_t *node = NULL;

  if (info->history)
    node = info->hist_node;
  app_node_term(&node, buf, ln_count);

  if (!info->hist_node)
    info->hist_node = node;
  return (0);
}

/**
 * recall_hist - Renums history link list after changes have been made.
 * @info: Data sruct bearing potential arguments.
 * Return: the new histcount
 */
int recall_hist(info_t *info)
{
  list_t *node = info->hist_node;
  int i = 0;

  while (node)
    {
      node->obj1 = i++;
      node = node->nxt;
    }
  return (info->count_hist = i);
}
