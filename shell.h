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



#endif /* SHELL_H */
