#include "main.h"

/**
 * count_digits - counts the number of digits in an int including '-' sign
 * @num: integer to count
 *
 * Return: digit count
*/

int count_digits(int num)
{
	int count = 0;

	if (num == 0)
		return (1);

	if (num < 0)
	{
		num = (-1) * num;
		count++;
	}

	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

/**
 * to_string - converts integer to string
 * @str: empty string.
 * @num: number to be converted.
 */

void to_string(int num, char *str)
{
	int i = 0, j = 0, len, sign = 1;
	char temp;

	if (num < 0)
	{
		sign = -1;
		num = -num;
	}

	if (num == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}

	while (num > 0)
	{
		str[i++] = num % 10 + '0';
		num /= 10;
	}

	if (sign < 0)
	{
		str[i++] = '-';
	}

	str[i] = '\0';

	len = _strlen(str);
	for (j = 0; j < len / 2; j++)
	{
		temp = str[j];
		str[j] = str[len - j - 1];
		str[len - j - 1] = temp;
	}
}

/**
 * _atoi - convert string to int
 * @s: input string
 *
 * Return: int value
*/

int _atoi(char *s)
{
	int i, value = 0, sign = 1, end = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign = (-1) * sign;

		if (end > 0 && s[i] == ' ')
			break;
		if (value >= INT_MAX / 10 || (value == INT_MAX / 10 && s[i] - '0' > 7))
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		if (s[i] >= '0' && s[i] <= '9')
		{

			value = value * 10 + s[i] - '0';
			end += 1;
		}

	}
	value = value * sign;
	return (value);
}

/**
 * _isdigit - checks if string contains only digits
 * @str: input string
 *
 * Return: 1 if it is a digit
 *         0 if not
*/

int _isdigit(char *str)
{
	unsigned int i = 0;

	if (str == NULL)
		return (1);

	if (str[0] == '-' && str[1] != '\0')
		i++;

	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}

	return (1);
}

/**
 * tcnt - counts the number of tokens in token string
 * @tok: input 2 array of tokens
 *
 * Return: 1 if it is a digit
 *         0 if not
 */

int tcnt(char **tok)
{
	unsigned int i = 0;
	unsigned int count = 0;

	while (tok[i++] != NULL)
	{
		count++;
	}

	return (count);
}
