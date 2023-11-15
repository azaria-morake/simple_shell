/**
 * main - Is the main function where all the computation takes place.
 * @void: Main takes no arguments.
 *
 * Description: Display a CMD prompt, wait for user input
 * store user input, write user input to stdout
 * returns to CMD prompt when child process terminates
 * Returns: 0.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{

/* getline() variable declarations */
char *line_buff;
size_t length;
ssize_t std_in;

/* write() variable declarations */
const char *std_out;
const char *cmd_prmpt;
ssize_t out_bytes; /* writes output to stdout */
ssize_t out_bytes2;

/* getline() assignments */
line_buff = NULL;
length = 0;

cmd_prmpt = "$ ";
out_bytes = write(1, std_out, strlen(std_out));

std_in = getline(&line_buff, &length, stdin);

/* write() assignments */
std_out = "The command you've entered is: %s.\n", std_in;

out_bytes2 = write(1, std_out, strlen(std_out));


free(line_buff);

return 0;
}

