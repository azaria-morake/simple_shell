#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for command chaining */
#define C_CMD_NORM
#define C_CMD_OR
#define C_CMD_AND
#define CMD_LOOP/*CMD_CHAIN3 */

/* for convert_number() */
#define LOWERCASE1_CONV
#define UNSIGNED2_CONV

/* 1 if using system getline() */
#define CNT_GETLINE 0
#define CNT_STRTOK 0

#define HISTORY_FILE ".simpsh_history"
#define HISTORY_MAX 4096

extern char **environ; /*environ*/


/**
 * struct str_ls - Singly linked lists,
 * @obj: Number field.
 * @obj2: String object.
 * @obj3: Redirects to next node.
 */
typedef struct str_ls
{
  int _number;
  char *_string;
  struct str_ls *nxt; /*liststr*/
} list_t;

/**
 * struct datapass - Incorporates pseudo-arguments to be passed into a function
 * enabling a consistent prototype for a function pointer structure.
 * @ar_g: Getline generated string with args.
 * @arg_v: String array from arg.
 * @cmd_path: cmd string path.
 * @arg_c: Arg count.
 * @ln_count: Err count.
 * @exits_err: Err for exits.
 * @ln_flag: Count line of input.
 * @fl_name: File name.
 * @_home: Duplicate of local environment.
 * @usr_env: User defined copy of environment.
 * @hist_node: History node.
 * @nic: Alias node.
 * @home_mod: Activates when environment is modified.
 * @conition: Return of previously executed cmd.
 * @cmd_bufferer: cmd buffer.
 * @cmd_species: commands like ||  && ;.
 * @rd_filedescrip: Read file descriptor.
 * @count_hist: Count history line number.
 */
typedef struct datapass /*passinfo*/
{
  char *ar_g;
  char **arg_v;
  char *cmd_path; /*path*/
  int arg_c; /*argc*/
  unsigned int ln_count;
  int exits_err;
  int ln_flag;
  char *fl_name; /*fname*/
  list_t *usr_env; /**/
  list_t *hist_node; /*history*/
  list_t *nic; /*alias*/
  char **_home; /*environ*/
  int home_mod; /*env_changed*/
  int condition; /*status*/

  char **cmd_bufferer; /* pointer to cmd ; chain buffer, for memory mangement */
  int cmd_species; /* CMD_type ||, &&, ; */ /*cmd_buff_type*/
  int rd_filedescrip; /*readfd*/
  int count_hist; /*historycount*/
} info_t;

#define DATA_INIT \ /*INFO_INIT*/
  {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
      0, 0, 0}

/**
 *builtin_cmd - All builtin objects.
 *@obj1: Built in flag.
 *@function_: Function.
 */
typedef struct builtin_cmd
{
  char *obj1;
  int (*function_)(info_t *obj2);
} builtin_table;


/* toem_shloop.c */
int cmd_looper(info_t *obj1, char **obj2); /*hsh*/
int builtin_finder(info_t *obj1); /*find_builtin*/
void cmd_finder(info_t *obj1);/*find_cmd*/
void cmd_fork(info_t *obj1); /*fork_cmd*/

/* toem_parser.c */
int cmd(info_t *obj1, char *obj2);/*is_cmd*/
char *duplicate_char(char *obj1, int obj2, int obj3); /*dup_chars*/
char *path_finder(info_t *obj1, char *obj2, char *obj3); /*find_path*/

/* loophsh.c */
int cmd_loop(char **obj1); /*loophsh*/

/* toem_errors.c */
void c_puts2(char *obj1);/*_eputs*/
int c_putchar2(char obj1); /*_eputchar*/
int c_put(char obj1, int obj2);/*_putfd*/
int c_puts(char *obj1, int obj2); /*_putsfd*/

/* toem_string.c */
int c_strlen(char *obj); /*strlen*/
int c_strcmp(char *obj1, char *obj2); /*_strcmp*/
char *starts_(const char *, const char *obj2); /*starts_with*/
char *c_strcat(char *obj1, char *obj2); /*_strcat*/

/* toem_string1.c */
char *c_strcpy(char *obj1, char *obj2);/* _strcpy*/
char *c_strdup(const char *obj1); /*_strdup*/
void c_puts(char *obj1); /*_puts*/
int c_putchar(char obj1);/*_putchar*/

