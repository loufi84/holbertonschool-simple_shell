#include "shell.h"

/**
 * path_error - Helper function that handles the inability to find a command
 *
 * @args: A pointer to the array of commands
 * @path: Pointer to the path using _getenv
 */

void path_error(char *args, char *path)
{
	fprintf(stderr, "%s: command not found\n", args);
	free(path);
}

/**
 * alloc_error - Helper function that handle allocation error
 *
 * @cmd: The pointer to the command to reinitialize
 */

void alloc_error(char *cmd)
{
	fprintf(stderr, "alloc failed for %s\n", cmd);
	exit(EXIT_FAILURE);
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
	if (strchr(cmd[0], '/'))/*Search for sign '/'*/
	{
		if (access(cmd[0], F_OK | X_OK) == 0)/*If true, execute*/
			return;
		fprintf(stderr, "command not found: %s\n", cmd[0]);/*If false, error*/
		cmd[0] = NULL;
		return;
	}
	path_env = _getenv("PATH");
	if (!path_env || !*path_env)/*If empty or not exists, error*/
		path_error(cmd[0], path_env);

	path_copy = strdup(path_env);
	if (!path_copy)/*If memory alloc fails, error*/
		alloc_error(cmd[0]);

	split_path(path_copy, dirs);/*Cut path with ':'*/
	for (i = 0; dirs[i] && !found; i++)
	{
		sprintf(full_path, "%s/%s", dirs[i], cmd[0]);
		if (access(full_path, F_OK | X_OK) == -1)/*If path exists, continue*/
			continue;
		new_cmd = strdup(full_path);/*memory allowed to existing full path*/
		if (!new_cmd)
			break;
		cmd[0] = new_cmd;
		found = 1;
	}
	free(path_copy);
	free(path_env);
	if (found)/*If nothing found, nothing is executed so return*/
		return;
}
