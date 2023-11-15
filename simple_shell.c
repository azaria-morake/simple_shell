/**
 * main - Is the main fucntion where all program computations take place.
 * @void: Main takes no arguments.
 *
 * Description: Displays a shell like prompt to end user and they can use stdi
 * to communicate with the shell.
 * Return: 0.
 */

#include "shell.h"

int main(void)
{
	while(1)
	{
		cmd_prompt();
	}
	return (0);
}
