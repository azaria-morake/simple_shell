/**
 * handle_path - Handles path.
 * @en_var: Is the environment variable.
 *
 * Return: Returns path.
 */

#include "shell.h"

char *handle_path(char **en_var)
{
	char *delimiter;
	delimiter = "=";
	int x = 0;
	char *tunnel_id, *tunnel_val, *tunnel;

	while (en_var[x] != NULL)
	{
		tunnel_id = strtok(en_var[x], delimiter);
		tunnel_val = strtok(NULL, delimiter);

		if (tunnel_id != NULL && tunnel_val != NULL && _strcmp(tunnel_id, "PATH") == 0)
		{
			tunnel = tunnel_val;
			return (tunnel);
			break;
		}
		x++;
	}
	return (NULL);
}
			
