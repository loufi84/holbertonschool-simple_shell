#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
*  read_line - prints a prompt (takes input and prints it)
*
* Return: the line read
*/

char *read_line(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t whole_line;

	printf("$ ");/*Prompt*/

	whole_line = getline(&line, &len, stdin);/*Read user input*/

	if (whole_line == -1) /*EOF, (Ctrl+D) or error*/
	{
		printf("\n");
		free(line);
		return (NULL);
	}

	return (line);
}

/**
* split_string - splits a string into tokens using spaces as delimiter
* @string: the input string to split
* @array: array to put the tokens in
*
* Return: a NULL-terminated array of tokens (words), or NULL on failure
*/

int split_string(char *string, char *array[])
{
	int i = 0;

	char *token;

	char *delim = " \t\n";

	if (string == NULL)
		return (0);

	token = strtok(string, delim);

	while (token && i < MAX_ARGS - 1)
	{
		array[i++] = token;
		token = strtok(NULL, delim);
	}

	array[i] = NULL;

	return (i);
}

/**
* exit - simulation de la fonction exit standard
* @status: code de sortie à retourner à l’OS
*
* Cette version affiche le code de sortie, flush stdout,
* et termine le programme immédiatement avec _exit().
*/
void exit(int status)
{
	/* Optionnel : afficher ou logger quelque chose avant de quitter*/
	write(STDOUT_FILENO, "Fermeture du programme\n", 24);

	/* Termine immédiatement le programme, sans nettoyer*/
	_exit(status);
}
