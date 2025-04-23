#include "shell.h"

/**
 * main - Entry point
 *
 * @argc: Argument count
 * @argv: Argument value
 *
 * Return: 0 for success, various errors
 */
int main(int __attribute__((unused))argc, char *argv[])
{
	char *line = NULL, *args[MAX_ARGS], *trimmed_line;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("simple_shell> ");
		fflush(stdout);

		if (line)
			free(line);

		line = read_line();
		if (line == NULL)
			break;

		comments_handling(line);

		trimmed_line = trim_whitespace(line);

		if (*trimmed_line == '\0')
			continue;

		if (split_string(trimmed_line, args) == NULL || args[0] == NULL)
			continue;

		if (what_is_cmd(args, line, last_status) != 0)
			last_status = run_cmd(args, argv[0]);
	}

	free(line);
	return (last_status);
}
