/**
 * main - Is the main function where all computations take place.
 * @void: Takes no args.
 *
 * Returns: 0.
 */

#include "shell.h"

int main(void) {
  char *cmd_input = NULL;      /* captures user input */
  char cmd_shell[MAX];         /* stores user input */
  char cmd_invalid = '\n';     /* Invalid input */
  char cmd_line_root[MAX] = "cmd_sh$ "; /* Prompt to be displayed */
  size_t cmd_count;            /* counts the number of items in cmd_input */
  size_t cmd_limit = 50;
  size_t length;/* Line limit */

  while (1) {
    printf("%s", cmd_line_root);

    if (getline(&cmd_input, &cmd_count, stdin) == -1) {
      perror("Error reading input");
      break;
    }

    /* Replace newline character with null character */
    length = strlen(cmd_input);
    if (cmd_input[length - 1] == '\n') {
      cmd_input[length - 1] = '\0';
    }

    /* Check for invalid input */
    if (strcmp(cmd_input, &cmd_invalid) == 0) {
      printf("Invalid input\n");
    } else {
      /* Tokenize the input */
      char *token = strtok(cmd_input, " ");
      int x = 0;

      /* Copy tokens into cmd_shell */
      while (token != NULL && x < MAX - 1) {
	strcpy(cmd_shell, token);
	token = strtok(NULL, " ");
	x++;
      }

      if (cmd_count > cmd_limit || strcmp(cmd_shell, &cmd_invalid) == 0) {
	printf("Invalid token or exceeded line limit.\n");
	printf("Line limit is 50, including white space.\n");
	printf("Valid tokens are characters, excluding white space.\n");
      }
    }
  }

  /* No need to free the allocated memory for cmd_input since it's not dynamically allocated */

  return 0;
}
