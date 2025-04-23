#include "shell.h"

/**
 * shell_help - Display the shell's help page
 *
 * @args: The args of the help
 */

void shell_help(char **args)
{
	if (args[1] == NULL)
	{
		printf("⌌----------ฅ^•ﻌ•^ฅ----------⌍\n");
		printf("|         Shell help        |\n");
		printf("|---------------------------|\n");
		printf("| help: display help        |\n");
		printf("| env: display environment  |\n");
		printf("| exit: exit the shell      |\n");
		printf("| all other commands are    |\n");
		printf("| handled with PATH.        |\n");
		printf("|------------😎-------------|\n");
		printf("⌎---------------------------⌏\n");
	}
	else
	{
		if (strcmp(args[1], "exit") == 0)
			help_exit();
		else if (strcmp(args[1], "env") == 0)
			help_env();
		else if (strcmp(args[1], "help") == 0)
			help_help();
		else
			fprintf(stderr, "help: no help topics match %s\n", args[1]);
	}
}
