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
		if (str[i] < '0' || str[i] > '9')/*Non-digit character*/
			return (0);
	}
	return (1);/*String is numeric*/
}

/**
 * _atoi - convert a string to an int
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

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 *
 * @str: The input string to be trimmed.
 *
 * Return: A pointer to the string with leading and
 * trailing whitespace removed.
 * xIf the string is empty or contains only whitespace,
 * returns an empty string.
 */

char *trim_whitespace(char *str)
{
	char *end;
/*Skip leading whitespace*/
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;/*Move end pointer to the last character*/
	/*Trim trailing whitespace*/
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	end[1] = '\0';
	return (str);
}


/**
* _strchr - locates a character in a string
* @c: parameter
* @s: string
*
* Return: return to the first occurence or NULL if the character is not found
*/

char *_strchr(char *s, char c)
{

	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (s);
		}

	s++;
	}

	if (c == '\0')
	{
		return (s);
	}

	return (NULL);
}

/**
* handle_exit - Function to handle exit command
*
* @args: User input
* @exit_status: Exit code to return
*
* Return: The exit status or 0 if no input
*/

int handle_exit(char **args, int *exit_status)
{/*If an argument is provided, convert it to an integer exit status*/
	if (args[1])
	{
		*exit_status = _atoi(args[1]);
	}

	else
	{
		*exit_status = 0;/*Default exit status is 0 if none provided*/
	}

	/*Tell main to exit*/
	return (1);
}
