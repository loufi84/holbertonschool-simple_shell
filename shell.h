#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

extern char **environ;

int split_string(char *string, char *array[]);
char *read_line(void);
void shutdown(char **args);
void print_env(char **args);
int built_in(char *cmd, char **args);
void cd_builtin(char *args[]);
int change_directory(char *path);

/**
 * struct builtin_s - A simple structure to store the built_in
 *						functions of the Shell
 *
 * @name: The name of the function
 * @func: A pointer to the function to be called
 */

typedef struct builtin_s
{
	char *name;
	void (*func)(char **args);
} builtin_t;

#endif /* SHELL_H */
