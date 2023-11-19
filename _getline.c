#include "shell.h"

/**
 * input_buf - Command buffer.
 * @info: Parameter.
 * @buf: Buffer index.
 * @len: Length index.
 *
 * Return: bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
  ssize_t r = 0;
  size_t len_p = 0;

  if (!*len)
    {
      
      free(*buf);
      *buf = NULL;
      signal(SIGINT, handle_sigint);
      #if CNT_GETLINE
      r = getline(buf, &len_p, stdin);
      #else
      r = c_getline(info, buf, &len_p);
      #endif
      if (r > 0)
	{
	  if ((*buf)[r - 1] == '\n')
	    {
	      (*buf)[r - 1] = '\0';
	      r--;
	    }
	  info->ln_flag = 1;
	  rm_coms(*buf);
	  create_hist_ls(info, *buf, info->count_hist++);

	  {
	    *len = r;
	    info->cmd_bufferer = buf;
	  }
	}
    }
  return (r);
}

/**
 * _input - Gets a std input line.
 * @info: Parameter.
 *
 * Return: Bytes read.
 */
ssize_t _input(info_t *info)
{
  static char *buf;
  static size_t i, j, len;
  ssize_t r = 0;
  char **buf_p = &(info->ar_g), *p;

  c_putchar(BUFFER_FLUSH);
  r = input_buf(info, &buf, &len);
  if (r == -1)
    return (-1);
  if (len)
    {
      j = i;
      p = buf + i;

      inspect_loop(info, buf, &j, i, len);
      while (j < len)
	{
	  if (loop(info, buf, &j))
	    break;
	  j++;
	}

      i = j + 1;
      if (i >= len)
	{
	  i = len = 0;
	  info->cmd_race = C_CMD_NORM;
	}

      *buf_p = p;
      return (c_strlen(p));
    }

  *buf_p = buf;
  return (r);
}

/**
 * read_buf - Buffer reader.
 * @obj1: Parameter.
 * @obj2: Actual buffer.
 * @obj3: Size.
 *
 * Return: r.
 */
ssize_t read_buf(info_t *obj1, char *obj2, size_t *obj3)
{
  ssize_t r = 0;

  if (*obj3)
    return (0);
  r = read(obj1->rd_filedescrip, obj2, READ_BUFFER_SIZE);
  if (r >= 0)
    *obj3 = r;
  return (r);
}

/**
 * c_getline - Gets std input line.
 * @info: Parameter.
 * @ptr: Pointer to buffer.
 * @length: Pointer size.
 *
 * Return: s.
 */
int c_getline(info_t *info, char **ptr, size_t *length)
{
  static char buf[READ_BUFFER_SIZE];
  static size_t i, len;
  size_t k;
  ssize_t r = 0, s = 0;
  char *p = NULL, *new_p = NULL, *c;

  p = *ptr;
  if (p && length)
    s = *length;
  if (i == len)
    i = len = 0;

  r = read_buf(info, buf, &len);
  if (r == -1 || (r == 0 && len == 0))
    return (-1);

  c = str2chr(buf + i, '\n');
  k = c ? 1 + (unsigned int)(c - buf) : len;
  new_p = c_realloc(p, s, s ? s + k : k + 1);
  if (!new_p)
    return (p ? free(p), -1 : -1);

  if (s)
    strn_cat(new_p, buf + i, k - i);
  else
    _strn_cpy(new_p, buf + i, k - i + 1);

  s += k - i;
  i = k;
  p = new_p;

  if (length)
    *length = s;
  *ptr = p;
  return (s);
}

/**
 * handle_sigint - Handles ctrl-C.
 * @sig_num: Signal number.
 *
 * Return: void.
 */
void handle_sigint(__attribute__((unused))int sig_num)
{
  c_puts("\n");
  c_puts("$ ");
  c_putchar(BUFFER_FLUSH);
}

