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


	errno = 0;
	whole_line = _getline(&line, &len, 0);/*Read user input*/

	if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
	{
		if (errno == 0) /*If user types Ctrl+D (EOF)*/
		{
			free(line);
			return (NULL);
		}
		perror("_getline failed"); /*Handle error*/
		free(line);
		exit(errno);
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
	int i = 0, len = 0;
	char *token, *delim = " \t\n";

	if (string == NULL)
		return (NULL);
/*Incrementation until the first character, after all spaces at the beginning*/
	while (*string == ' ' || *string == '\t' || *string == '\n')
	{
		string++;
	}

	len = strlen(string);
/*Eras spaces at the end*/
	while (len > 0 && (string[len - 1] == ' ' || string[len - 1] == '\t' ||
		string[len - 1] == '\n'))
	{
		string[len - 1] = '\0';
		len--;
	}

	token = strtok(string, delim);

	while (token != NULL && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok(NULL, delim);
	}
	array[i] = NULL;

	return (array[0]);
}

/**
* shutdown - This function exits the Shell
*
* @code: The exit code
*/
void shutdown(char **code)
{
	int status = 0;

	if (code[1])
	{
		if (!is_numeric(code[1]))
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", code[1]);
			exit(2);
		}
		if (code[2] != NULL)
		{
			fprintf(stderr, "exit: too many arguments\n");
			return;
		}
		status = _atoi(code[1]);
	}
	exit(status);
}

/**
 * print_env - This function prints the current environment
 *
 * @env: Just a necessity for structure
 */

void print_env(char **env)
{
	int i = 0;
	(void)env;

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
 * @shell_name: The name of the shell
 */

void run_cmd(char *args[], const char *shell_name)
{
	int status;
	pid_t pid;

	if (args == NULL || args[0] == NULL)
		return;

	path_handling(args);
	if (args[0] == NULL)/*If command not exists, exit*/
		exit(EXIT_FAILURE);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");/*If fork failed, error exit*/
		exit(EXIT_FAILURE);
	}

	if (pid == 0)/*Child process*/
	{
		execve(args[0], args, environ);/*Else, executes*/
		if (errno == ENOENT)
			fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
		else
			perror(shell_name);
		exit(127);
	}
	else/*Parent process*/
	{
		waitpid(pid, &status, 0);/*Waits for child to end*/
	}

}
