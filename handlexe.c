#include "main.h"

/**
 * exec - function utilises execve() to execute standard commands in path
 * @glob: struct of global variables.
 * @cmd: command that is entered in command line
 */

void exec(char *cmd, myglob_t *glob)
{
	char **envcpy = environ;

	execve(cmd, glob->tokens, envcpy);
	if (errno == EACCES)
	{
		write_exec_err(glob);
		glob->es = 126;
	}
	free_alloced_mem_on_exit(glob);
	_exit(glob->es);
}
