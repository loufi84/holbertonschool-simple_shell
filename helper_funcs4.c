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

	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	for (; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}
