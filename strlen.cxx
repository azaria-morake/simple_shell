/**
 * str_len - This counts string length.
 * @string: String to be counted.
 *
 * Return: Returns x.
 */

#include "shell.h"

int str_len(char *string)
{
	int x = 0;

	while (string[x] != '\0')
		x++;

	return (x);
}
