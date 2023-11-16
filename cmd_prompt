/**
 * cmd_prompt - Reads user input as stdi.
 * @void: The function takes no arguments.
 *
 * Description: Recognizes the standard input by user
 * to communicate with the shell.
 * Return: num chars from stdi.
 */

#include "shell.h"

int cmd_prompt(char **arg_v, char **en_var)

{
	char *line_buff, *cmd, *cmd_buff[MAX];/*cmd_buff stores stdi args */
	size_t length;
	ssize_t std_in, arg_c; /*arg_c argumnt count*/

	line_buff = NULL;
	length = 0;
	std_in = getline(&line_buff, &length, stdin);

	if (std_in == -1)
	{
		if (feof(stdin))
		{
			free(line_buff);
			exit(0);
		}

		else
		{
			perror("getline() stderr.");
			free(line_buff);
		}
	}

	cmd = rm_newline(line_buff, std_in);
	printf("cmd is: %s", cmd);

	arg_c = tokens(cmd, cmd_buff);
	printf("Arguments are: %s %s", cmd_buff[0], cmd_buff[1]);

	executor(cmd_buff, arg_v, en_var);
	
	free(line_buff);

	return (std_in);

}
