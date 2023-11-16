#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 80

int str_len(char *string);
char *handle_path(char **en_var); /*_path.c*/
int executor(char *cmd_buff[], char **arg_v, char **en_var); /*executor.c*/
int tokens(char *cmd, char *cmd_buff[]); /* tokens.c */
int cmd_prompt(void); /* linked to cmd_prompt.c */
char *rm_newline(char *string, int length); /* newline.c */
#endif
