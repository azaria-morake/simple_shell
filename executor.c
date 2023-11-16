/**
 * executor - Executes user stdi.
 * @cmd_buff: Store user stdi commands in a buffer.
 * @arg_v: Is the argument vector.
 * @en_var: Is the environment variable.
 * Return: Returns 0 for success.
 */

#include "shell.h"

int executor(char *cmd_buff[], char **arg_v, char **en_var)
{
	pid_t pid;
	int execmd, condition;

	pid = fork();

	char *tunnel = handle_path(en_var);
	printf("The sought-after path is: %s.", tunnel);

	if (pid == -1)
	{
		perror("Child process failure.");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execmd = execve(cmd_buff[0], cmd_buff, NULL);
		if (execmd == -1)
		{
			perror("Command execution failure."); /*exit*/
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&condition);
	return (0);
}
