#include "main.h"

/**
 * splitstr - function splits string in tokens.
 * @line: line pointer to command line string
 * @linecopy: pointer to copy of line ptr
 *
 * Return: 2d array of tokens
 */

char **splitstr(char *line, char *linecopy)
{
	char *token = NULL;
	char *delim = " \n\t\r";
	char **tokenarray = NULL;
	unsigned int tokencount = 0;
	int i = 0;

	if (line == NULL || linecopy == NULL)
		return (NULL);
	token = str_tok(line, delim);
	tokencount++;

	if (token == NULL)
		return (NULL);
	while (token != NULL)
	{
		token = str_tok(NULL, delim);
		tokencount++;
	}
	tokenarray = malloc(sizeof(char *) * tokencount);
	if (tokenarray == NULL)
		return (NULL);

	token = str_tok(linecopy, delim);
	for (i = 0; token != NULL; i++)
	{
		tokenarray[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (tokenarray[i] == NULL)
		{
			free_tokens(tokenarray);
			return (NULL);
		}

		str_cpy(tokenarray[i], token);
		token = str_tok(NULL, delim);
	}
	tokenarray[i] = NULL;

	return (tokenarray);
}

