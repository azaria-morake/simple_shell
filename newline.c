/**
 * rm_newline - Removes '\n' from user stdi.
 * @string: Points to a string for user stdi.
 * @length: Length of user stdi.
 *
 * Description: All it seeks to do is terminate '\n'.
 * Return: String.
 */

#include "shell.h"

char *rm_newline(char *string, int length)
{
	if (string > 0 && string[length - 1] == '\n')
		string[length - 1] = '\0';
	return (string);
}
