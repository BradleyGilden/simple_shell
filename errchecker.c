#include "main.h"

/**
 * malloc_checkptr - check if return is NULL and exit if condition is met
 * @s: check null string
 */

void malloc_checkptr(char *s)
{
	if (s == NULL)
		exit(EXIT_FAILURE);
}

/**
 * malloc_checkdptr - check if return is NULL and exit if condition is met
 * @s: check null 2d string
 */

void malloc_checkdptr(char **s)
{
	if (s == NULL)
		exit(EXIT_FAILURE);
}

/**
 * getret - check for getline return value and EOF condition
 * @glob: struct of global variables
 * @ret: return of getline function
 */

void getret(myglob_t *glob, ssize_t ret)
{
	char newln_c = '\n';

	if (glob->lineptr == NULL)
		return;
	if (ret == -1)
	{
		free_alloced_mem_on_exit(glob);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, &newln_c, 1);
		exit(glob->es);
	}
}

/**
 * write_cmd_err - writes error output for commands not found in path
 * @glob: struct of global variables
 */


void write_cmd_err(myglob_t *glob)
{
	char *str = malloc(sizeof(char) * (count_digits(glob->ln) + 1));

	malloc_checkptr(str);
	to_string(glob->ln, str);

	write(STDERR_FILENO, glob->av, _strlen(glob->av));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, glob->tokens[0], _strlen(glob->tokens[0]));
	write(STDERR_FILENO, ": not found", 11);
	write(STDERR_FILENO, "\n", 1);
	free(str);
}

/**
 * write_exec_err - writes error when execve fails.
 * @glob: struct of global variablesr
 */

void write_exec_err(myglob_t *glob)
{
	char *str = malloc(sizeof(char) * (count_digits(glob->ln) + 1));
	char *message = ": Permission denied";

	malloc_checkptr(str);
	to_string(glob->ln, str);

	write(STDERR_FILENO, glob->av, _strlen(glob->av));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, _strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, glob->tokens[0], _strlen(glob->tokens[0]));
	write(STDERR_FILENO, message, _strlen(message));
	write(STDERR_FILENO, "\n", 1);
	free(str);
}
