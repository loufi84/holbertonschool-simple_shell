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

	char *delim = " \t\n";

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
* shutdown - This function exits the Shell
*/
void shutdown(void)
{
	printf("Merci d'avoir utilisé notre programme ฅ^•ﻌ•^ฅ\n");
	exit(EXIT_SUCCESS);
}

/**
 * print_env - This function prints the current environment
 */

void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * run_cmd - A function that run user's command
 *
 * @args: The command to run
 */

void run_cmd(char *args[])
{
	char *cmd = args[0];
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execve(cmd, args, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	return;
}
