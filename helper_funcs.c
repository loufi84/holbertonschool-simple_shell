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
	int i = 0;
	char *token, *delim = " \t\n";

	if (string == NULL)
		return (NULL);
/*Incrementation until the first character, after all spaces at the beginning*/
	while (*string == ' ' || *string == '\t' || *string == '\n')
	{
		string++;
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
* @args: Tokenized commmand line arguments
* @line: Input line to be freed before exit
* @last_status: Last exit status to use if no status provided
*/
void shutdown(char **args, char *line, int last_status)
{
	int status = last_status;

	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			/*check if is a number*/
			fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
			free(line);
			exit(2);
		}
		if (args[2]) /*Too many arguments*/
		{
			fprintf(stderr, "exit: too many arguments\n");
			return; /*Does not end the shell like Bash*/
		}
		status = _atoi(args[1]);
	}
	free(line);
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
 *
 * Return: Error codes if fail, pid status
 */

int run_cmd(char *args[], const char *shell_name)
{
	int status;
	pid_t pid;

	if (args == NULL || args[0] == NULL)
		return (0);

	path_handling(args);
	if (args[0] == NULL)/*If command not exists, exit*/
		return (127);

	pid = fork();
	if (pid == -1)
	{
		perror("fork");/*If fork failed, error exit*/
		return (1);
	}

	if (pid == 0)/*Child process*/
	{
		execve(args[0], args, environ);/*Else, executes*/
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
			exit(127);
		}
		else
		{
			perror(shell_name);
			exit(1);
		}
	}
	else/*Parent process*/
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}

}
