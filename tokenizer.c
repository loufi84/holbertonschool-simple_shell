#include "shell.h"

/**
*  read_line - prints a prompt (takes input and prints it)
*
* Return: the line read
*/

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t whole_line;

		printf("$ ");/*Prompt*/

		whole_line = getline(&line, &len, stdin);/*Read user input*/

		if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
		{
			printf("\n");
			free(line);
			return (NULL);
		}

	return (line);
}

/**
 * split_string - splits a string into tokens using spaces as delimiter
 * @string: the input string to split
 * @array: array to put the tokens in
 *
 * Return: a NULL-terminated array of tokens (words), or NULL on failure
 */

int split_string(char *string, char *array[])
{
	int i = 0;
	char *token;
	char *delim = " \t\n:";

	if (string == NULL)
		return (0);

	token = strtok(string, delim);

	while (token && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok(NULL, delim);
	}

	array[i] = NULL;

	return (i);
}

/**
* is_built_in - definds if the command is a built-in or not
* @cmd: the array of tokens
*
* Return: 0 in success, -1 in failure
*/

int is_built_in(char **cmd) /*cmd = the array of tokens (=input)*/
{
	static char buffer[BUFFER_SIZE];
	char **dir;
	char *path_env = getenv("PATH");
	int full_path = split_string(path_env, dir);/*Look for the path*/
	int i = 0;

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
	{
		return (-1);
	}

/*Check if PATH is absent or here but empty*/
	if (path_env == NULL || path_env[0] == '\0')
	{
		return (-1);
	}

	if (strcmp(cmd[0], "/") == 0)/*Check if cmd is an absolute path*/
	{/*If path exists and if it's executable, execute the input*/
		if (access(path_env, F_OK) && access(path_env, X_OK))
		{
			execve(path_env, cmd, environ);
		}

		else
		{
			return (-1);
		}
	}

	else
	{
		while (full_path)
		{
			sprintf(buffer, "%s", *cmd);

			if (access(buffer, F_OK) && access(buffer, X_OK))
			{
				execve(buffer, cmd, environ);
			}

			else
			{
				return (-1);
			}

			i++;
		}
	}

	return (0);
}
