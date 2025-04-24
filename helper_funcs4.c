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
	char *start = str;
	char *end;

    /* Skip leading spaces and tabs */
	while (*start == ' ' || *start == '\t')
		start++;

	if (*start == '\0')  /* If the string is empty or only spaces */
		return (start);

    /* Find the end of the string */
	end = start;
	while (*end != '\0') /* Walk to the end of the string */
		end++;

    /* Move end back to the last non-whitespace character */
	end--;

    /* Skip trailing spaces and tabs */
	while ((end > start) && (*end == ' ' || *end == '\t'))
		end--;

    /* Null terminate after the last non-space character */
	end[1] = '\0';

	return (start);
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
* _strcmp - compares 2 strings
* @s1: first string to be compared
* @s2: second string to be compared
*
* Return: an integer
*/

int _strcmp(char *s1, char *s2)
{

	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{

		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}

		i++;
	}

	return (s1[i] - s2[i]);

}
