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
*
* Return: a NULL-terminated array of tokens (words), or NULL on failure
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
		status = _atoi(args[1]);/*Convert the exit arg to integer status code*/

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
 * @args: The command to run
 * @cmd_c: Command count
 * @shell_n: The name of the shell
 * @exit_stat: Exit status pointer
 * Return: Error codes if fail, pid status
 */

int run_cmd(char **args, int cmd_c, const char *shell_n, int *exit_stat)
{
	char *command_path;

	if (args == NULL || args[0] == NULL)
		return (0);
/* Handle built-in commands */
	if (handle_builtin(args, exit_stat) != -1)
		return (*exit_stat);

	if (_strchr(args[0], '/') != NULL)
	{
		if (access(args[0], F_OK | X_OK) == 0)
			command_path = strdup(args[0]);
		else
		{
			print_error(args, cmd_c, shell_n, exit_stat);
			return (*exit_stat);
		}
	}
	else
	{/* Try to find command path from PATH environment */
		command_path = find_command_path(args[0], exit_stat);
		if (command_path == NULL)
		{/* If not found, print error and return */
			print_error(args, cmd_c, shell_n, exit_stat);
			return (*exit_stat);
		}
	}

	execute_command(command_path, args, shell_n, exit_stat);
	return (*exit_stat);
}
