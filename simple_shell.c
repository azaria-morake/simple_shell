/**
 * main - Is the main fucntion where all program computations take place.
 * @arg_v: Is the argument vector.
 * @arg_c: Is the argument count.
 * @en_var: Is the environment variable.
 *
 * Return: 0.
 */

#include "shell.h"

int main(int arg_c, char **arg_v, char **en_var)
{
	(void) arg_c;
	
	while(1)
	{
		cmd_prompt(arg_v, en_var);
	}
	return (0);
}
