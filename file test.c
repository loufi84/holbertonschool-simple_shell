#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_LINE 1024

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    char *envp[] = { /* Environnement minimal*/
        "PATH=/usr/bin",
        "HOME=/home/user",
        NULL
     };

    printf("Entrez une commande avec son chemin complet (ex: /bin/ls -l): ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    line[strcspn(line, "\n")] = '\0';

    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    char *command = args[0];

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execve(command, args, envp);

        perror("execve");
        exit(EXIT_FAILURE);
    } else {

        int status;
        waitpid(pid, &status, 0);
        printf("Le processus fils est terminé.\n");
    }

    return 0;
}
