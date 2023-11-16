/**
 * parse - Concatenates.
 * @string_1: User stdi.
 * @string_2: Is the path.
 *
 * Return: outcome.
 */

#include "shell.h"

char parse(char *string_1, char *string_2)
{
	int length_1 = str_len(string_1), length_2 = str_len(string_2);
	char outcome = malloc(length_1 + length_2 + 2);

	outcome = str_cat(string_1, "/");
	outcome = str_cat(outcome, string_2);
	outcome = str_cat(outcome, "\0");

	return (outcome);
}
