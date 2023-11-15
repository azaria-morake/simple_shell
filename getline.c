/**
* With this program I want to read input from user and output it to stdio
*
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)

{

	char *line = NULL;
	size_t length = 0;

	printf("Enter a command:\n");

	ssize_t read = getline(&line, &length, stdin);

	if (read != -1) {
		printf("The command you've entered is: %s.\n", line);
	}
	else {
		perror("getline() error.\n");
		return (1);
	}
	free(line);
	return (0);
}
