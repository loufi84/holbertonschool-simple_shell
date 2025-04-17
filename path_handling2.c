#include "shell.h"

/**
* path_handling - handles the path if not absolute
* @cmd: an array of tokens (= input)
*
* Return: 0 in success, -1 in failure
*/

int path_handling(char **cmd)
{
	static char buffer[BUFFER_SIZE];
	char *dir[MAX_ARGS];
	char *path_copy;
	char *path_env = getenv("PATH");
	char *full_path;
	int i = 0;

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
		return (-1);

	/*Check if PATH is absent or here but empty*/
	if (path_env == NULL || path_env[0] == '\0')
	{
		return (-1);
	}

	path_copy = strdup(path_env);

	if (path_copy == NULL)
	{
		return (-1);
	}

	full_path = split_string(path_copy, dir);/*Look for the path*/

	while (dir[i] != NULL)
	{
		sprintf(buffer, "%s/%s", dir[i], cmd[0]);

		if (access(buffer, F_OK) == 0 && access(buffer, X_OK) == 0)
		{
			cmd[0] = buffer;
			free(path_copy);
			return (0);
		}
		i++;
	}

	free(path_copy);
	return (-1);
}
