/**
 * main - Is the main fucntion where all program computations take place.
 * @void: Main takes no arguments.
 *
 * Description: Displays a shell like prompt to end user and they can use stdi
 * to communicate with the shell.
 * Return: 0.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MXLL 1024 /* Maximum line length */

int main(void)

{
	char stdin_line[MXLL];
	char cmd_prompt[] = "$ ";
	char stderr_message[] = "Command not found.\n";
	char eof[] = "Received EOF. Exiting...\n"; /* EOF message */
	int write_bytes, read_bytes;
	char *argv[MXLL];

	while (1)
	{
   write_bytes = write(STDOUT_FILENO, cmd_prompt, strlen(cmd_prompt));
		if (write_bytes < 0)
		{
			perror("write");
			exit(1);
		}

		read_bytes = getline(stdin, stdin_line, MXLL);

		if (read_bytes == -1)
		{
	 write_bytes = write(STDOUT_FILENO, eof, strlen(eof));
	 if (write_bytes < 0)
	 {
		 perror("write");
		 exit(1);
	 }
	 break;

	 if (strlen(stdin_line) == 1)
	 {
		 continue;
	 }
	 /* Remove the trailing newline character */
	 stdin_line[strlen(stdin_line) - 1] = '\0';
	 /* Tokenize the input into arguments */
	 int argc = 1;
	 char *token = strtok(stdin_line, " ");
	 argv[0] = token;
	 while ((token = strtok(NULL, " ")) != NULL)
	 {
		 argc++;
		 argv[argc - 1] = token;
	 }
	 argv[argc] = NULL;

	 /* Execute the command */
	 pid_t pid = fork();
	 if (pid == 0)
	 {
		 execve(argv[0], argv, NULL); /* Child process */

		 /* If execve fails, print an error message and exit */
   write_bytes = write(STDOUT_FILENO, stderr_message, strlen(stderr_message));
     if (write_bytes < 0)
     {
	     perror("write");
	     exit(1);
     }
     exit(1);
	 }
	 else if (pid > 0)
	 {
		 wait(NULL); /* Parent process */
	 }
	 else
	 {
		 perror("fork"); /* Fork failed */
		 exit(1);
	 }
		}
		return (0);
	}
