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
#include <errno.h>

#define BUFFER_SIZE 1024
#define INIT_BUF_SIZE 128
#define MAX_ARGS 64

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
	void (*func)(char **);
} builtin_t;

extern char **environ;

char *split_string(char *string, char *array[]);
char *read_line(void);
void shutdown(char **code);
void print_env(char **env);
int built_in(char *cmd);
void path_handling(char **cmd);
void run_cmd(char *args[], const char *shell_name);
int what_is_cmd(char **cmd);
char *split_path(char *string, char *array[]);
char *_getenv(const char *name);
void path_error(char *args, char *path);
void alloc_error(char *cmd);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void comments_handling(char *line);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void shell_help(char **args);
void help_help(void);
void help_exit(void);
void help_env(void);
int is_numeric(const char *str);
int _atoi(char *s);


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



#endif /* SHELL_H */

