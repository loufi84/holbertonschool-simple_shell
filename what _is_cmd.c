#include "shell.h"

/**
* what_is_cmd - check if the command is an absolute path or a built_in
* @cmd: an array of tokens (= input)
*
* Return: 0 in success, -1 in failure
*/

int what_is_cmd(char **cmd)
{
	builtin_t verif[] = {
		{"exit", shutdown},
		{"env", print_env},
		{NULL, NULL}
	};
	int i = 0;
	char *path_env = getenv("PATH");

	if (cmd == NULL || *cmd == NULL)/*Check if pointers are valid*/
	{
		return (-1);
	}

	for (i = 0; i < 3; i++)
	{/*If cmd is a built-in, call the correct function*/
		if (strcmp(verif[i].name, cmd[0]) == 0)
		{
			verif[i].func();
			return (0);
		}
	}

	if (cmd[0][0] == '/')/*Check if cmd is an absolute path*/
	{/*If path exists and if it's executable, execute the input*/
		if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == 0)
		{
			execve(cmd[0], cmd, environ);
			return (0);
		}

		else
		{
			return (-1);
		}
	}

	return (-1);/*If not a built-in nor an absolute path*/
}