/* toem_exits.c */
char *_strn_cpy(char *obj1, char *obj2, int obj3); /*_strncpy*/
char *strn_cat(char *, char *obj1, int obj2); /*_strncat*/
char *str2chr(char *obj1, char obj2); /*_strchr*/

/* toem_tokenizer.c */
char **token1(char *obj1, char *obj2);/*strtow*/
char **token2(char *obj2, char obj1); /*strtow2*/

/* toem_realloc.c */
char *set_mem(char *obj1, char obj2, unsigned int obj3); /*_memset*/
void _release(char **obj1); /*ffree*/
void *c_realloc(void *obj1, unsigned int obj2, unsigned int obj3); /*_realloc*/

/* toem_memory.c */
int release(void **obj1); /*bfree*/

/* toem_atoi.c */
int reactive(info_t *); /*interactive*/
int c_delimiter(char obj1, char *obj2); /*_isdelimiter*/
int c_alpha(int obj1);/*_isalpha*/
int atoint(char *obj1); /*_atoi*/

/* toem_errors1.c */
int errtoint(char *obj1); /*_erratoi*/
void display_err(info_t *obj1, char *obj2); /*print_error*/
int display_errd(int obj1, int obj2); /*print_d*/
char *num_converter(long int obj1, int obj2, int obj3); /*convert_number*/
void rm_coms(char *obj1); /*remove_comments*/

/* toem_builtin.c */
int c_esc(info_t *obj1);/*_myexit*/
int c_cmd(info_t *obj1); /* mycd*/
int mayday(info_t *obj1);/*_myhelp*/

/* toem_builtin1.c */
int my_hist(info_t *obj1); /*my history*/
int my_nic(info_t *obj1); /*_myalias*/

/*toem_getline.c */
ssize_t _input(info_t *obj);/*get_input*/
int c_getline(info_t *obj1, char **obj2, size_t *obj3);/* _getline*/
void handle_sigint(int obj1); /*sigintHandler*/

/* toem_getinfo.c */
void clr_data(info_t *obj1);/*clear_info*/
void stage_data(info_t *obj1, char **obj2); /*set_info*/
void rm_data(info_t *obj1, int obj2);/*free_info*/

/* toem_environ.c */
char *habitat2(info_t *obj1, const char *obj2); /*_getenviron*/
int myhabitat(info_t *obj1); /*_myenv*/
int set_myhabitat(info_t *obj1); /*_mysetenv*/
int unset_myhabitat(info_t *obj1); /*_myunsetenv*/
int group_habitat_ls(info_t *obj1);/* populate_env_list*/

/* toem_getenv.c */
char **habitat(info_t *obj1); /*getenviron*/
int habitat_unset(info_t *obj1, char *obj2);/*_unsetenv*/
int habitat_set(info_t *obj1, char *obj2, char *obj3); /*_setenv*/

/* toem_history.c */
char *hist_fl(info_t *obj1); /*get_history_file*/
int record_hist(info_t *obj1); /*write_history*/
int rd_hist(info_t *obj1); /*read_history*/
int create_hist_ls(info_t *obj1, char *obj2, int ln_count); /*build_history_list*/
int recall_hist(info_t *obj1); /*renumber_history*/

/* toem_lists.c */
list_t *app_node(list_t **obj1, const char *obj2, int obj3); /*add_node*/
list_t *app_node_term(list_t **obj1, const char *obj2, int obj3); /*add_node_end*/
size_t display_ls_str(const list_t *obj1); /*print_list_str*/
int rm_index_node(list_t **obj1, unsigned int obj2); /*delete_node_at_index*/
void free_ls(list_t **obj1); /*free_list*/

/* toem_lists1.c */
size_t ls_lenght(const list_t *obj1); /*list len*/
char **ls_to_str(list_t *obj1); /*list_to_strings*/
size_t list_display(const list_t *obj1); /*print_list*/
list_t *node_entry(list_t *obj2, char *obj2, char obj3); /*node_starts_with*/
ssize_t node_index(list_t *obj1, list_t *obj2); /*get_node_index*/

/* toem_vars.c */
int loop(info_t *obj1, char *obj2, size_t *obj3); /*is_chain*/
void inspect_loop(info_t *obj1, char *obj2, size_t *obj3, size_t obj4, size_t obj5); /*check_chain*/
int rm_nic(info_t *obj1); /*replace_alias*/
int rm_vrs(info_t *obj1); /*replace_vars*/
int rm_str(char **obj1, char *obj2); /*replace_string*/

#endif
