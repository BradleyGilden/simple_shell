#include "main.h"

/**
 * _strlen - calculates length of a string
 * @str: input string
 *
 * Return: length of string (excluding null character)
 */

int _strlen(char *str)
{
	int i = 0, len = 0;

	while (str[i++])
		len++;

	return (len);
}

/**
 * str_cpy - function copies string contents from the src to the dest string
 *           if dest string is already occupied, it will be overwritten
 * @dest: string to be copied to
 * @src: string to copy
 *
 * Return: address of destination string
 */
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strncmp - compares the first n bytes of 2 strings
 * @str1: first string in comparison
 * @str2: second string in comparison
 * @len: number of bytes to compare
 *
 * Return: 0 if bytes match, non-zero otherwise
 */
int _strncmp(const char *str1, const char *str2, size_t len)
{
	while (len--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		if (*str1 == '\0')
			break;
		str1++;
		str2++;
	}
	return (0);
}

/**
 * _strcmp - function that compares strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if string is equal.
 *         ->if s1 > s2, then return + ascii value of ...
 *         the first extra character in s1
 *         ->if s1 < s2 then return - ascii value of ...
 *         first extra character in s2
 *         ->if s1 != s2 at index i ...
 *         then return s1[i] - s2[i]
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0, s1_len = 0, s2_len = 0;

	while (s1[i++])
		s1_len++;

	i = 0;

	while (s2[i++])
		s2_len++;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	if (s1_len > s2_len)
		return (s1[s2_len]);

	else if (s2_len > s1_len)
		return ((-1) * s2[s1_len]);
	else
		return (0);
}

/**
 * _strcat - concatinates source string to dest string
 * @dest: resultant string after concatination
 * @source: string to be added to the resultant string
 *
 * Return: return dest string
 */
char *_strcat(char *dest, char *source)
{
	unsigned int  i = 0;
	char *end = dest + _strlen(dest);

	while (source[i])
	{
		*end++ = source[i++];
	}

	*end = '\0';
	return (dest);
}
