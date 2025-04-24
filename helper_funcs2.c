#include "shell.h"

/**
 * split_path - A function to split path of PATH
 *
 * @string: Pointer to the user's input
 * @array: Pointer to array containing the PATH
 *
 * Return: First directory of PATH
 */

char *split_path(char *string, char *array[])
{
	int i = 0;
	char *token;

	token = strtok(string, ":");/*Split string at every ':'*/
	while (token && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok(NULL, ":");
	}
	array[i] = NULL;
	return (array[0]);
}

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

/**
* what_is_cmd - check if the command is an absolute path or a built_in
* @cmd: an array of tokens (= input)
*
* Return: 0 in success, -1 in failure
*/

int what_is_cmd(char **cmd, char *line, int last_status)
{
	builtin_t verif[] = {
		{"env", print_env},
		{"help", shell_help},
		{NULL, NULL}
	};
	int i = 0;

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
	{
		return (-1);
	}

	if (strcmp(cmd[0], "exit") == 0)
	{
		shutdown(cmd, line, last_status);
		return (0);
	}

	for (i = 0; verif[i].name != NULL; i++)
	{/*If cmd is a built-in, call the correct function*/
		if (strcmp(verif[i].name, cmd[0]) == 0)
		{
			verif[i].func(cmd);
			return (0);
		}
	}

	if (cmd[0][0] == '/')/*Check if cmd is an absolute path*/
	{/*If path exists and if it's executable, execute the input*/
		if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == 0)
		{
			return (-1);
		}

		else
		{
			perror(cmd[0]);
			return (-1);
		}
	}

	return (-1);/*If not a built-in nor an absolute path*/
}
