#include "shell.h"

/**
 * process_command - Process a command line
 * @line: Input command line
 * @argv: Program arguments
 * @cmd_count: Command counter
 * @exit_status: Pointer to exit status
 *
 * Return: 1 to exit shell, 0 to continue
 */
int process_command(char *line, char *argv[], int cmd_count, int *exit_status)
{
	char **args = NULL, *trimmed_line = NULL;
	int built_result;

	comments_handling(line);
	trimmed_line = trim_whitespace(line);
	args = split_string(trimmed_line);

	if (args == NULL || args[0] == NULL || args[0][0] == '\0')
	{
		free(args);
		return (0);
	}

	built_result = handle_builtin(args, exit_status);
	if (built_result == 1) /* exit builtin */
	{
		free(args);
		return (1);
	}
	else if (built_result == 0) /* Other builtin */
	{
		free(args);
		return (0);
	}

	run_cmd(args, cmd_count, argv[0], exit_status);
	free(args);
	return (0);
}

/**
 * main - Entry point
 *
 * @argc: Argument count
 * @argv: Argument value
 *
 * Return: 0 for success, various errors
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	char *line = NULL;
	int exit_status = 0, cmd_count = 0;
	int should_exit;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell> ");
		fflush(stdout);

		if (line)
			free(line);

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		cmd_count++;
		should_exit = process_command(line, argv, cmd_count, &exit_status);
		if (should_exit)
		{
			free(line);
			exit(exit_status);
		}
	}
	free(line);
	return (exit_status);
}
