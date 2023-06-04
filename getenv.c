#include "main.h"

/**
 * letter_ch - compare chars of strings
 * @s: input string.
 * @part: partiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int letter_ch(char s[], const char *part)
{
	usint a = 0, b = 0, c = 0;

	while (s[a])
	{
		b = 0;
		while (part[b])
		{
			if (s[a] == part[b])
			{
				c++;
				break;
			}
			b++;
		}
		a++;
	}
	if (a == c)
		return (1);
	return (0);
}

/**
 * str_tok - splits a string by some partiter.
 * @str: input string.
 * @part: partiter.
 *
 * Return: string splited.
 */
char *str_tok(char str[], const char *part)
{
	static char *splt, *last;
	char *beginning = NULL, nol = '\0';
	usint idx = 0, track = 0;

	if (str != NULL)
	{
		if (letter_ch(str, part))
			return (NULL);
		splt = str;
		idx = _strlen(str);
		last = &str[idx];
	}
	beginning = splt;
	if (beginning == last)
		return (NULL);

	for (; *splt; splt++)
	{
		if (splt != beginning)
			if (*splt && *(splt - 1) == '\0')
				break;
		for (idx = 0; *(part + idx); idx++)
		{
			if (*splt == *(part + idx))
			{
				*splt = nol;
				if (splt == beginning)
					beginning += 1;
				break;
			}
		}
		if (track == 0 && *splt)
			track = 1;
	}
	if (track == 0)
		return (NULL);
	return (beginning);
}

/**
 * _getenv - searches for environment variable in path and ...
 *           returns pointer to it's value.
 * @path: environment variable to search for
 * Return: address of value string
 *         NULL if variable does not exist.
 */

char *_getenv(char *path)
{
	char **env;
	size_t path_len;

	env = environ;
	path_len = _strlen(path);

	while (*env != NULL)
	{
		if (_strncmp(*env, path, path_len) == 0 && (*env)[path_len] == '=')
		{
			return (&((*env)[path_len + 1]));
		}
		env++;
	}

	return (NULL);
}
