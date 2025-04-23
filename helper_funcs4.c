#include "shell.h"

/**
 * is_numeric - Helper function to check if an arg is numeric
 *
 * @str: The string to check
 *
 * Return: 1 if numeric, 0 if not
 */

int is_numeric(const char *str)
{
	int i = 0;

	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	for (; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * _atoi - convert a string to an itnt
 * @s: sring to convert to int
 * Return: int
 */

int _atoi(char *s)
{
	int i = 0, sign = 1;
	unsigned int num = 0;

	if (!s)
		return (0);

	while (s[i] == ' ')
		i++;

	if (s[i] == '-')
		sign = -1, i++;
	else if (s[i] == '+')
		i++;

	while (s[i] >= '0' && s[i] <= '9')
	{
		num = num * 10 + (s[i] - '0');
		i++;
	}

	return (num * sign);
}

