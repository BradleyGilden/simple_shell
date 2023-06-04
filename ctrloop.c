#include "sash.h"

/**
 * w_out - prints strings out onto screen using write
 * @message: message to be printed
 */

void w_out(char *message)
{
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * display_prompt - displays prompt in interactive mode
 * @es: error status
 */
void display_prompt(int es)
{
	char *stable = "✔ <";
	char *err = "✖ <";
	char *end = "> $ ";
	char *str_es;

	if (isatty(STDIN_FILENO))
	{
		str_es = malloc(sizeof(char) * (count_digits(es) + 1));
		malloc_checkptr(str_es);
		to_string(es, str_es);
		if (es == 0)
			w_out(stable);
		else
			w_out(err);
		w_out(str_es);
		w_out(end);
		free(str_es);
	}
}

/**
 * my_getline - Handles the main process for interactive mode
 * @av: vector of arguments passed to the program.
 */

void my_getline(char *av)
{
	int built_ret = 0;
	ssize_t getlin_ret = 0;
	size_t n = 0;
	myglob_t glob;

	glob.lineptr = NULL, glob.copy = NULL, glob.tokens = NULL;
	glob.es = 0, glob.ln = 0, glob.av = NULL;
	glob.av = av;
	while (1)
	{
		display_prompt(glob.es);

		getlin_ret = getline(&(glob.lineptr), &n, stdin);
		getret(&glob, getlin_ret);
		glob.ln++;

		if (glob.lineptr == NULL || _strcmp(glob.lineptr, "\n") == 0)
			continue;
		glob.lineptr[getlin_ret - 1] = '\0';

		glob.copy = malloc(sizeof(char) * getlin_ret);
		malloc_checkptr(glob.copy);
		str_cpy(glob.copy, glob.lineptr);
		glob.tokens = splitstr(glob.lineptr, glob.copy);
		if (glob.tokens == NULL)
			continue;
		built_ret = ch_builtin(&glob);
		if (built_ret != 0)
			continue;

		glob.es = 0;

		forking(&glob);
	}
}
