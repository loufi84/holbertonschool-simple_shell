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

/**
 * help_help - Helper function to display help help page
 */

void help_help(void)
{
	printf("⌌--------------🐱--------------⌍\n");
	printf("|           Help help          |\n");
	printf("|------------------------------|\n");
	printf("| help: This command will      |\n");
	printf("| display the help page        |\n");
	printf("| in the shell                 |\n");
	printf("|--------------😎--------------|\n");
	printf("| usage : help [BUILTIN]       |\n");
	printf("⌎------------------------------⌏\n");
}

/**
 * help_exit - Helper function to display exit help page
 */

void help_exit(void)
{
	printf("⌌--------------🐱--------------⌍\n");
	printf("|           Help exit          |\n");
	printf("|------------------------------|\n");
	printf("| exit: This command will      |\n");
	printf("| exit the shell with the      |\n");
	printf("| given exit status            |\n");
	printf("|--------------😎--------------|\n");
	printf("| usage : exit [status]        |\n");
	printf("⌎------------------------------⌏\n");
}

/**
 * help_env - An helper function to display env help page
 */

void help_env(void)
{
	printf("⌌--------------🐱--------------⌍\n");
	printf("|           Help env           |\n");
	printf("|------------------------------|\n");
	printf("| env: This command will       |\n");
	printf("| display the current          |\n");
	printf("| environment                  |\n");
	printf("|--------------😎--------------|\n");
	printf("| usage : env                  |\n");
	printf("⌎------------------------------⌏\n");
}
