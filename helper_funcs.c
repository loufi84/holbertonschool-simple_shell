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


	whole_line = _getline(&line, &len, 0);/*Read user input*/

	if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
	{
		free(line);
		line = NULL;
		len = 0;
		printf("\n");
		return (NULL);
	}
	return (line);
}

/**
* split_string - splits a string into tokens using various delimiters
* @string: the input string to split
* @array: array to put the tokens in
*
* Return: a NULL-terminated array of tokens (words), or NULL on failure
*/

char *split_string(char *string, char *array[])
{
	int i = 0;
	char *token, *delim = " \t\n";
	char *save;

	if (string == NULL)
		return (NULL);

	token = strtok_r(string, delim, &save);

	while (token != NULL && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok_r(NULL, delim, &save);
	}
	array[i] = NULL;

	return (array[0]);
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
	int status;
	pid_t pid = fork();

	if (args == NULL || args[0] == NULL)
		return;

	if (pid == -1)
	{
		perror("fork");/*If fork failed, error exit*/
		exit(EXIT_FAILURE);
	}

	if (pid == 0)/*Child process*/
	{
		path_handling(args);
		if (args[0] == NULL)/*If command not exists, exit*/
			exit(EXIT_FAILURE);
		execve(args[0], args, environ);/*Else, executes*/
		perror(args[0]);/*If execute failed, error exit*/
		exit(EXIT_FAILURE);
	}
	else/*Parent process*/
	{
		waitpid(pid, &status, 0);/*Waits for child to end*/
	}

}
