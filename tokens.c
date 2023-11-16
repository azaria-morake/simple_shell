/**
 * tokens - Breaks string into tokens.
 * @cmd: Any command steaming from stdi.
 * @cmd_buff: Stores commands in a buffer.
 *
 * Description: Readies tokens to be parsed.
 * Return: Returns x.
 */

#include "shell.h"

int tokens(char *cmd, char *cmd_buff[])
{
	char *delimiter = " ";
	char *blocks; /*tokens*/
	int x = 0; /*initialize counter*/

	blocks = strtok(cmd, delimiter);

	while(blocks)
	{
		cmd_buff[x++] = blocks;
		blocks = strtok(NULL, delimiter);
	}

	cmd_buff[x] = NULL;
	
	return (x);
}
