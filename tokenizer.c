#include "shell.h"

/**
*  read_line - prints a prompt (takes input and prints it)
*
* Return: the line read
*/

char read_line(void)
{
	char line = NULL;
	size_t len = 0;
	ssize_t whole_line;

	while (1)
	{
		printf("$ ");/*Prompt*/

		whole_line = getline(&line, &len, stdin);/*Read user input*/

		if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
		{
			printf("\n");
			break;
		}

		printf("%s", line); /*Echo the input*/
	}

	free(line);

	return (0);
}

/**
 * split_string - splits a string into tokens using spaces as delimiter
 * @string: the input string to split
 * @array: array to put the tokens in
 *
 * Return: a NULL-terminated array of tokens (words), or NULL on failure
 */

char *split_string(char *string, char *array[])
{
	int i = 0;
	char *token;
	char delim[] = {"\"", " ", "\n", "\t", "\'", "(", ")", "{", "}", "&", "$",
					"[", "]", "*", "\\", "|", "/", "!", ",", ";", "?", ":",
					"<", ">", "-", "+", "~", "#", "=", "_", "^", "@", '\0'};

	if (string == NULL)
		return (NULL);

	token = strtok(string, delim);

	for (i = 0; i != '\0'; i++)
	{
		token = strtok(NULL, delim);
	}

	array[i] = NULL;

	return (array[i]);
}
