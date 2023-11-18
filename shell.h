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


#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1


#define C_CMD_NORM
#define C_CMD_OR
#define C_CMD_AND
#define CMD_LOOP


#define LOWERCASE1_CONV
#define UNSIGNED2_CONV


#define CNT_GETLINE 0
#define CNT_STRTOK 0

#define HISTORY_FILE ".simpsh_history"
#define HISTORY_MAX 4096

extern char **environ;


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
  struct str_ls *nxt;
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
typedef struct datapass
{
  char *ar_g;
  char **arg_v;
  char *cmd_path;
  int arg_c;
  unsigned int ln_count;
  int exits_err;
  int ln_flag;
  char *fl_name;
  list_t *usr_env;
  list_t *hist_node;
  list_t *nic;
  char **_home;
  int home_mod;
  int condition;

  char **cmd_bufferer;
  int cmd_race;
  int rd_filedescrip;
  int count_hist;
} info_t;

#define DATA_INIT \
  {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
      0, 0, 0}

/**
 * builtin_cmd - All builtin objects.
 * @c_type: Built in flag.
 * @function_: Function.
 */
typedef struct builtin_cmd
{
  char *c_type;
  int (*function_)(info_t *object);
} builtin_cmd_table;



int cmd_looper(info_t *obj1, char **obj2);
int builtin_finder(info_t *obj1);
void cmd_finder(info_t *obj1);
void cmd_fork(info_t *obj1);


int cmd(info_t *obj1, char *obj2);
char *duplicate_char(char *obj1, int obj2, int obj3);
char *path_finder(info_t *obj1, char *obj2, char *obj3);


int cmd_loop(char **obj1);


void c_puts2(char *obj1);
int c_putchar2(char obj1);
int c_put(char obj1, int obj2);
int c_puts(char *obj1, int obj2);


int c_strlen(char *obj);
int c_strcmp(char *obj1, char *obj2);
char *starts_(const char *, const char *obj2);
char *c_strcat(char *obj1, char *obj2);


char *c_strcpy(char *obj1, char *obj2);
char *c_strdup(const char *obj1);
void c_puts(char *obj1);
int c_putchar(char obj1);


char *_strn_cpy(char *obj1, char *obj2, int obj3);
char *strn_cat(char *, char *obj1, int obj2);
char *str2chr(char *obj1, char obj2);


char **token1(char *obj1, char *obj2);
char **token2(char *obj2, char obj1);


char *set_mem(char *obj1, char obj2, unsigned int obj3);
void _release(char **obj1);
void *c_realloc(void *obj1, unsigned int obj2, unsigned int obj3);


int release(void **obj1);


int reactive(info_t *);
int c_delimiter(char obj1, char *obj2);
int c_alpha(int obj1);
int atoint(char *obj1);


int errtoint(char *obj1);
void display_err(info_t *obj1, char *obj2);
int display_errd(int obj1, int obj2);
char *num_converter(long int obj1, int obj2, int obj3);
void rm_coms(char *obj1);


int c_esc(info_t *obj1);
int c_cmd(info_t *obj1);
int mayday(info_t *obj1);


int my_hist(info_t *obj1);
int my_nic(info_t *obj1);


ssize_t _input(info_t *obj);
int c_getline(info_t *obj1, char **obj2, size_t *obj3);
void handle_sigint(int obj1);


void clr_data(info_t *obj1);
void stage_data(info_t *obj1, char **obj2);
void rm_data(info_t *obj1, int obj2);


char *habitat2(info_t *obj1, const char *obj2);
int myhabitat(info_t *obj1);
int set_myhabitat(info_t *obj1);
int unset_myhabitat(info_t *obj1);
int group_habitat_ls(info_t *obj1);


char **habitat(info_t *obj1);
int habitat_unset(info_t *obj1, char *obj2);
int habitat_set(info_t *obj1, char *obj2, char *obj3);


char *hist_fl(info_t *obj1);
int record_hist(info_t *obj1);
int rd_hist(info_t *obj1);
int create_hist_ls(info_t *obj1, char *obj2, int ln_count);
int recall_hist(info_t *obj1);


list_t *app_node(list_t **obj1, const char *obj2, int obj3);
list_t *app_node_term(list_t **obj1, const char *obj2, int obj3);
size_t display_ls_str(const list_t *obj1);
int rm_index_node(list_t **obj1, unsigned int obj2);
void free_ls(list_t **obj1);


size_t ls_lenght(const list_t *obj1);
char **ls_to_str(list_t *obj1);
size_t list_display(const list_t *obj1);
list_t *node_entry(list_t *obj2, char *obj2, char obj3);
ssize_t node_index(list_t *obj1, list_t *obj2);


int loop(info_t *obj1, char *obj2, size_t *obj3);
void inspect_loop(info_t *obj1, char *obj2, size_t *obj3, size_t obj4, size_t obj5);
int rm_nic(info_t *obj1);
int rm_vrs(info_t *obj1);
int rm_str(char **obj1, char *obj2);

#endif
