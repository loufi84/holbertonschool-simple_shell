#include "shell.h"

/**
 * path_error - Helper function that handles the inability to find a command
 *
 * @args: A pointer to the array of commands
 */

void path_error(char *args)
{
	fprintf(stderr, "%s: command not found\n", args);
}

/**
 * alloc_error - Helper function that handle allocation error
 *
 * @cmd: The pointer to the command to reinitialize
 */

void alloc_error(char *cmd)
{
	cmd = NULL;
}

/**
 * path_handling - Resolves command path using PATH env variable
 * @cmd: Array containing command and arguments
 */
void path_handling(char **cmd)
{
	char *path_env, *path_copy, *new_cmd, *dirs[BUFFER_SIZE];
	char full_path[BUFFER_SIZE];
	int i, found = 0;

	if (!cmd || !cmd[0])
		return;
	if (strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK | X_OK) == 0)
			return;
		fprintf(stderr, "command not found: %s\n", cmd[0]);
		cmd[0] = NULL;
		return;
	}
	path_env = getenv("PATH");
	if (!path_env || !*path_env)
		path_error(cmd[0]);

	path_copy = strdup(path_env);
	if (!path_copy)
		alloc_error(cmd[0]);

	split_path(path_copy, dirs);
	for (i = 0; dirs[i] && !found; i++)
	{
		sprintf(full_path, "%s/%s", dirs[i], cmd[0]);
		if (access(full_path, F_OK | X_OK) == -1)
			continue;
		new_cmd = strdup(full_path);
		if (!new_cmd)
			break;
		cmd[0] = new_cmd;
		found = 1;
	}
	free(path_copy);
	if (found)
		return;
}
