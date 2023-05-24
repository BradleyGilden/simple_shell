#include "main.h"

/**
 * find_path - builds path directory for the standard command cmd entered
 * @cmd: input command string
 *
 * Return: built directory
 */

char *find_path(char *cmd)
{
	struct stat statbuffer;
	char *token, *pathdir = NULL, *env_path = NULL, *env_path_cp = NULL;

	if (stat(cmd, &statbuffer) == 0)
		return (cmd);
	env_path = _getenv("PATH");

	if (env_path != NULL)
	{
		env_path_cp = _strdup(env_path);

		if (env_path_cp == NULL)
			return (NULL);
		token = str_tok(env_path_cp, ":");
		while (token != NULL)
		{
			pathdir = malloc(_strlen(cmd) + _strlen(token) + 2);
			if (pathdir == NULL)
				return (NULL);
			str_cpy(pathdir, token);
			_strcat(pathdir, "/");
			_strcat(pathdir, cmd);
			_strcat(pathdir, "\0");
			if (stat(pathdir, &statbuffer) == 0)
			{
				free(env_path_cp);
				return (pathdir);
			}
			else
			{
				free(pathdir);
				token = str_tok(NULL, ":");
			}
		}
		free(env_path_cp);
		return (NULL);
	}
	return (NULL);
}

/**
 * check_path - designed to check if cmd executable exists within path
 * @cmd: input command string
 *
 * Return: check status: 0 if found
 *                      -1 otherwise
 */

int check_path(char *cmd)
{
	struct stat statbuffer;
	char *token, *pathdir = NULL, *env_path = NULL, *env_path_cp = NULL;

	if (stat(cmd, &statbuffer) == 0)
		return (0);

	env_path = _getenv("PATH");

	if (env_path != NULL)
	{
		env_path_cp = _strdup(env_path);

		if (env_path_cp == NULL)
			return (-1);
		token = str_tok(env_path_cp, ":");
		while (token != NULL)
		{
			pathdir = malloc(_strlen(cmd) + _strlen(token) + 2);
			if (pathdir == NULL)
				return (-1);
			str_cpy(pathdir, token);
			_strcat(pathdir, "/");
			_strcat(pathdir, cmd);
			_strcat(pathdir, "\0");
			if (stat(pathdir, &statbuffer) == 0)
			{
				free(env_path_cp);
				free(pathdir);
				return (0);
			}
			else
			{
				free(pathdir);
				token = str_tok(NULL, ":");
			}
		}
		free(env_path_cp);
		return (-1);
	}
	return (-1);
}
