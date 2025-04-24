#include "shell.h"

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
	char *line = NULL, **args = NULL, *trimmed_line = NULL;
	int exit_status = 0, cmd_count = 0;
	int built_result;

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
		comments_handling(line);
		trimmed_line = trim_whitespace(line);

		args = split_string(trimmed_line);
		if (args == NULL || args[0] == NULL || args[0][0] == '\0')
		{
			free(args);
			continue;
		}

		built_result = handle_builtin(args, &exit_status);
		if (built_result == 1) /*exit builtin*/
		{
			free(args);
			free(line);
			exit(exit_status);
		}
		else if (built_result == 0) /*Other builtin*/
		{
			free(args);
			continue;
		}

		run_cmd(args, cmd_count, argv[0], &exit_status);
		free(args);
	}

	free(line);
	return (exit_status);
}
