#include "main.h"

/**
 * write_exec_err2 - writes error output for exit argument error
 * @glob: struct of global variables
 */

void write_exec_err2(myglob_t *glob)
{
	char *str = malloc(sizeof(char) * (count_digits(glob->ln) + 1));

	malloc_checkptr(str);
	to_string(glob->ln, str);

	write(STDERR_FILENO, glob->av, _strlen(glob->av));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, glob->tokens[0], _strlen(glob->tokens[0]));
	write(STDERR_FILENO, ": Illegal number: ", 18);
	write(STDERR_FILENO, glob->tokens[1], _strlen(glob->tokens[1]));
	write(STDERR_FILENO, "\n", 1);
	free(str);
}
