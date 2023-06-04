#include "main.h"

/**
 * ch_builtin - function selects which built-in functions to implement
 * @glob: struct of global variables
 *
 * Return: 1 if using execve in main shell loop is not necessary
 *         0 otherwise
 */

int ch_builtin(myglob_t *glob)
{
	if (_strcmp(glob->tokens[0], "exit") == 0)
	{
		exit_args(glob);
		return (1);
	}
	else if (_strcmp(glob->tokens[0], "env") == 0)
	{
		_printenv();
		free_alloced_mem_on_exit(glob);
		return (1);
	}
	else if (_strcmp(glob->tokens[0], "echo") == 0)
	{
		if (tcnt(glob->tokens) > 1)
			echo_args(glob->tokens, &(glob->es));
	}
	else if (_strcmp(glob->tokens[0], "/bin/echo") == 0)
	{
		if (tcnt(glob->tokens) > 1)
			echo_args(glob->tokens, &(glob->es));
	}
	return (0);
}

/**
 * _printenv - prints the environment list using global environ variable
 */

void _printenv(void)
{
	unsigned int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * exit_args - function handles exit built-in and it's arguments
 * @glob: struct of global variables
 */

void exit_args(myglob_t *glob)
{
	int stat;
	char **token = glob->tokens;

	if (tcnt(glob->tokens) == 1)
	{
		free_alloced_mem_on_exit(glob);
		exit(glob->es);
	}
	else if (tcnt(glob->tokens) > 1 && _isdigit(token[1]) == 0)
	{
		write_exec_err2(glob);
		free_alloced_mem_on_exit(glob);
		glob->es = 2;
	}
	else
	{
		stat = _atoi(token[1]);
		free_alloced_mem_on_exit(glob);
		exit(stat);
	}
}

/**
 * echo_args - handles $$, $? and $VAR arguments for echo command.
 * @tok: tokenized 2d array of line ptr string.
 * @es: error status
 */

void echo_args(char **tok, int *es)
{
	int i = 1, old_size;
	int pid = (int)getpid();
	char *str, *retvar;

	while (tok[i] != NULL)
	{
		if (tok[i][0]  == '$' && _strlen(tok[i]) >= 2)
		{
			retvar = _getenv(&tok[i][1]);
			old_size = _strlen(tok[i]) + 1;
			if (tok[i][1] == '$' && tok[i][2] == '\0')
			{
				str = malloc(sizeof(char) * (count_digits(pid) + 1));
				malloc_checkptr(str);
				to_string(pid, str);
				tok[i] = _realloc(tok[i], old_size, _strlen(str) + 1);
				malloc_checkptr(tok[i]);
				str_cpy(tok[i], str);
				free(str);
			}
			else if (tok[i][1] == '?' && tok[i][2] == '\0')
			{
				str = malloc(sizeof(char) * (count_digits(*es) + 1));
				malloc_checkptr(str);
				to_string(*es, str);
				tok[i] = _realloc(tok[i], old_size, _strlen(str) + 1);
				malloc_checkptr(tok[i]);
				str_cpy(tok[i], str);
				free(str);
			}
			else if (retvar != NULL)
			{
				tok[i] = _realloc(tok[i], old_size, _strlen(retvar) + 1);
				malloc_checkptr(tok[i]);
				str_cpy(tok[i], retvar);
			}
		}
		i++;
	}
}
