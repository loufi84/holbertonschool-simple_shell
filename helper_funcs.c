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
