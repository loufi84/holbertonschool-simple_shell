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
	int (*func)(char **args, int *exit_status);
} builtin_t;

extern char **environ;

char **split_string(char *string);
char *read_line(void);
void shutdown(char **args, char *line, int last_status);
void print_env(char **env);
int run_cmd(char **args, int cmd_c, const char *shell_n, int *exit_stat);
char *_getenv(const char *name);
void comments_handling(char *line);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void shell_help(char **args);
void help_help(void);
void help_exit(void);
void help_env(void);
int is_numeric(const char *str);
int _atoi(char *s);
char *trim_whitespace(char *str);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t len);
int handle_builtin(char **args, int *exit_status);
char *find_command_path(char *command, int *exit_status);
void print_error(char **args, int cmd_c, const char *shell_n, int *exit_stat);
void execute_command(char *cmd_path, char **args, const char *shell_n,
int *exit_stat);
int handle_help(char **args, int *exit_status);
int handle_env(char **args, int *exit_status);
int handle_exit(char **args, int *exit_status);


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
