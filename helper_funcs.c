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
	whole_line = getline(&line, &len, stdin);/*Read user input*/

	if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
	{
		if (errno == 0) /*If user types Ctrl+D (EOF)*/
		{
			free(line);
			return (NULL);
		}
		perror("getline failed"); /*Handle error*/
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
#include "shell.h"

/**
 * split_string - Split a string by whitespace into an array of tokens
 * @string: Input string
 *
 * Return: Pointer to a NULL-terminated array of strings
 */

char **split_string(char *string)
{
	char **tokens = malloc(sizeof(char *) * MAX_ARGS);
	char *token;
	int i = 0;

	if (!tokens)
		return (NULL);

	token = strtok(string, " \t\n");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;

	return (tokens);
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

int run_cmd(char **args, int cmd_c, const char *shell_n, int *exit_stat)
{
	char *command_path;
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (0);

	if (handle_builtin(args, exit_stat) != -1)
		return (*exit_stat);

	command_path = find_command_path(args[0], exit_stat);
	if (command_path == NULL)
	{
		print_error(args, cmd_c, shell_n, exit_stat);
		return (*exit_stat);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		*exit_stat = 1;
		free(command_path);
		return (*exit_stat);
	}

	if (pid == 0)
	{
		execve(command_path, args, environ);
		perror(shell_n);
		free(command_path);
		exit(127); /*Command not found*/
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*exit_stat = WEXITSTATUS(status);
	else
		*exit_stat = 1;
	free(command_path);
	return (*exit_stat);
}
