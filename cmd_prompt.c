/**
 * cmd_prompt - Reads user input as stdi.
 * @void: The function takes no arguments.
 *
 * Description: Recognizes the standard input by user
 * to communicate with the shell.
 * Return: num chars from stdi.
 */

#include "shell.h"

int cmd_prompt(void)

{
	char *line_buff;
	size_t length;
	ssize_t std_in;

	line_buff = NULL;
	length = 0;
	std_in = getline(&line_buff, &length, stdin);

	return (std_in);

}
