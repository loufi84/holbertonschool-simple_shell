#include "shell.h"

/**
 * _strlen - A function that calculate the length of the string
 *
 * @str: The string to calculate the length from
 *
 * Return: The length of the string
 */

int _strlen(char *str)
{
	int len = 0;

	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _strcmp - compare 2 strings
 * @s1: 1st string to compare
 * @s2: 2nd string to compare
 * Return: 0 if equal, < 0 if s1 < s2, > 0 if s1 > s2
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

	i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _atoi - convert a string to an itnt
 * @s: sring to convert to int
 * Return: int
 */

int _atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;
	int sign = 1;
	int fnd_dig = 0;

	while (s[i] == ' ')
	{
		i++;
	}


	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + (s[i] - '0');
			fnd_dig = 1;
		}
		else if (fnd_dig)
		{
			break;
		}

		i++;
	}

	if (!fnd_dig)
		return (0);

	return (num * sign);
}
