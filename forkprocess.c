#include "main.h"

/**
 * forkerr - handles for errors
 * @glob: struct of global variables.
 */

void forkerr(myglob_t *glob)
{
	if (errno == EACCES)
	{
		glob->es = 126;
		write_exec_err(glob);
	}
	else
	{
		glob->es = 127;
		write_cmd_err(glob);
	}
}

/**
 * forking - function initializes forking the main process in order to...
 *             execute the standard commands in the child process.
 * @glob: struct of global variables.
 */

void forking(myglob_t *glob)
{
	pid_t fret;
	int status, tracker = 0;
	char *cmd = glob->tokens[0];

	if (glob->tokens[0][0] != '/' && glob->tokens[0][0] != '.')
	{
		tracker = 1;
		cmd = find_path(glob->tokens[0]);
	}
	if (cmd == NULL || access(cmd, F_OK) == -1)
	{
		forkerr(glob);
	}
	else
	{
		fret = fork();
		if (fret == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (fret == 0)
			exec(cmd, glob);
		else
		{
			wait(&status);
			glob->es = wexitstat(status);
		}
	}

	free_alloced_mem_on_exit(glob);
	if (tracker)
		free(cmd);
}
