#include <stdio.h>
#include <stdlib.h>

int main(void)

{

	char *line = NULL;
	size_t length = 0;
	ssize_t read;

	printf("Enter a command:\n");

	read = getline(&line, &length, stdin);

	if (read != -1)
	{
		printf("The command you've entered is: %s.\n", line);
	}
	else
	{
		perror("getline() error.\n");
		return (1);
	}
	free(line);
	return (0);
}
